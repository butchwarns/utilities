#include "Look.h"

void Look::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle slider_style, Slider &slider)
{
    // Background
    g.fillAll(BEIGE);

    // Outline
    g.setColour(juce::Colours::black);
    g.drawRect(slider.getLocalBounds(), 2);

    // Indicator region
    const auto bounds = slider.getLocalBounds();
    g.setColour(GREY);
    g.fillRect(bounds.getX(), bounds.getY(), (int)(sliderPos), bounds.getHeight());
}

void Look::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider)
{
    const auto centre_x = ((float)x + (float)width) / 2.0f;
    const auto centre_y = ((float)x + (float)height) / 2.0f;

    // Knob

    const auto knob_radius = KNOB_DIM / 2.0f;
    Path k;
    k.addEllipse(centre_x - knob_radius, centre_y - knob_radius, KNOB_DIM, KNOB_DIM);

    g.setColour(Colours::white);
    g.fillPath(k);
    g.setColour(GREY);
    g.fillPath(k);

    g.setColour(Colours::black);
    g.strokePath(k, PathStrokeType(2.0f));

    // Pointer

    const auto pointer_radius = POINTER_DIM / 2.0f;
    const auto knob_offset = (width - KNOB_DIM) / 2.0f;
    Path p;
    p.addEllipse(x - pointer_radius, y - pointer_radius, POINTER_DIM, POINTER_DIM);

    AffineTransform pointer_transform;
    pointer_transform = pointer_transform
                            .translated(0.0f, -knob_radius + (pointer_radius + POINTER_OFFSET))
                            .rotated((sliderPos - 0.5f) * (rotaryEndAngle - rotaryStartAngle))
                            .translated(knob_radius + knob_offset, knob_radius + knob_offset);
    p.applyTransform(pointer_transform);

    g.setColour(Colours::white);
    g.fillPath(p);

    g.setColour(Colours::black);
    g.strokePath(p, PathStrokeType(2.0f));
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
        g.setFont(Look::getFontInterBlack(FONT_SIZE));
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

Font Look::getLabelFont(Label &label)
{
    if ((label.getProperties()["gui_class"] == "label") || dynamic_cast<Slider *>(label.getParentComponent()))
    {
        return getFontInterRegular(FONT_SIZE);
    }
    else if (label.getProperties()["gui_class"] == "bold")
    {
        return getFontInterBlack(FONT_SIZE);
    }
    else if (label.getProperties()["gui_class"] == "title")
    {
        return getFontInterBlack(FONT_SIZE_TITLE);
    }
    else
    {
        return label.getFont();
    }
}

Font Look::getFontInterRegular(float height)
{
    static auto font = Font(Typeface::createSystemTypefaceFor(BinaryData::InterRegular_otf, BinaryData::InterRegular_otfSize));
    return font.withHeight(height).withExtraKerningFactor(KERNING_FACTOR);
}

Font Look::getFontInterBlack(float height)
{
    static auto font = Font(Typeface::createSystemTypefaceFor(BinaryData::InterBlack_otf, BinaryData::InterBlack_otfSize));
    return font.withHeight(height).withExtraKerningFactor(KERNING_FACTOR);
}