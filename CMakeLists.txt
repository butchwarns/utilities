# bw_utility CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(bw_utility VERSION 0.1.0)

add_subdirectory(JUCE)                  

juce_add_plugin(BW_UTILITY
    # VERSION ...                       # Set this if the plugin version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "butch_warns"          # Specify the name of the plugin's author
    IS_SYNTH FALSE                      # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE              # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE             # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE   # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE        # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Buwa       # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Util                    # A unique four-character plugin id with exactly one upper-case character
                                        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS VST3                        # The formats to build. Other valid formats are: AAX Unity VST AU AUv3 Standalone
    PRODUCT_NAME "bw_utility")          # The name of the final executable, which can differ from the target name

###############################################################################
# Sources

juce_generate_juce_header(BW_UTILITY)

set(SRC_PLUGIN_BASE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/PluginParameters.cpp)

set(SRC_DSP
        source/dsp/CrossoverFilter.cpp)

set(SRC_BDSP
        BDSP/source/filter/HP1_DCBlock.cpp
        BDSP/source/smoother/SmootherLinear.cpp
        BDSP/source/cv/VoltPerOctave.cpp
        BDSP/source/filter/LP1_RC_TPT.cpp
        BDSP/source/filter/HP1_RC_TPT.cpp
        BDSP/source/filter/LP2_SallenKey_TPT.cpp
        BDSP/source/filter/HP2_SallenKey_TPT.cpp)

set(SRC_GUI_COMPONENTS
        source/gui/components/Spacer.cpp
        source/gui/components/SliderRotary.cpp
        source/gui/components/SliderRotaryLabeled.cpp
        source/gui/components/SliderHorizontal.cpp
        source/gui/components/SliderHorizontalLabeled.cpp
        source/gui/components/CheckboxLabeled.cpp
        source/gui/components/LabelTitle.cpp)

set(SRC_GUI
        ${SRC_GUI_COMPONENTS}
        source/gui/Look.cpp
        source/gui/Header.cpp
        source/gui/Footer.cpp
        source/gui/Channels.cpp
        source/gui/BassMono.cpp
        source/gui/Sliders.cpp
        source/gui/PhaseFlip.cpp
        source/gui/DCBlock.cpp
        source/gui/Tooltip.cpp
        source/gui/WindowContents.cpp)

target_sources(BW_UTILITY
    PRIVATE
        ${SRC_PLUGIN_BASE}
        ${SRC_DSP}
        ${SRC_BDSP}
        ${SRC_GUI})

###############################################################################

target_compile_definitions(BW_UTILITY
    PUBLIC
        JUCE_WEB_BROWSER=0              # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0                 # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0    # If you disable the splashscreen, you either need a valid JUCE license or release under GPLv3
        JUCE_REPORT_APP_USAGE=0)

juce_add_binary_data(BWUtilityBinaryData 
    NAMESPACE 
        BinaryData
    SOURCES
        resources/fonts/Inter-Regular.otf
        resources/fonts/Inter-Italic.otf
        resources/fonts/Inter-Bold.otf
        resources/fonts/Inter-Black.otf)

target_link_libraries(BW_UTILITY
    PRIVATE
        BWUtilityBinaryData
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic") # Position-independent code, needed for linking to binary target on linux