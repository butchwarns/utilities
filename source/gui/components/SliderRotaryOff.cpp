#include "SliderRotaryOff.h"
SliderRotaryOff::SliderRotaryOff(PluginParameters &p, ParameterID param_id)
    : SliderRotary(p, param_id)
{
}

void SliderRotaryOff::sliderValueChanged(Slider *slider)
{
    const float val_denorm = p.denormalise_param_for_ui((float)(slider->getValue()), param_id);

    std::stringstream val_formatted;
    if (val_denorm > OFF_THRESHOLD)
    {
        // Format value string to the correct number of decimal places
        val_formatted << std::fixed << std::setprecision(num_decimal_places);
        val_formatted << val_denorm << value_suffix.toStdString();
    }
    else
    {
        // Below threshold, turn off
        val_formatted << "OFF";
    }

    label.setText(val_formatted.str(), dontSendNotification);
}