#pragma once
#include <JuceHeader.h>

class LinkButton
{
public:
    LinkButton();

private:
    void paint(Graphics &g) override;
    void resized() override;
};