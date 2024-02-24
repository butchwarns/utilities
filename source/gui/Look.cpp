/*
Look.cpp
Copyright (C) 2024 Butch Warns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Look.h"
#include "colours.h"
#include "sizes.h"

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

    const auto bounds = slider.getLocalBounds();

    // Line
    g.setColour(juce::Colours::black);
    g.drawLine(0.0f, (float)(bounds.getHeight()) / 2.0f, (float)(bounds.getWidth()), (float)(bounds.getHeight()) / 2.0f, OUTLINE);

    // Thumb

    auto thumb_rect = Rectangle<float>(sliderPos, (float)(bounds.getHeight()) / 2.0f - (float)(SLIDER_HORIZONTAL_THUMB_HEIGHT) / 2.0f, (float)(SLIDER_HORIZONTAL_THUMB_WIDTH), (float)(SLIDER_HORIZONTAL_THUMB_HEIGHT));
    auto slider_pos_relative = (sliderPos - (float)bounds.getX()) / (float)bounds.getWidth();
    thumb_rect.translate(slider_pos_relative * (-(float)SLIDER_HORIZONTAL_THUMB_WIDTH - 2.0f), 0.0f);

    g.setColour(Colours::black);
    g.drawRect(thumb_rect.translated(1.0, 1.0), OUTLINE);
    g.drawRect(thumb_rect.translated(2.0, 2.0), OUTLINE);

    g.setColour(BEIGE);
    g.fillRect(thumb_rect);
    g.setColour(GREY_TRANSPARENT);
    g.fillRect(thumb_rect);

    g.setColour(Colours::black);
    g.drawRect(thumb_rect, OUTLINE);
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

    // Knob (fill and offset outline)

    const float knob_radius = KNOB_DIM / 2.0f;
    Path k;
    k.addEllipse(bounds.toFloat().reduced(OUTLINE));

    // Knob (outline offset)
    Path k_offset = k;
    auto outline_offset = AffineTransform::translation(1.0f, 1.0f);
    k_offset.applyTransform(outline_offset);
    g.setColour(Colours::black);
    g.strokePath(k_offset, PathStrokeType(OUTLINE));
    k_offset.applyTransform(outline_offset);
    g.strokePath(k_offset, PathStrokeType(OUTLINE));

    g.setColour(BEIGE);
    g.fillPath(k);
    g.setColour(GREY_TRANSPARENT);
    g.fillPath(k);

    // Pointer

    Path p;
    const auto pointer_line = Line<float>(0.0f, 0.0f, 0.0f, (float)(POINTER_LENGTH));
    p.addLineSegment(pointer_line, OUTLINE / 2.0f);

    AffineTransform pointer_transform;
    pointer_transform = pointer_transform
                            .translated(0.0f, PAD + OUTLINE + 0.5f)
                            .translated(0.0f, -knob_radius)
                            .rotated((sliderPos - 0.5f) * (rotaryEndAngle - rotaryStartAngle))
                            .translated(knob_radius, knob_radius)
                            .translated((float)(width - height) / 2.0f, 0.0f);
    p.applyTransform(pointer_transform);

    g.setColour(Colours::white);
    g.strokePath(p, PathStrokeType(OUTLINE));

    // Knob (outline)

    g.setColour(Colours::black);
    g.strokePath(k, PathStrokeType(OUTLINE));
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

    if (ticked)
    {
        g.fillAll(GREY_TRANSPARENT);
        g.fillAll(GREY_TRANSPARENT);
        g.drawRect(bounds.getX() + 1, bounds.getY() + 1, bounds.getWidth() - 1, bounds.getHeight() - 1, (int)OUTLINE);
    }
    else
    {
        g.drawRect(bounds.getX(), bounds.getY(), bounds.getWidth() - 1, bounds.getHeight() - 1, (int)OUTLINE);
    }

    // Outline
    g.setColour(juce::Colours::black);
    g.drawRect(bounds, (int)OUTLINE);
}

void Look::drawLabel(Graphics &g, Label &label)
{
    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        g.setColour(label.findColour(Label::textColourId).withMultipliedAlpha(alpha));

        const Font font(getLabelFont(label));
        g.setFont(font);

        const auto bounds = label.getLocalBounds();

        g.drawFittedText(label.getText(), bounds, label.getJustificationType(),
                         jmax(1, (int)((float)bounds.getHeight() / font.getHeight())),
                         1.0f);
    }
}

Font Look::getLabelFont(Label &label)
{
    const auto props = label.getProperties();

    if (props["text_style"] == "bold")
    {
        return getFontInterBold(FONT_SIZE);
    }
    if ((props["text_style"] == "black") || (props["gui_class"] == "title"))
    {
        return getFontInterBlack(FONT_SIZE);
    }
    else if (props["text_style"] == "italic")
    {
        return getFontInterItalic(FONT_SIZE);
    }
    else // Default
    {
        return getFontInterRegular(FONT_SIZE);
    }
}

void Look::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &editor)
{
    ignoreUnused(width, height, editor);

    g.fillAll(GREY_TRANSPARENT);
}

void Look::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &editor)
{
    ignoreUnused(width, height);

    g.setColour(Colours::black);
    g.drawRect(editor.getLocalBounds(), (int)OUTLINE);
}

CaretComponent *Look::createCaretComponent(Component *keyFocusOwner)
{
    auto caret = new CaretComponent(keyFocusOwner);
    caret->setColour(CaretComponent::caretColourId, Colours::black);

    return caret;
}

void Look::drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &box)
{
    ignoreUnused(width, height, buttonX, buttonY, buttonW, buttonH);

    auto bounds = box.getLocalBounds();

    // Background
    g.setColour(BEIGE);
    g.fillRect(bounds);

    // Outline
    g.setColour(Colours::black);
    g.drawRect(bounds, (int)OUTLINE);

    // Pointer

    auto bounds_button = bounds.removeFromLeft(CHECKBOX_DIM);

    g.setColour(GREY_TRANSPARENT);
    g.fillRect(bounds_button);
    if (isButtonDown)
    {
        g.fillRect(bounds_button);
        g.fillRect(bounds_button);
    }

    g.setColour(Colours::black);
    auto font = getFontInterRegular((float)(bounds.getHeight()));
    g.setFont(font);
    g.drawFittedText(String(CharPointer_UTF8("\xE2\x86\x93")), bounds_button, Justification::centred, 1, 1.0f);

    // Outline
    g.setColour(Colours::black);
    g.drawRect(bounds_button, (int)OUTLINE);
}

void Look::positionComboBoxText(ComboBox &box, Label &label)
{
    auto bounds = box.getLocalBounds();
    bounds.removeFromLeft(CHECKBOX_DIM);
    label.setBounds(bounds);
}

void Look::drawPopupMenuItem(Graphics &g, const Rectangle<int> &area,
                             const bool isSeparator, const bool isActive,
                             const bool isHighlighted, const bool isTicked,
                             const bool hasSubMenu, const String &text,
                             const String &shortcutKeyText,
                             const Drawable *icon, const Colour *const textColourToUse)
{
    ignoreUnused(isSeparator, isActive, isTicked, hasSubMenu, shortcutKeyText, icon, textColourToUse);

    // Background
    g.fillAll(BEIGE);
    if (isHighlighted)
    {
        g.fillAll(GREY_TRANSPARENT);
    }

    // Text
    auto font = Look::getFontInterRegular(FONT_SIZE);
    g.setFont(font);
    g.setColour(Colours::black);
    g.drawFittedText(text, area, Justification::centred, 1.0f);

    // Outline
    g.setColour(Colours::black);
    g.drawRect(area, 1.0f);
}

void Look::drawPopupMenuBackground(Graphics &g, int width, int height)
{
    ignoreUnused(width, height);
    g.fillAll(Colours::black);
}
