#pragma once

#include "PluginParameters.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include "../BDSP/source/filter/MM2_Butterworth_TPT.h"
#include "../BDSP/source/filter/HP1_DCBlock.h"
#include "../BDSP/source/smoother/SmootherLinear.h"
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

    bdsp::smoother::SmootherLinear smooth_width;
    bdsp::smoother::SmootherLinear smooth_volume;
    bdsp::smoother::SmootherLinear smooth_bass_mono_freq;
    bdsp::smoother::SmootherLinear smooth_bass_width;
    bdsp::smoother::SmootherLinear smooth_pan;
    bdsp::smoother::SmootherLinear smooth_flip_l;
    bdsp::smoother::SmootherLinear smooth_flip_r;

    bdsp::filter::MM2_Butterworth_TPT lp_crossover[NUM_CHANNELS][NUM_CROSSOVER_FILTERS];
    bdsp::filter::MM2_Butterworth_TPT hp_crossover[NUM_CHANNELS][NUM_CROSSOVER_FILTERS];

    bdsp::filter::HP1_DCBlock dc_block[NUM_CHANNELS];

    inline void update_crossover_cutoff(float frequency);
    static inline void apply_phase_flip(float flip_l, float &left, float flip_r, float &right);
    static inline float sum_to_mono(float left, float right);
    static inline float difference_stereo(float channel, float mono_sum);
    inline void split_bands(float &left, float &right, float &lo_l, float &hi_l, float &lo_r, float &hi_r);
    static inline void apply_bass_width(float bass_width, float &left, float &right, float &lo_l, float &hi_l, float &lo_r, float &hi_r);
    static inline void apply_width(float width, float &left, float &right);
    static inline void apply_channels(ChannelsChoice channels, float &left, float &right);
    static inline void apply_volume(float volume, float &left, float &right);
    static inline void apply_pan(float pan, float &left, float &right);
    inline void apply_dc_block(float dc_block_active, float &left, float &right);

    int window_width_saved;
    int window_height_saved;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
