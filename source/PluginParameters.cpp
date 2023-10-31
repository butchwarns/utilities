#include "PluginParameters.h"

PluginParameters::PluginParameters(juce::AudioProcessor &processor)
    : apvts(processor, nullptr, "parameters", parameter_layout())
{
    channels_norm = apvts.getRawParameterValue("channels");
    volume_norm = apvts.getRawParameterValue("volume");
    width_norm = apvts.getRawParameterValue("width");
    mono_norm = apvts.getRawParameterValue("mono");
    bass_mono_norm = apvts.getRawParameterValue("bass_mono");
    bass_mono_freq_norm = apvts.getRawParameterValue("bass_mono_freq");
    phase_flip_l_norm = apvts.getRawParameterValue("phase_flip_l");
    phase_flip_r_norm = apvts.getRawParameterValue("phase_flip_r");
    pan_norm = apvts.getRawParameterValue("pan");
    dc_block_norm = apvts.getRawParameterValue("dc_block");
}

ChannelsChoice PluginParameters::channels()
{
    const auto choice = static_cast<ChannelsChoice>((int)*channels_norm);
    return choice;
}

String PluginParameters::channels_string_from_index(int value, int max_string_len)
{
    String choice = CHANNELS_CHOICES[value];

    constrain_string_length(choice, max_string_len);

    return choice;
}

float PluginParameters::volume()
{
    const float gain = denormalise_volume(*volume_norm);
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

    const auto val_norm = bdsp::mappings::normalise(db, -66.1f, 35.0f);

    return val_norm;
}

float PluginParameters::denormalise_volume(float val_norm)
{
    const auto db = denormalise_volume_db(val_norm);
    const float gain = bdsp::decibel::db_to_raw_gain_off(db, OFF_THRESHOLD);

    return gain;
}

float PluginParameters::denormalise_volume_db(float val_norm)
{
    const auto db = bdsp::mappings::map_linear_norm<float>(val_norm, -66.1f, 35.0f);

    return db;
}

String PluginParameters::volume_string_from_value(float value, int max_string_len)
{
    const float val_denorm = denormalise_volume_db(value);

    std::stringstream val_formatted;
    if (val_denorm <= OFF_THRESHOLD)
    {
        // Below threshold, turn off
        val_formatted << "OFF";
    }
    else // Default
    {
        // Format value string to the correct number of decimal places
        const int num_decimal_places = 1;
        const String value_suffix = "dB";
        val_formatted << std::fixed << std::setprecision(num_decimal_places);
        val_formatted << val_denorm << value_suffix;
    }

    String val_formatted_str = val_formatted.str();

    constrain_string_length(val_formatted_str, max_string_len);

    return val_formatted_str;
}

float PluginParameters::width()
{
    return *width_norm;
}

float PluginParameters::denormalise_width(float val_norm)
{
    // Convert to percent
    return 100 * val_norm;
}

String PluginParameters::width_string_from_value(float value, int max_string_len)
{
    const float val_denorm = denormalise_width(value);

    std::stringstream val_formatted;
    const int num_decimal_places = 0;
    const String value_suffix = "%";
    val_formatted << std::fixed << std::setprecision(num_decimal_places);
    val_formatted << val_denorm << value_suffix;

    String val_formatted_str = val_formatted.str();

    constrain_string_length(val_formatted_str, max_string_len);

    return val_formatted_str;
}

bool PluginParameters::mono()
{
    return static_cast<bool>(*mono_norm);
}

String PluginParameters::mono_string_from_bool(bool value, int max_string_len)
{
    String s;
    if (value)
    {
        s = "MONO";
    }
    else
    {
        s = "STEREO";
    }

    constrain_string_length(s, max_string_len);

    return s;
}

bool PluginParameters::bass_mono()
{
    return static_cast<bool>(*bass_mono_norm);
}

String PluginParameters::bass_mono_string_from_bool(bool value, int max_string_len)
{
    String s;
    if (value)
    {
        s = "BASS MONO";
    }
    else
    {
        s = "BASS STEREO";
    }

    constrain_string_length(s, max_string_len);

    return s;
}

float PluginParameters::bass_mono_freq()
{
    const float freq = denormalise_bass_mono_freq(*bass_mono_freq_norm);

    return freq;
}

float PluginParameters::normalise_bass_mono_freq(float freq)
{
    const float cv = bdsp::cv::VoltPerOctave::freq_to_volt(freq, ZERO_VOLT_FREQ_BASS_MONO);
    const float cv_norm = bdsp::mappings::normalise(cv, -5.0f, 5.0f);

    return cv_norm;
}

float PluginParameters::denormalise_bass_mono_freq(float val_norm)
{
    const float cv = bdsp::mappings::map_linear_norm(val_norm, -5.f, 5.0f);
    const float freq = bdsp::cv::VoltPerOctave::volt_to_freq(cv, ZERO_VOLT_FREQ_BASS_MONO);

    return freq;
}

String PluginParameters::bass_mono_freq_string_from_value(float value, int max_string_len)
{
    const float val_denorm = denormalise_bass_mono_freq(value);

    std::stringstream val_formatted;
    const int num_decimal_places = 0;
    const String value_suffix = "Hz";
    val_formatted << std::fixed << std::setprecision(num_decimal_places);
    val_formatted << val_denorm << value_suffix.toStdString();

    String val_formatted_str = val_formatted.str();

    constrain_string_length(val_formatted_str, max_string_len);

    return val_formatted_str;
}

float PluginParameters::phase_flip_l()
{
    const float flip = bdsp::mappings::unipolar_to_bipolar((float)(*phase_flip_l_norm));
    return flip;
}

String PluginParameters::phase_flip_l_string_from_bool(bool value, int max_string_len)
{
    String s;
    if (value)
    {
        s = "L FLIPPED";
    }
    else
    {
        s = "L NOT FLIPPED";
    }

    constrain_string_length(s, max_string_len);

    return s;
}

float PluginParameters::phase_flip_r()
{
    const float flip = bdsp::mappings::unipolar_to_bipolar((float)(*phase_flip_r_norm));
    return flip;
}

String PluginParameters::phase_flip_r_string_from_bool(bool value, int max_string_len)
{
    String s;
    if (value)
    {
        s = "R FLIPPED";
    }
    else
    {
        s = "R NOT FLIPPED";
    }

    constrain_string_length(s, max_string_len);

    return s;
}

float PluginParameters::pan()
{
    return *pan_norm;
}

String PluginParameters::pan_string_from_value(float value, int max_string_len)
{
    std::stringstream val_formatted;
    const float centre_range = 0.005f;
    val_formatted << std::fixed << std::setprecision(0);
    if (value < 0.5f - centre_range)
    {
        val_formatted << bdsp::mappings::map_linear(value, 0.0f, 0.5f, 50.0f, 0.0f) << "L";
    }
    else if (value > 0.5f + centre_range)
    {
        val_formatted << bdsp::mappings::map_linear(value, 0.5f, 1.0f, 0.0f, 50.0f) << "R";
    }
    else
    {
        val_formatted << "C";
    }

    String val_formatted_str = val_formatted.str();

    constrain_string_length(val_formatted_str, max_string_len);

    return val_formatted_str;
}

bool PluginParameters::dc_block()
{
    return (bool)*dc_block_norm;
}

String PluginParameters::dc_block_string_from_bool(bool value, int max_string_len)
{
    String s;
    if (value)
    {
        s = "DC BLOCKED";
    }
    else
    {
        s = "DC NOT BLOCKED";
    }

    constrain_string_length(s, max_string_len);

    return s;
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    std::unique_ptr<ParameterGroup> phase_flip_grp = std::make_unique<ParameterGroup>("phase_flip", "PHASE_FLIP", "|");
    phase_flip_grp->addChild(std::make_unique<juce::AudioParameterBool>("phase_flip_l", "PHASE_FLIP_L", false, "", phase_flip_l_string_from_bool));
    phase_flip_grp->addChild(std::make_unique<juce::AudioParameterBool>("phase_flip_r", "PHASE_FLIP_R", false, "", phase_flip_r_string_from_bool));

    std::unique_ptr<ParameterGroup> channels_grp = std::make_unique<ParameterGroup>("channels", "CHANNELS", "|");
    channels_grp->addChild(std::make_unique<juce::AudioParameterChoice>("channels", "CHANNELS", CHANNELS_CHOICES, 0, "", channels_string_from_index));
    channels_grp->addChild(std::make_unique<juce::AudioParameterBool>("mono", "MONO", false, "", mono_string_from_bool));

    std::unique_ptr<ParameterGroup> bass_mono_grp = std::make_unique<ParameterGroup>("bass_mono", "BASS_MONO", "|");
    bass_mono_grp->addChild(std::make_unique<juce::AudioParameterBool>("bass_mono", "BASS_MONO", false, "", bass_mono_string_from_bool));
    const float bass_mono_freq_default = normalise_bass_mono_freq(120.0f);
    bass_mono_grp->addChild(std::make_unique<juce::AudioParameterFloat>("bass_mono_freq", "BASS_MONO_FREQ", NormalisableRange<float>(0.0f, 1.0f, 0.0001f), bass_mono_freq_default, "", AudioProcessorParameter::genericParameter, bass_mono_freq_string_from_value));

    std::unique_ptr<ParameterGroup> sliders_grp = std::make_unique<ParameterGroup>("sliders", "SLIDERS", "|");
    sliders_grp->addChild(std::make_unique<juce::AudioParameterFloat>("width", "WIDTH", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f, "", AudioProcessorParameter::genericParameter, width_string_from_value));
    // Tiny positive offset prevents default volume from showing minus sign (-0.0dB)
    const float volume_default = normalise_volume(1.001f);
    // Constructor with NormalisableRange allows for setting a finer slider interval
    sliders_grp->addChild(std::make_unique<juce::AudioParameterFloat>("volume", "VOLUME", NormalisableRange<float>(0.0f, 1.0f, 0.0001f), volume_default, "", AudioProcessorParameter::genericParameter, volume_string_from_value));
    sliders_grp->addChild(std::make_unique<juce::AudioParameterFloat>("pan", "PAN", NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f, "", AudioProcessorParameter::genericParameter, pan_string_from_value));

    std::unique_ptr<ParameterGroup> dc_block_group = std::make_unique<ParameterGroup>("dc_block", "DC_BLOCK", "|");
    dc_block_group->addChild(std::make_unique<juce::AudioParameterBool>("dc_block", "DC_BLOCK", false, "", dc_block_string_from_bool));

    layout.add(std::move(phase_flip_grp), std::move(channels_grp), std::move(bass_mono_grp), std::move(sliders_grp), std::move(dc_block_group));

    return layout;
}

void PluginParameters::constrain_string_length(String &s, int max_len)
{
    const int len = s.length();
    if (len > max_len)
    {
        s = s.dropLastCharacters(len - max_len);
    }
}