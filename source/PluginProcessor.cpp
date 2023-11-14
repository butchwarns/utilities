#include "PluginProcessor.h"
#include "PluginEditor.h"

int PluginProcessor::window_width_saved = WIN_WIDTH;
int PluginProcessor::window_height_saved = WIN_HEIGHT;

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      p(*this)
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

    for (int ch = 0; ch < Channel::NUM_CHANNELS; ++ch)
    {
        crossover[ch].reset(sampleRate);

        dc_filter[ch].reset(sampleRate);
        dc_filter[ch].set_cutoff(10.0); // Fixed cutoff
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
    const double volume = p.volume();

    smooth_volume.set_target_val(volume);

    const bool mono = p.mono();
    double width = p.width();
    if (mono)
    {
        width = 0.0f;
    }
    smooth_width.set_target_val(width);

    const bool bass_mono = p.bass_mono();
    double bass_width = 1.0;
    if (bass_mono)
    {
        bass_width = 0.0f;
    }
    smooth_bass_width.set_target_val(bass_width);
    const double bass_mono_freq = p.bass_mono_freq();
    smooth_bass_mono_freq.set_target_val(bass_mono_freq);

    const double phase_flip_l = p.phase_flip_l();
    smooth_flip_l.set_target_val(phase_flip_l);
    const double phase_flip_r = p.phase_flip_r();
    smooth_flip_r.set_target_val(phase_flip_r);

    const double pan = p.pan();
    smooth_pan.set_target_val(pan);

    const bool dc_block = p.dc_block();

    // PROCESS AUDIO SAMPLES

    float *left = buffer.getWritePointer(0);
    float *right = buffer.getWritePointer(1);

    for (int n = 0; n < buffer.getNumSamples(); ++n)
    {
        auto l = (double)left[n];
        auto r = (double)right[n];

        // update smoothed parameters
        const double width_smooth = smooth_width.next();
        const double volume_smooth = smooth_volume.next();
        const double bass_mono_freq_smooth = smooth_bass_mono_freq.next();
        const double bass_width_smooth = smooth_bass_width.next();
        const double pan_smooth = smooth_pan.next();
        const double flip_l_smooth = smooth_flip_l.next();
        const double flip_r_smooth = smooth_flip_r.next();

        update_crossover_cutoff(bass_mono_freq_smooth);

        apply_phase_flip(flip_l_smooth, l, flip_r_smooth, r);

        double lo_l = 0.0f;
        double lo_r = 0.0f;
        double hi_l = 0.0f;
        double hi_r = 0.0f;
        split_bands(l, r, lo_l, hi_l, lo_r, hi_r);

        if (bass_mono)
        {
            apply_bass_width(bass_width_smooth, l, r, lo_l, hi_l, lo_r, hi_r);
        }

        apply_width(width_smooth, l, r);

        apply_channels(channels, l, r);

        apply_volume(volume_smooth, l, r);

        apply_pan(pan_smooth, l, r);

        apply_dc_block(dc_block, l, r);

        left[n] = (float)l;
        right[n] = (float)r;
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

int PluginProcessor::get_saved_window_width()
{
    return window_width_saved;
}

int PluginProcessor::get_saved_window_height()
{
    return window_height_saved;
}

// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

void PluginProcessor::update_crossover_cutoff(double frequency)
{
    for (int channel = 0; channel < Channel::NUM_CHANNELS; ++channel)
    {
        crossover[channel].set_cutoff(frequency);
    }
}

void PluginProcessor::apply_phase_flip(double flip_l, double &left, double flip_r, double &right)
{
    left *= flip_l;
    right *= flip_r;
}

void PluginProcessor::encode_mid_side(double left, double right, double &mid, double &side)
{
    mid = (left + right) / sqrt(2.0);
    side = (left - right) / sqrt(2.0);
}

void PluginProcessor::decode_mid_side(double mid, double side, double &left, double &right)
{
    left = (mid + side) / sqrt(2.0);
    right = (mid - side) / sqrt(2.0);
}

void PluginProcessor::split_bands(double left, double right, double &lo_l, double &hi_l, double &lo_r, double &hi_r)
{
    CrossoverFilterOutput bands_left = crossover[Channel::L].process(left);
    CrossoverFilterOutput bands_right = crossover[Channel::R].process(right);

    lo_l = bands_left.lo;
    hi_l = bands_left.hi;
    lo_r = bands_right.lo;
    hi_r = bands_right.hi;
}

void PluginProcessor::apply_bass_width(double bass_width, double &left, double &right, double &lo_left, double &hi_left, double &lo_right, double &hi_right)
{
    double lo_mid = 0.0;
    double lo_side = 0.0;

    encode_mid_side(lo_left, lo_right, lo_mid, lo_side);

    lo_side *= bass_width;

    decode_mid_side(lo_mid, lo_side, lo_left, lo_right);

    left = hi_left + lo_left;
    right = hi_right + lo_right;
}

void PluginProcessor::apply_width(double width, double &left, double &right)
{
    double mid = 0.0;
    double side = 0.0;

    encode_mid_side(left, right, mid, side);

    side *= width;

    decode_mid_side(mid, side, left, right);
}

void PluginProcessor::apply_channels(ChannelsChoice channels, double &left, double &right)
{
    if (channels == ChannelsChoice::LEFT)
    {
        right = left;
    }
    else if (channels == ChannelsChoice::RIGHT)
    {
        left = right;
    }
    else if (channels == ChannelsChoice::SWAPPED)
    {
        const double temp = left;
        left = right;
        right = temp;
    }
}

void PluginProcessor::apply_volume(double volume, double &left, double &right)
{
    left *= volume;
    right *= volume;
}

void PluginProcessor::apply_pan(double pan, double &left, double &right)
{
    // Use constant power panning
    left *= dsp::FastMathApproximations::cos<double>(pan);
    right *= dsp::FastMathApproximations::sin<double>(pan);

    // Scale to 0dB at center position
    // (Scale down by tiny amount to peak at close to 0dB!)
    left *= sqrt(2.0);
    right *= sqrt(2.0);
}

void PluginProcessor::apply_dc_block(double dc_block_active, double &left, double &right)
{
    const auto left_no_dc = dc_filter[Channel::L].process(left);
    const auto right_no_dc = dc_filter[Channel::R].process(right);

    if ((bool)dc_block_active)
    {
        left = left_no_dc;
        right = right_no_dc;
    }
}