#include "SliderRotary.h"

SliderRotary::SliderRotary(PluginParameters &_p, ParameterID _param_id) : p(_p), param_id(_param_id), num_decimal_places(2), value_suffix("")
{
    slider.addListener(this);

    addAndMakeVisible(&slider);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setColour(Slider::textBoxTextColourId, Colours::black);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setRange(0.0f, 1.0f, 0.001f);

    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);

    attachment = std::make_unique<SliderAttachment>(p.apvts, param_id.getParamID(), slider);
}

void SliderRotary::set_decimal_places_to_display(int _num_decimal_places)
{
    num_decimal_places = _num_decimal_places;
}

void SliderRotary::set_value_suffix(juce::String _value_suffix)
{
    value_suffix = _value_suffix;
}

void SliderRotary::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void SliderRotary::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(bounds.removeFromTop(KNOB_DIM));
    label.setBounds(bounds);
}

void SliderRotary::sliderValueChanged(Slider *slider)
{
    const float val_denorm = p.denormalise_param_for_ui((float)(slider->getValue()), param_id);

    std::stringstream val_formatted;
    const bool is_slider_rotary_off = slider->getProperties()["gui_class"] == "slider_rotary_off";
    const bool is_param_pan = slider->getProperties()["param"] == "pan";
    if (is_param_pan)
    {
        // Map to panning values
        const float centre_range = 0.005f;
        val_formatted << std::fixed << std::setprecision(0);
        if (val_denorm < 0.5f - centre_range)
        {
            val_formatted << bdsp::mappings::map_linear(val_denorm, 0.0f, 0.5f, 50.0f, 0.0f) << "L";
        }
        else if (val_denorm > 0.5f + centre_range)
        {
            val_formatted << bdsp::mappings::map_linear(val_denorm, 0.5f, 1.0f, 0.0f, 50.0f) << "R";
        }
        else
        {
            val_formatted << "C";
        }
    }
    else if (is_slider_rotary_off && (val_denorm <= OFF_THRESHOLD))
    {
        // Below threshold, turn off
        val_formatted << "OFF";
    }
    else // Default
    {
        // Format value string to the correct number of decimal places
        val_formatted << std::fixed << std::setprecision(num_decimal_places);
        val_formatted << val_denorm << value_suffix.toStdString();
    }

    label.setText(val_formatted.str(), dontSendNotification);
}