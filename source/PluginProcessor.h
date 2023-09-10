#pragma once

#include "PluginParameters.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include "../BDSP/source/filter/LP1_RC_TPT.h"
#include "../BDSP/source/filter/HP1_RC_TPT.h"

constexpr int NUM_CROSSOVER_POLES = 2;

class PluginProcessor : public juce::AudioProcessor
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
    using AudioProcessor::processBlock;

    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

private:
    PluginParameters p;

    bdsp::filter::LP1_RC_TPT lp_crossover[NUM_CHANNELS][NUM_CROSSOVER_POLES];
    bdsp::filter::HP1_RC_TPT hp_crossover[NUM_CHANNELS][NUM_CROSSOVER_POLES];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
