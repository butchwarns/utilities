#pragma once

constexpr float OUTLINE = 2.0f;

constexpr float KERNING_FACTOR = 0.1f;

constexpr int PAD = 5;

constexpr int LABEL_HEIGHT = 20;

constexpr int HEADER_HEIGHT = 25;
constexpr int FOOTER_HEIGHT = 25;

constexpr float FONT_SIZE = 14.0f;
constexpr float FONT_SIZE_TITLE = 18.0f;

constexpr int SLIDER_DIM = 50;
constexpr int KNOB_DIM = 40;
constexpr int POINTER_DIM = 8;
constexpr int POINTER_OFFSET = 5;
constexpr int SLIDER_ROTARY_LABELED_HEIGHT = SLIDER_DIM + 2 * LABEL_HEIGHT;

constexpr int SPACER_HEIGHT = 11;

constexpr int CHECKBOX_DIM = 20;

constexpr int CHANNELS_HEIGHT = 70;
constexpr int BASS_MONO_HEIGHT = 90;

// Rotary sliders with label and textbox
constexpr int SLIDERS_HEIGHT = SLIDER_ROTARY_LABELED_HEIGHT;

constexpr int WIN_HEIGHT = HEADER_HEIGHT + FOOTER_HEIGHT + 2 * SPACER_HEIGHT + CHANNELS_HEIGHT + BASS_MONO_HEIGHT + 3 * PAD + SLIDERS_HEIGHT;
constexpr int WIN_WIDTH = 115;