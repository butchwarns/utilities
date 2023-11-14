#include "Tooltip.h"
#include "colours.h"

Tooltip::Tooltip()
{
    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setEditable(false);
    label.getProperties().set("gui_class", "bold");
    label.setColour(Label::textColourId, RED_TRANSPARENT);
}

void Tooltip::set_tooltip(String msg)
{
    label.setText(msg, dontSendNotification);
}

void Tooltip::paint(Graphics &g)
{
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds());
}

void Tooltip::resized()
{
    label.setBounds(getLocalBounds());
}
