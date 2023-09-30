#include "PhaseFlip.h"

PhaseFlip::PhaseFlip(PluginParameters &p) : check_l(p, "phase_flip_l"), check_r(p, "phase_flip_r")
{
    addAndMakeVisible(&label);
    label.setText("PHASE FLIP", dontSendNotification);
    label.setColour(Label::textColourId, Colours::black);
    label.setJustificationType(Justification::centred);
    label.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&check_l);
    check_l.label.setText("L", dontSendNotification);

    addAndMakeVisible(&check_r);
    check_r.label.setText("R", dontSendNotification);

    attachment_check_l = std::make_unique<ButtonAttachment>(p.get_apvts(), "phase_flip_l", check_l.checkbox);
    attachment_check_r = std::make_unique<ButtonAttachment>(p.get_apvts(), "phase_flip_r", check_r.checkbox);
}

void PhaseFlip::paint(Graphics &g)
{
    ignoreUnused(g);
}

void PhaseFlip::resized()
{
    auto bounds = getLocalBounds();

    label.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(PAD);

    check_l.setBounds(bounds.removeFromLeft((bounds.getWidth() - PAD) / 2));
    bounds.removeFromLeft(PAD);
    check_r.setBounds(bounds);
}