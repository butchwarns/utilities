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

float PluginParameters::width()
{
    return *width_norm;
}

float PluginParameters::denormalise_width(float val_norm)
{
    // Convert to percent
    return 100 * val_norm;
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

float PluginParameters::phase_flip_l()
{
    const float flip = bdsp::mappings::unipolar_to_bipolar((float)(*phase_flip_l_norm));
    return flip;
}

float PluginParameters::phase_flip_r()
{
    const float flip = bdsp::mappings::unipolar_to_bipolar((float)(*phase_flip_r_norm));
    return flip;
}

float PluginParameters::pan()
{
    return *pan_norm;
}
bool PluginParameters::dc_block()
{
    return (bool)*dc_block_norm;
}

float PluginParameters::denormalise_param_for_ui(float val_norm, const juce::ParameterID &parameter_id)
{
    auto param = parameter_id.getParamID();
    if (param == "volume")
    {
        return denormalise_volume_db(val_norm);
    }
    else if (param == "bass_mono_freq")
    {
        return denormalise_bass_mono_freq(val_norm);
    }
    else if (param == "width")
    {
        return denormalise_width(val_norm);
    }
    else
    {
        return val_norm;
    }
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    std::unique_ptr<ParameterGroup> phase_flip_grp = std::make_unique<ParameterGroup>("phase_flip", "PHASE_FLIP", "|");
    phase_flip_grp->addChild(std::make_unique<juce::AudioParameterBool>("phase_flip_l", "PHASE_FLIP_L", false));
    phase_flip_grp->addChild(std::make_unique<juce::AudioParameterBool>("phase_flip_r", "PHASE_FLIP_R", false));

    std::unique_ptr<ParameterGroup> channels_grp = std::make_unique<ParameterGroup>("channels", "CHANNELS", "|");
    channels_grp->addChild(std::make_unique<juce::AudioParameterChoice>("channels", "CHANNELS", CHANNELS_CHOICES, 0));
    channels_grp->addChild(std::make_unique<juce::AudioParameterBool>("mono", "MONO", false));

    std::unique_ptr<ParameterGroup> bass_mono_grp = std::make_unique<ParameterGroup>("bass_mono", "BASS_MONO", "|");
    bass_mono_grp->addChild(std::make_unique<juce::AudioParameterBool>("bass_mono", "BASS_MONO_ACTIVE", false));
    const float bass_mono_freq_default = normalise_bass_mono_freq(145.0f);
    bass_mono_grp->addChild(std::make_unique<juce::AudioParameterFloat>("bass_mono_freq", "BASS_MONO_FREQ", 0.0f, 1.0f, bass_mono_freq_default));

    std::unique_ptr<ParameterGroup> sliders_grp = std::make_unique<ParameterGroup>("sliders", "SLIDERS", "|");
    sliders_grp->addChild(std::make_unique<juce::AudioParameterFloat>("width", "WIDTH", 0.0f, 1.0f, 1.0f));
    // Tiny positive offset prevents default volume from showing minus sign (-0.0dB)
    const float volume_default = normalise_volume(1.001f);
    // Constructor with NormalisableRange allows for setting a finer slider interval
    sliders_grp->addChild(std::make_unique<juce::AudioParameterFloat>("volume", "VOLUME", NormalisableRange<float>(0.0f, 1.0f, 0.0001f), volume_default));
    sliders_grp->addChild(std::make_unique<juce::AudioParameterFloat>("pan", "PAN", 0.0f, 1.0f, 0.5f));

    std::unique_ptr<ParameterGroup> dc_block_group = std::make_unique<ParameterGroup>("dc_block", "DC_BLOCK", "|");
    dc_block_group->addChild(std::make_unique<juce::AudioParameterBool>("dc_block", "DC_BLOCK", false));

    layout.add(std::move(phase_flip_grp), std::move(channels_grp), std::move(bass_mono_grp), std::move(sliders_grp), std::move(dc_block_group));

    return layout;
}