#pragma once

constexpr float KERNING_FACTOR = 0.1f;

constexpr int PAD = 5;

constexpr int HEADER_HEIGHT = 35;
constexpr int FOOTER_HEIGHT = 35;

constexpr float FONT_SIZE = 11.0f;
constexpr float FONT_SIZE_TITLE = 15.0f;

constexpr int LABEL_HEIGHT = 20;

constexpr int CHECKBOX_DIM = 20;

constexpr int CHANNELS_HEIGHT = 70;
constexpr int BASS_MONO_HEIGHT = 90;

constexpr int SLIDERS_HEIGHT = 90; // Slider with label and textbox
constexpr int SLIDER_WIDTH = 50;

constexpr int SPACER_HEIGHT = 11;
constexpr int SPACER_LINE = 1;

constexpr int WIN_HEIGHT = HEADER_HEIGHT + FOOTER_HEIGHT + 2 * SPACER_HEIGHT + CHANNELS_HEIGHT + BASS_MONO_HEIGHT + 2 * PAD + SLIDERS_HEIGHT;
constexpr int WIN_WIDTH = 115;