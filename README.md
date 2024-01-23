# bw_utility

[![Integration Pipeline](https://github.com/butchwarns/bw_utility/actions/workflows/integrate.yaml/badge.svg)](https://github.com/butchwarns/bw_utility/actions/workflows/integrate.yaml)
[![Release Pipeline](https://github.com/butchwarns/bw_utility/actions/workflows/release.yaml/badge.svg)](https://github.com/butchwarns/bw_utility/actions/workflows/release.yaml)

<img src='/images/bw_utility-v_0_1_1.jpg' width='200' alt="bw_utility v0.1.1 user interface">

## Description
The *bw_utility* plugin is a simple VST3/AU utility tool for macOS.

## Project status
Functional work in progress. (I do intend to add more features and create installers for Linux/Windows sometime in the future!)

## Features
- PHASE FLIP - Inverts polarity of selected channel.
- CHANNELS - Selects output channel routing. Options are: STEREO, LEFT, RIGHT, SWAPPED.
- BASS MONO - Makes bass band strictly mono. Bandwidth can be set through slider.
- DC BLOCK - Filters DC offsets from input signal.
- WIDTH - Controls stereo width. Range: 0%-400%.
- VOLUME - Simple volume control. Lowest setting mutes. Higher settings amplify the signal.
- PAN - Controls left-right panning.
  
## Installation
Currently only _macOS_ is supported. Installers can be downloaded in the [releases](https://github.com/butchwarns/bw_utility/releases) section.

If you are savvy with JUCE/C++, you can build the plugin for any operating system using CMake:  
Clone the repo, populate submodules, and run `build.sh release`. The plugin should be automatically user-installed.

## License
Project source code is licensed under GPLv3. The "Inter" font family is licensed under OFL.
External dependencies have their own licensing (see the corresponding repositories).

Copyright © 2024 Butch Warns
