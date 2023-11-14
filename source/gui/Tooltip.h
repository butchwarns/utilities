#pragma once

#include <JuceHeader.h>

class Tooltip : public Component
{
public:
    Tooltip();

    void set_tooltip(String msg);

private:
    void paint(Graphics &g) override;
    void resized() override;

    Label label;
};