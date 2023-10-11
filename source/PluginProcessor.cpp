#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
      p(*this), window_width_saved(WIN_WIDTH), window_height_saved(WIN_HEIGHT)
{
}

PluginProcessor::~PluginProcessor()
{
}

const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
    return false;
}

bool PluginProcessor::producesMidi() const
{
    return false;
}

bool PluginProcessor::isMidiEffect() const
{
    return false;
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String PluginProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void PluginProcessor::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);

    smooth_width.reset(sampleRate);
    smooth_width.set_time_constant(SMOOTHING_TIME_DEFAULT);

    smooth_volume.reset(sampleRate);
    smooth_volume.set_time_constant(SMOOTHING_TIME_DEFAULT);

    smooth_bass_mono_freq.reset(sampleRate);
    smooth_bass_mono_freq.set_time_constant(SMOOTHING_TIME_DEFAULT);

    smooth_pan.reset(sampleRate);
    smooth_pan.set_time_constant(SMOOTHING_TIME_DEFAULT);

    smooth_flip_l.reset(sampleRate);
    smooth_flip_l.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_flip_r.reset(sampleRate);
    smooth_flip_r.set_time_constant(SMOOTHING_TIME_DEFAULT);

    for (int ch = 0; ch < 2; ++ch)
    {
        for (int i = 0; i < 2; ++i)
        {
            lp_crossover[i][ch].reset(sampleRate);
            hp_crossover[i][ch].reset(sampleRate);
        }

        dc_block[ch].reset(sampleRate);
    }
}

void PluginProcessor::releaseResources()
{
}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    // Only stereo layout supported
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    // Layout is supported
    return true;
}

void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                   juce::MidiBuffer &midiMessages)
{
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // No need to keep this code if your algorithm always overwrites
    // all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // UPDATE PARAMETER VALUES (once per block)

    const ChannelsChoice channels = p.channels();
    const float volume = p.volume();

    smooth_volume.set_target_val(volume);

    const bool mono = p.mono();
    float width = p.width();
    if (mono)
    {
        width = 0.0f;
    }
    smooth_width.set_target_val(width);

    const bool bass_mono = p.bass_mono();
    const float bass_mono_freq = p.bass_mono_freq();
    smooth_bass_mono_freq.set_target_val(bass_mono_freq);

    const float phase_flip_l = p.phase_flip_l();
    smooth_flip_l.set_target_val(phase_flip_l);
    const float phase_flip_r = p.phase_flip_r();
    smooth_flip_r.set_target_val(phase_flip_r);

    const float pan = p.pan();
    smooth_pan.set_target_val(pan);

    const bool dc_block_active = p.dc_block();

    // PROCESS AUDIO SAMPLES

    float *left = buffer.getWritePointer(0);
    float *right = buffer.getWritePointer(1);

    for (int n = 0; n < buffer.getNumSamples(); ++n)
    {
        // update smoothed parameters
        float width_smooth = smooth_width.next();
        float volume_smooth = smooth_volume.next();
        float bass_mono_freq_smooth = smooth_bass_mono_freq.next();
        float pan_smooth = smooth_pan.next();
        float flip_l_smooth = smooth_flip_l.next();
        float flip_r_smooth = smooth_flip_r.next();

        // Set filter cutoff
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            for (int i = 0; i < NUM_CROSSOVER_POLES; ++i)
            {
                lp_crossover[channel][i].set_cutoff(bass_mono_freq_smooth);
                hp_crossover[channel][i].set_cutoff(bass_mono_freq_smooth);
            }
        }

        // Apply phase flip
        left[n] = flip_l_smooth * left[n];
        right[n] = flip_r_smooth * right[n];

        // create mono sum
        const float mono_sum = (left[n] + right[n]) / 2.0f;

        // Apply bass mono

        // Split both channels into bands
        float lo_left = left[n];
        float lo_right = right[n];
        float hi_left = left[n];
        float hi_right = right[n];

        for (int i = 0; i < NUM_CROSSOVER_POLES; ++i)
        {
            lo_left = (float)(lp_crossover[0][i].process(lo_left));
            lo_right = (float)(lp_crossover[1][i].process(lo_right));
            hi_left = (float)(hp_crossover[0][i].process(hi_left));
            hi_right = (float)(hp_crossover[1][i].process(hi_right));
        }

        // Summ bass band to mono
        if (width_smooth > 0.0f && bass_mono)
        {
            const float lo_mono_sum = (lo_left + lo_right) / 2.0f;

            // Copy to output
            left[n] = hi_left + lo_mono_sum;
            right[n] = hi_right + lo_mono_sum;
        }

        // Apply stereo width
        left[n] = width_smooth * left[n] + (1.0f - width_smooth) * mono_sum;
        right[n] = width_smooth * right[n] + (1.0f - width_smooth) * mono_sum;

        // Apply channels param
        if (channels == LEFT)
        {
            right[n] = left[n];
        }
        else if (channels == RIGHT)
        {
            left[n] = right[n];
        }
        else if (channels == SWAPPED)
        {
            const float temp = left[n];
            left[n] = right[n];
            right[n] = temp;
        }

        // Apply output volume
        left[n] = volume_smooth * left[n];
        right[n] = volume_smooth * right[n];

        // Apply pan
        left[n] = (2.0f * (1.0f - pan_smooth)) * left[n];
        right[n] = (2.0f * pan_smooth) * right[n];

        // Apply DC blocking filter
        const auto left_no_dc = (float)(dc_block[0].process(left[n]));
        const auto right_no_dc = (float)(dc_block[1].process(right[n]));
        if (dc_block_active)
        {
            left[n] = left_no_dc;
            right[n] = right_no_dc;
        }
    }
}

bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *PluginProcessor::createEditor()
{
    return new PluginEditor(*this, p);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    // Save window size to state
    auto elem = p.apvts.state.getOrCreateChildWithName("window_size", nullptr);
    elem.setProperty("window_width", window_width_saved, nullptr);
    elem.setProperty("window_height", window_height_saved, nullptr);

    auto state = p.apvts.copyState();

    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    if (xml != nullptr)
    {
        if (xml->hasTagName(p.apvts.state.getType()))
        {
            auto state = juce::ValueTree::fromXml(*xml);
            p.apvts.replaceState(state);

            // Restore window size from state
            auto elem = p.apvts.state.getChildWithName("window_size");
            const int width = elem.getProperty("window_width");
            const int height = elem.getProperty("window_height");
            set_saved_window_size(width, height);
        }
    }
}

void PluginProcessor::set_saved_window_size(int _window_width_saved, int _window_height_saved)
{
    window_width_saved = _window_width_saved;
    window_height_saved = _window_height_saved;
}

int PluginProcessor::get_saved_window_width() const
{
    return window_width_saved;
}

int PluginProcessor::get_saved_window_height() const
{
    return window_height_saved;
}

// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
