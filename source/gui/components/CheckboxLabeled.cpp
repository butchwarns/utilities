#include "CheckboxLabeled.h"

CheckboxLabeled::CheckboxLabeled(PluginParameters &p, ParameterID param_id)
{
    ignoreUnused(param_id);

    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    label.getProperties().set("gui_class", "italic");

    addAndMakeVisible(&checkbox);
}

void CheckboxLabeled::paint(Graphics &g)
{
    ignoreUnused(g);
}

void CheckboxLabeled::resized()
{
    auto bounds = getLocalBounds();

    checkbox.setBounds(bounds.removeFromRight(CHECKBOX_DIM));
    label.setBounds(bounds);
}