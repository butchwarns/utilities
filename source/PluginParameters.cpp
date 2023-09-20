#include "PluginParameters.h"

PluginParameters::PluginParameters(juce::AudioProcessor &processor)
    : apvts(processor, nullptr, "parameters", parameter_layout()), sample_rate(1.0)
{
    channels_norm = apvts.getRawParameterValue("channels");
    volume_norm = apvts.getRawParameterValue("volume");
    width_norm = apvts.getRawParameterValue("width");
    mono_norm = apvts.getRawParameterValue("mono");
    bass_mono_norm = apvts.getRawParameterValue("bass_mono");
    bass_mono_freq_norm = apvts.getRawParameterValue("bass_mono_freq");
}

void PluginParameters::reset(double _sample_rate)
{
    sample_rate = _sample_rate;

    smooth_volume.reset(_sample_rate);
    smooth_width.reset(_sample_rate);
    smooth_bass_mono_freq.reset(_sample_rate);

    smooth_volume.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_width.set_time_constant(SMOOTHING_TIME_DEFAULT);
    smooth_bass_mono_freq.set_time_constant(SMOOTHING_TIME_DEFAULT);
}

juce::ValueTree PluginParameters::copy_state()
{
    return apvts.copyState();
}

juce::Identifier PluginParameters::state_type() const
{
    return apvts.state.getType();
}

void PluginParameters::replace_state(juce::ValueTree const &new_state)
{
    apvts.replaceState(new_state);
}

ChannelsChoice PluginParameters::channels()
{
    const auto choice = static_cast<ChannelsChoice>((int)*channels_norm);
    return choice;
}

float PluginParameters::volume()
{
    smooth_volume.set_target_val(*volume_norm);
    const float volume_smoothed_norm = smooth_volume.next();

    const auto db = bdsp::mappings::map_linear_norm<float>(volume_smoothed_norm, -66.1f, 35.0f);
    const float gain = bdsp::decibel::db_to_raw_gain_off(db, -66.0f);

    return gain;
}

float PluginParameters::normalise_volume(float gain)
{
    // Find dB value for given gain
    float db = 0.0f;
    if (gain <= bdsp::decibel::db_to_raw_gain(-66.0f))
    {
        db = -66.0f;
    }
    else
    {
        db = bdsp::decibel::raw_gain_to_db(gain);
    }

    // Normalise
    const auto norm = bdsp::mappings::map_linear<float>(db, -66.0, 35.0f, 0.0f, 1.0f);

    return norm;
}

float PluginParameters::width()
{
    smooth_width.set_target_val(*width_norm);
    const float width_smoothed = smooth_width.next();

    return width_smoothed;
}

bool PluginParameters::mono()
{
    return static_cast<bool>(*mono_norm);
}

bool PluginParameters::bass_mono()
{
    return static_cast<bool>(*bass_mono_norm);
}

float PluginParameters::bass_mono_freq()
{
    smooth_bass_mono_freq.set_target_val(*bass_mono_freq_norm);
    const float freq_smoothed_norm = smooth_bass_mono_freq.next();

    const float cv = bdsp::mappings::map_linear_norm(freq_smoothed_norm, -5.f, 5.0f);
    const float freq = bdsp::cv::VoltPerOct::volt_to_freq(cv, ZERO_VOLT_FREQ_BASS_MONO);

    return freq;
}

float PluginParameters::normalise_bass_mono_freq(float freq)
{
    const float cv = bdsp::cv::VoltPerOct::freq_to_volt(freq, ZERO_VOLT_FREQ_BASS_MONO);
    const float cv_norm = bdsp::mappings::map_linear(cv, -5.0f, 5.0f, 0.0f, 1.0f);

    return cv_norm;
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    std::unique_ptr<ParameterGroup> utility_grp = std::make_unique<ParameterGroup>("utility", "UTILITY", "|");
    utility_grp->addChild(std::make_unique<juce::AudioParameterChoice>("channels", "CHANNELS", CHANNELS_CHOICES, 0));
    utility_grp->addChild(std::make_unique<juce::AudioParameterFloat>("volume", "VOLUME", 0.0f, 1.0f, normalise_volume(1.0f)));
    utility_grp->addChild(std::make_unique<juce::AudioParameterFloat>("width", "WIDTH", 0.0f, 1.0f, 1.0f));
    utility_grp->addChild(std::make_unique<juce::AudioParameterBool>("mono", "MONO", false));
    utility_grp->addChild(std::make_unique<juce::AudioParameterBool>("bass_mono", "BASS_MONO", false));
    utility_grp->addChild(std::make_unique<juce::AudioParameterFloat>("bass_mono_freq", "BASS_MONO_FREQ", 0.0f, 1.0f, normalise_bass_mono_freq(120.0f)));

    layout.add(std::move(utility_grp));

    return layout;
}