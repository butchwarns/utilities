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
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
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

    p.reset(sampleRate);
    smooth_width.reset(sampleRate);

    smooth_width.set_time_constant(SMOOTHING_TIME_WIDTH);

    for (int ch = 0; ch < 2; ++ch)
    {
        for (int i = 0; i < 2; ++i)
        {
            lp_crossover[i][ch].reset(sampleRate);
            hp_crossover[i][ch].reset(sampleRate);
        }
    }
}

void PluginProcessor::releaseResources()
{
}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
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

    // Update parameter values once per block
    // TODO..
    const float volume = p.volume();
    float target_width = p.width();
    float width = 0.0f;
    const bool mono = p.mono();
    const ChannelsChoice channels = p.channels();
    const bool bass_mono = p.bass_mono();
    const float bass_mono_freq = p.bass_mono_freq();
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int i = 0; i < NUM_CROSSOVER_POLES; ++i)
        {
            lp_crossover[channel][i].set_cutoff(bass_mono_freq);
            hp_crossover[channel][i].set_cutoff(bass_mono_freq);
        }
    }

    // Apply mono switch and smoothing
    if (mono)
    {
        target_width = 0.0f;
    }

    smooth_width.set_target_val(target_width);
    width = smooth_width.next();

    // PROCESS AUDIO

    float *left_ch = buffer.getWritePointer(0);
    float *right_ch = buffer.getWritePointer(1);

    for (int n = 0; n < buffer.getNumSamples(); ++n)
    {
        if (channels == ChannelsChoice::LEFT)
        {
            right_ch[n] = left_ch[n];
        }
        else if (channels == ChannelsChoice::RIGTH)
        {
            left_ch[n] = right_ch[n];
        }
        else // Stereo
        {
            float mono_sum = 0.0f;
            float crossover_lower_band[NUM_CHANNELS] = {0.0f};
            float crossover_upper_band[NUM_CHANNELS] = {0.0f};

            for (int channel = 0; channel < totalNumInputChannels; ++channel)
            {
                auto *x = buffer.getWritePointer(channel);
                // Apply output volume
                x[n] = volume * x[n];

                mono_sum += x[n];

                // If not mono, use bass mono crossover
                if (!mono)
                {
                    crossover_lower_band[channel] = x[n];
                    for (int i = 0; i < 2; ++i)
                    {
                        crossover_lower_band[channel] = lp_crossover[channel][i].process(crossover_lower_band[channel]);
                        crossover_upper_band[channel] = hp_crossover[channel][i].process(crossover_upper_band[channel]);
                    }
                }
            }

            // Apply bass mono setting
            if (bass_mono)
            {
                float lower_band[NUM_CHANNELS] = {0.0f};
                float upper_band[NUM_CHANNELS] = {0.0f};
                for (int channel = 0; channel < totalNumInputChannels; ++channel)
                {
                    auto *x = buffer.getWritePointer(channel);
                    lower_band[channel] = x[n];
                    upper_band[channel] = x[n];
                    for (int i = 0; i < NUM_CROSSOVER_POLES; ++i)
                    {
                        lower_band[channel] = lp_crossover[channel][i].process(lower_band[channel]);
                        upper_band[channel] = hp_crossover[channel][i].process(upper_band[channel]);
                    }
                }
                const float lower_band_mono = (lower_band[0] + lower_band[1]) * 0.5f;
                for (int channel = 0; channel < totalNumInputChannels; ++channel)
                {
                    auto *x = buffer.getWritePointer(channel);
                    x[n] = upper_band[channel] + lower_band_mono;
                }
            }

            // Apply stereo width setting or mono
            for (int channel = 0; channel < totalNumInputChannels; ++channel)
            {
                auto *x = buffer.getWritePointer(channel);
                x[n] = width * x[n] + (1.0f - width) * mono_sum;
            }
        }
    }
}

bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *PluginProcessor::createEditor()
{
    // return new PluginEditor(*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    juce::ValueTree state = p.copy_state();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    if (xml.get() != nullptr)
    {
        if (xml->hasTagName(p.state_type()))
        {
            p.replace_state(juce::ValueTree::fromXml(*xml));
        }
    }
}

// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
