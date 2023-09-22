#include "Look.h"

void Look::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle slider_style, Slider &slider)
{
    // Background
    g.fillAll(BEIGE);

    // Outline
    g.setColour(juce::Colours::black);
    g.drawRect(slider.getLocalBounds(), 2);

    const auto bounds = slider.getLocalBounds();
    g.setColour(juce::Colour(juce::uint8(0x00), juce::uint8(0x00), juce::uint8(0x00), juce::uint8(0x66)));
    g.fillRect(bounds.getX(), bounds.getY(), (int)(sliderPos), bounds.getHeight());
}

void Look::drawTickBox(Graphics &g, Component &component,
                       float x, float y, float w, float h,
                       const bool ticked,
                       const bool isEnabled,
                       const bool shouldDrawButtonAsHighlighted,
                       const bool shouldDrawButtonAsDown)
{
    // Background
    g.fillAll(BEIGE);

    // Outline
    g.setColour(juce::Colours::black);
    g.drawRect(component.getLocalBounds(), 2);

    if (ticked)
    {
        g.drawFittedText("X", component.getLocalBounds(), juce::Justification::centred, 1, 1.0f);
    }
}

void Look::drawLabel(Graphics &g, Label &label)
{
    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        g.setColour(label.findColour(Label::textColourId).withMultipliedAlpha(alpha));

        const Font font(getLabelFont(label));
        g.setFont(font);

        auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
                         jmax(1, (int)((float)textArea.getHeight() / font.getHeight())),
                         label.getMinimumHorizontalScale());
    }
}
