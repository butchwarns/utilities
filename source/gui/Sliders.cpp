#include "Sliders.h"

Sliders::Sliders(PluginParameters &p) : slider_width(p, "width"), slider_volume(p, "volume"), slider_pan(p, "pan")
{
    addAndMakeVisible(&slider_width);
    slider_width.label.set_text("WIDTH");
    slider_width.label.getProperties().set("gui_class", "bold");
    slider_width.slider.set_decimal_places_to_display(0);
    slider_width.slider.set_value_suffix("%");

    addAndMakeVisible(&slider_volume);
    slider_volume.label.set_text("VOLUME");
    slider_volume.label.getProperties().set("gui_class", "bold");
    slider_volume.slider.slider.getProperties().set("gui_class", "slider_rotary_off");
    slider_volume.slider.set_decimal_places_to_display(1);
    slider_volume.slider.set_value_suffix("dB");

    addAndMakeVisible(&slider_pan);
    slider_pan.label.set_text("PAN");
    slider_pan.label.getProperties().set("gui_class", "bold");
    slider_pan.slider.slider.getProperties().set("param", "pan");
    slider_pan.slider.slider.getProperties().set("gui_class", "slider_symmetric");
}

void Sliders::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Sliders::resized()
{
    auto bounds = getLocalBounds();

    slider_width.setBounds(bounds.removeFromTop(SLIDER_ROTARY_LABELED_HEIGHT));
    slider_pan.setBounds(bounds.removeFromBottom(SLIDER_ROTARY_LABELED_HEIGHT));
    // bounds.reduce(0, bounds.getHeight() - (SLIDER_ROTARY_LABELED_HEIGHT / 2));
    slider_volume.setBounds(bounds);
}