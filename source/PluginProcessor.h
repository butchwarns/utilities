/*
PluginProcessor.h
Copyright (C) 2024 Butch Warns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PLUGIN_PROCESSOR_H
#define PLUGIN_PROCESSOR_H

#include "PluginParameters.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include "../BDSP/source/filter/HP1_DCBlock.h"
#include "dsp/CrossoverFilter.h"
#include "../BDSP/source/smoother/SmootherLinear.h"
#include "gui/sizes.h"

enum Channel
{
    L = 0,
    R = 1,
    NUM_CHANNELS
};

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

    static void set_saved_window_size(int _window_width_saved, int _window_height_saved);
    static int get_saved_window_width();
    static int get_saved_window_height();

private:
    PluginParameters p;

    bdsp::smoother::SmootherLinear<double> smooth_width;
    bdsp::smoother::SmootherLinear<double> smooth_volume;
    bdsp::smoother::SmootherLinear<double> smooth_bass_mono_freq;
    bdsp::smoother::SmootherLinear<double> smooth_bass_width;
    bdsp::smoother::SmootherLinear<double> smooth_pan;
    bdsp::smoother::SmootherLinear<double> smooth_flip_l;
    bdsp::smoother::SmootherLinear<double> smooth_flip_r;

    CrossoverFilter crossover[Channel::NUM_CHANNELS];

    bdsp::filter::HP1_DCBlock dc_filter[Channel::NUM_CHANNELS];

    inline void update_crossover_cutoff(double frequency);
    static inline void apply_phase_flip(double flip_l, double &left, double flip_r, double &right);
    inline void split_bands(double left, double right, double &lo_l, double &hi_l, double &lo_r, double &hi_r);
    static inline void apply_bass_width(double bass_width, double &left, double &right, double &lo_left, double &hi_left, double &lo_right, double &hi_right);
    static inline void apply_width(double width, double &left, double &right);
    static inline void apply_channels(ChannelsChoice channels, double &left, double &right);
    static inline void apply_volume(double volume, double &left, double &right);
    static inline void apply_pan(double pan, double &left, double &right);
    inline void apply_dc_block(double dc_block_active, double &left, double &right);

    static int window_width_saved;
    static int window_height_saved;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};

#endif // PLUGIN_PROCESSOR_H