#pragma once

// Plugin works in stereo
constexpr int NUM_CHANNELS = 2;

// Value of time constant found by trial and error
constexpr float SMOOTHING_TIME_DEFAULT = 0.0001f;
constexpr float SMOOTHING_TIME_WIDTH = 0.00006f;