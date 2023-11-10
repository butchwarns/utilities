#pragma once

#include <JuceHeader.h>
#include "colours.h"
#include "sizes.h"

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
