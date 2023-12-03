/*
Look.h
Copyright (C) 2023 Butch Warns

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

#ifndef LOOK_H
#define LOOK_H

#include <JuceHeader.h>

class Look : public juce::LookAndFeel_V4
{
public:
    Look() = default;

    static Font getFontInterRegular(float height);
    static Font getFontInterItalic(float height);
    static Font getFontInterBold(float height);
    static Font getFontInterBlack(float height);

private:
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle slider_style, Slider &slider) override;

    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider) override;

    void drawTickBox(Graphics &g, Component &component,
                     float x, float y, float w, float h,
                     const bool ticked,
                     const bool isEnabled,
                     const bool shouldDrawButtonAsHighlighted,
                     const bool shouldDrawButtonAsDown) override;

    void drawLabel(Graphics &g, Label &label) override;
    Font getLabelFont(Label &label) override;

    void fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &editor) override;
    void drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &editor) override;
    CaretComponent *createCaretComponent(Component *keyFocusOwner) override;

    void drawComboBox(Graphics &g, int width, int height, bool, int, int, int, int, ComboBox &box) override;
    void positionComboBoxText(ComboBox &box, Label &label) override;
    void drawPopupMenuItem(Graphics &g, const Rectangle<int> &area,
                           const bool isSeparator, const bool isActive,
                           const bool isHighlighted, const bool isTicked,
                           const bool hasSubMenu, const String &text,
                           const String &shortcutKeyText,
                           const Drawable *icon, const Colour *const textColourToUse) override;
    void drawPopupMenuBackground(Graphics &g, int width, int height) override;
};

#endif // LOOK_H