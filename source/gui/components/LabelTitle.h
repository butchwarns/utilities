#pragma once

#include <JuceHeader.h>

class LabelTitle : public Component
{
public:
    LabelTitle();

    Label label;

    void set_text(String text);

private:
    void paint(Graphics &g) override;
    void resized() override;
};
