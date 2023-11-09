#pragma once

constexpr float OUTLINE = 2.0f;

constexpr float FONT_SIZE = 14.0f;
constexpr float FONT_SIZE_TITLE = 18.0f;
constexpr float KERNING_FACTOR = 0.1f;

constexpr int PAD = 5;

constexpr int LABEL_HEIGHT = 20;

constexpr int COMBOBOX_HEIGHT = LABEL_HEIGHT;

// SliderRotary
constexpr int KNOB_DIM = 50;
constexpr int POINTER_DIM = 9;
constexpr int POINTER_OFFSET = PAD;

// SliderRotaryLabeled
constexpr int SLIDER_ROTARY_HEIGHT = KNOB_DIM + LABEL_HEIGHT;
constexpr int SLIDER_ROTARY_LABELED_HEIGHT = SLIDER_ROTARY_HEIGHT + LABEL_HEIGHT;

// SliderHorizontal
constexpr int SLIDER_HORIZONTAL_HEIGHT = LABEL_HEIGHT;

// SliderHorizontalLabeled
constexpr int SLIDER_HORIZONTAL_LABELED_HEIGHT = SLIDER_HORIZONTAL_HEIGHT + LABEL_HEIGHT;

// CheckboxLabeled
constexpr int CHECKBOX_DIM = 20;
constexpr int CHECKBOX_LABELED_HEIGHT = CHECKBOX_DIM;

// Spacer
constexpr int SPACER_DIM = 11; // Width for vertical spacers, height for horizonal ones

// Header
constexpr int HEADER_HEIGHT = 25;
// Footer
constexpr int FOOTER_HEIGHT = 25;

// PhaseFlip
constexpr int PHASE_FLIP_HEIGHT = LABEL_HEIGHT + PAD + CHECKBOX_LABELED_HEIGHT;

// Channels
constexpr int CHANNELS_HEIGHT = LABEL_HEIGHT + PAD + COMBOBOX_HEIGHT + PAD + CHECKBOX_LABELED_HEIGHT;

// BassMono
constexpr int BASS_MONO_HEIGHT = LABEL_HEIGHT + PAD + CHECKBOX_LABELED_HEIGHT + SLIDER_HORIZONTAL_LABELED_HEIGHT;

// Sliders
constexpr int SLIDERS_HEIGHT = 3 * SLIDER_ROTARY_LABELED_HEIGHT;

// DCBlock
constexpr int DC_BLOCK_HEIGHT = LABEL_HEIGHT + PAD + CHECKBOX_LABELED_HEIGHT;

// Plugin window
constexpr int COLUMN1_WIDTH = 105;
constexpr int COLUMN2_WIDTH = 65;
constexpr int COLUMN1_HEIGHT = 3 * SPACER_DIM + PHASE_FLIP_HEIGHT + CHANNELS_HEIGHT + BASS_MONO_HEIGHT + DC_BLOCK_HEIGHT;
constexpr int COLUMN2_HEIGHT = SLIDERS_HEIGHT;
constexpr int WIN_HEIGHT = HEADER_HEIGHT + FOOTER_HEIGHT + 2 * PAD + COLUMN1_HEIGHT;
constexpr int WIN_WIDTH = COLUMN1_WIDTH + SPACER_DIM + COLUMN2_WIDTH + 2 * PAD;