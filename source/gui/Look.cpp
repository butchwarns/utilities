#include "Look.h"

Font Look::getFontInterRegular(float height)
{
    static auto font = Font(Typeface::createSystemTypefaceFor(BinaryData::InterRegular_otf, BinaryData::InterRegular_otfSize));
    return font.withHeight(height);
}

Font Look::getFontInterItalic(float height)
{
    static auto font = Font(Typeface::createSystemTypefaceFor(BinaryData::InterItalic_otf, BinaryData::InterItalic_otfSize));
    return font.withHeight(height);
}

Font Look::getFontInterBold(float height)
{
    static auto font = Font(Typeface::createSystemTypefaceFor(BinaryData::InterBold_otf, BinaryData::InterBold_otfSize));
    return font.withHeight(height);
}

Font Look::getFontInterBlack(float height)
{
    static auto font = Font(Typeface::createSystemTypefaceFor(BinaryData::InterBlack_otf, BinaryData::InterBlack_otfSize));
    return font.withHeight(height).withExtraKerningFactor(KERNING_FACTOR);
}

void Look::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle slider_style, Slider &slider)
{
    ignoreUnused(x, y, width, height, minSliderPos, maxSliderPos, slider_style);

    // Background
    g.fillAll(BEIGE);

    // Indicator region
    const auto bounds = slider.getLocalBounds();
    g.setColour(GREY_TRANSPARENT);
    g.fillRect(bounds.getX(), bounds.getY(), (int)(sliderPos), bounds.getHeight());

    // Outline
    g.setColour(juce::Colours::black);
    g.drawRect(slider.getLocalBounds(), 2);
}

void Look::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider)
{
    ignoreUnused(x, y);

    auto bounds = slider.getLocalBounds().reduced(PAD);

    // Reduce bounds to square if rectangular
    width = bounds.getWidth();
    height = bounds.getHeight();
    if (width > height)
    {
        bounds.setWidth(height);
        bounds.setX((int)((float)(bounds.getX()) + (float)(width - height) / 2.0f));
    }
    else
    {
        bounds.setHeight(width);
        bounds.setY((int)((float)(bounds.getY()) + (float)(height - width) / 2.0f));
    }

    // Knob

    const float knob_radius = KNOB_DIM / 2.0f;
    Path k;
    k.addEllipse(bounds.toFloat().reduced(OUTLINE));

    g.setColour(BEIGE);
    g.fillPath(k);
    g.setColour(GREY_TRANSPARENT);
    g.fillPath(k);

    g.setColour(Colours::black);
    g.strokePath(k, PathStrokeType(OUTLINE));

    // Pointer

    const float pointer_radius = POINTER_DIM / 2.0f;
    Path p;
    p.addEllipse(Rectangle<float>(-pointer_radius, -pointer_radius, POINTER_DIM, POINTER_DIM).reduced(OUTLINE));

    AffineTransform pointer_transform;
    pointer_transform = pointer_transform
                            .translated(0.0f, -knob_radius + POINTER_DIM + POINTER_OFFSET)
                            .rotated((sliderPos - 0.5f) * (rotaryEndAngle - rotaryStartAngle))
                            .translated(knob_radius, knob_radius)
                            .translated((float)(width - height) / 2.0f, 0.0f);
    p.applyTransform(pointer_transform);

    g.setColour(Colours::white);
    g.fillPath(p);

    g.setColour(Colours::black);
    g.strokePath(p, PathStrokeType(OUTLINE));
}

void Look::drawTickBox(Graphics &g, Component &component,
                       float x, float y, float w, float h,
                       const bool ticked,
                       const bool isEnabled,
                       const bool shouldDrawButtonAsHighlighted,
                       const bool shouldDrawButtonAsDown)
{
    ignoreUnused(x, y, w, h, isEnabled, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    auto bounds = component.getLocalBounds();

    // Background
    g.fillAll(BEIGE);

    // Outline
    g.setColour(juce::Colours::black);
    g.drawRect(bounds, (int)OUTLINE);

    if (ticked)
    {
        g.setColour(Colours::black);
        g.setFont(Look::getFontInterRegular(FONT_SIZE));
        g.drawFittedText("X", bounds, juce::Justification::centred, 1, 1.0f);
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

        // auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());
        const auto bounds = label.getLocalBounds();

        g.drawFittedText(label.getText(), bounds, label.getJustificationType(),
                         jmax(1, (int)((float)bounds.getHeight() / font.getHeight())),
                         1.0f);
    }
}

Font Look::getLabelFont(Label &label)
{
    if (label.getProperties()["gui_class"] == "bold")
    {
        return getFontInterBold(FONT_SIZE);
    }
    if (label.getProperties()["gui_class"] == "black")
    {
        return getFontInterBlack(FONT_SIZE);
    }
    else if (label.getProperties()["gui_class"] == "italic")
    {
        return getFontInterItalic(FONT_SIZE);
    }
    else if (label.getProperties()["gui_class"] == "title")
    {
        return getFontInterBlack(FONT_SIZE_TITLE);
    }
    else
    {
        return getFontInterRegular(FONT_SIZE);
    }
}

void Look::drawComboBox(Graphics &g, int width, int height, bool, int, int, int, int, ComboBox &box)
{
    ignoreUnused(width, height);

    auto bounds = box.getLocalBounds();

    g.setColour(BEIGE);
    g.fillRect(bounds);

    g.setColour(Colours::black);
    g.drawRect(bounds, 2.0f);
}

void Look::positionComboBoxText(ComboBox &box, Label &label)
{
    label.setBounds(box.getLocalBounds());
}

void Look::drawPopupMenuItem(Graphics &g, const Rectangle<int> &area,
                             const bool isSeparator, const bool isActive,
                             const bool isHighlighted, const bool isTicked,
                             const bool hasSubMenu, const String &text,
                             const String &shortcutKeyText,
                             const Drawable *icon, const Colour *const textColourToUse)
{
    ignoreUnused(isSeparator, isActive, isTicked, hasSubMenu, shortcutKeyText, icon, textColourToUse);

    g.setColour(BEIGE);
    g.fillRect(area);
    if (isHighlighted)
    {
        g.setColour(GREY_TRANSPARENT);
        g.fillRect(area);
    }
    g.setColour(Colours::black);
    g.drawRect(area, (int)OUTLINE);

    auto font = Look::getFontInterRegular(FONT_SIZE);
    g.setFont(font);
    g.setColour(Colours::black);
    g.drawFittedText(text, area, Justification::centred, 1.0f);
}

void Look::drawPopupMenuBackground(Graphics &g, int width, int height)
{
    ignoreUnused(width, height);
    g.fillAll(Colours::black);
}
