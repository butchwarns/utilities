#pragma once

#include "PluginParameters.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include "../BDSP/source/filter/MM2_Butterworth_TPT.h"
#include "../BDSP/source/filter/HP1_DCBlock.h"
#include "dsp/SmoothLinear.h"
#include "gui/sizes.h"

constexpr int NUM_CHANNELS = 2;          // Plugin works in stereo
constexpr int NUM_CROSSOVER_FILTERS = 2; // 2 Butterworth filters per band
constexpr float SMOOTHING_TIME_DEFAULT = 0.010f;

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

    void set_saved_window_size(int _window_width_saved, int _window_height_saved);
    int get_saved_window_width() const;
    int get_saved_window_height() const;

private:
    PluginParameters p;

    SmoothLinear smooth_width;
    SmoothLinear smooth_volume;
    SmoothLinear smooth_bass_mono_freq;
    SmoothLinear smooth_bass_width;
    SmoothLinear smooth_pan;
    SmoothLinear smooth_flip_l;
    SmoothLinear smooth_flip_r;

    bdsp::filter::MM2_Butterworth_TPT lp_crossover[NUM_CHANNELS][NUM_CROSSOVER_FILTERS];
    bdsp::filter::MM2_Butterworth_TPT hp_crossover[NUM_CHANNELS][NUM_CROSSOVER_FILTERS];

    bdsp::filter::HP1_DCBlock dc_block[NUM_CHANNELS];

    int window_width_saved;
    int window_height_saved;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
