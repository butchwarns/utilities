#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
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
    smooth_volume.reset(sampleRate);
    smooth_bass_mono_freq.reset(sampleRate);
    smooth_bass_width.reset(sampleRate);
    smooth_pan.reset(sampleRate);
    smooth_flip_l.reset(sampleRate);
    smooth_flip_r.reset(sampleRate);

    smooth_width.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_volume.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_bass_mono_freq.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_bass_width.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_pan.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_flip_l.set_time_constant(SMOOTHING_TIME_DEFAULT);
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
    float bass_width = 1.0;
    if (bass_mono)
    {
        bass_width = 0.0f;
    }
    smooth_bass_width.set_target_val(bass_width);
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
        // Rename current input samples for brevity
        float &l = left[n];
        float &r = right[n];

        // update smoothed parameters
        const float width_smooth = smooth_width.next();
        const float volume_smooth = smooth_volume.next();
        const float bass_mono_freq_smooth = smooth_bass_mono_freq.next();
        const float bass_width_smooth = smooth_bass_width.next();
        const float pan_smooth = smooth_pan.next();
        const float flip_l_smooth = smooth_flip_l.next();
        const float flip_r_smooth = smooth_flip_r.next();

        update_crossover_cutoff(bass_mono_freq_smooth);

        apply_phase_flip(flip_l_smooth, l, flip_r_smooth, r);

        // Split bands
        float lo_l = 0.0f;
        float lo_r = 0.0f;
        float hi_l = 0.0f;
        float hi_r = 0.0f;
        split_bands(l, r, lo_l, hi_l, lo_r, hi_r);

        apply_bass_width(bass_width_smooth, l, r, lo_l, hi_l, lo_r, hi_r);

        apply_width(width_smooth, l, r);

        apply_channels(channels, l, r);

        apply_volume(volume_smooth, l, r);

        apply_pan(pan_smooth, l, r);

        apply_dc_block(dc_block_active, l, r);
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

void PluginProcessor::update_crossover_cutoff(float frequency)
{
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        for (int i = 0; i < NUM_CROSSOVER_FILTERS; ++i)
        {
            lp_crossover[channel][i].set_cutoff(frequency);
            hp_crossover[channel][i].set_cutoff(frequency);
        }
    }
}

void PluginProcessor::apply_phase_flip(float flip_l, float &left, float flip_r, float &right)
{
    left *= flip_l;
    right *= flip_r;
}

float PluginProcessor::sum_to_mono(float left, float right)
{
    return (left + right) / 2.0f;
}

void PluginProcessor::split_bands(float &left, float &right, float &lo_l, float &hi_l, float &lo_r, float &hi_r)
{
    lo_l = left;
    lo_r = right;
    hi_l = left;
    hi_r = right;

    for (int i = 0; i < NUM_CROSSOVER_FILTERS; ++i)
    {
        lo_l = (float)(lp_crossover[0][i].process(lo_l).lp);
        lo_r = (float)(lp_crossover[1][i].process(lo_r).lp);
        hi_l = (float)(hp_crossover[0][i].process(hi_l).hp);
        hi_r = (float)(hp_crossover[1][i].process(hi_r).hp);
    }
}

void PluginProcessor::apply_bass_width(float bass_width, float &left, float &right, float &lo_l, float &hi_l, float &lo_r, float &hi_r)
{
    const float lo_mono_sum = sum_to_mono(lo_l, lo_r);
    lo_l = bass_width * lo_l + (1.0f - bass_width) * lo_mono_sum;
    lo_r = bass_width * lo_r + (1.0f - bass_width) * lo_mono_sum;
    left = hi_l + lo_l;
    right = hi_r + lo_r;
}
void PluginProcessor::apply_width(float width, float &left, float &right)
{
    const float mono_sum = sum_to_mono(left, right);
    left = width * left + (1.0f - width) * mono_sum;
    right = width * right + (1.0f - width) * mono_sum;
}

void PluginProcessor::apply_channels(ChannelsChoice channels, float &left, float &right)
{
    if (channels == LEFT)
    {
        right = left;
    }
    else if (channels == RIGHT)
    {
        left = right;
    }
    else if (channels == SWAPPED)
    {
        const float temp = left;
        left = right;
        right = temp;
    }
}

void PluginProcessor::apply_volume(float volume, float &left, float &right)
{
    left *= volume;
    right *= volume;
}

void PluginProcessor::apply_pan(float pan, float &left, float &right)
{
    left = (2.0f * (1.0f - pan)) * left;
    right = (2.0f * pan) * right;
}

void PluginProcessor::apply_dc_block(float dc_block_active, float &left, float &right)
{
    const auto left_no_dc = (float)(dc_block[0].process(left));
    const auto right_no_dc = (float)(dc_block[1].process(right));
    if (dc_block_active)
    {
        left = left_no_dc;
        right = right_no_dc;
    }
}