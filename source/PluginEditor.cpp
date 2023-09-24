#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor &p, Apvts &apvts)
    : AudioProcessorEditor(&p), processorRef(p), sliders(apvts), channels(apvts), bass_mono(apvts)
{
    juce::ignoreUnused(processorRef);

    // Get (usable) screen size
    // const juce::Displays::Display *display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    // juce::Rectangle<int> user_area = display->userArea;

    setSize(WIN_WIDTH, WIN_HEIGHT);

    setLookAndFeel(&look);

    addAndMakeVisible(&header);
    addAndMakeVisible(&footer);
    addAndMakeVisible(&sliders);
    addAndMakeVisible(&spacer1);
    addAndMakeVisible(&channels);
    addAndMakeVisible(&spacer2);
    addAndMakeVisible(&bass_mono);
}

void PluginEditor::paint(juce::Graphics &g)
{
    g.fillAll(RED);
}

void PluginEditor::resized()
{
    auto bounds = getLocalBounds();

    header.setBounds(bounds.removeFromTop(HEADER_HEIGHT));
    footer.setBounds(bounds.removeFromBottom(FOOTER_HEIGHT));

    bounds.reduce(PAD, PAD);

    sliders.setBounds(bounds.removeFromTop(SLIDERS_HEIGHT));

    spacer1.setBounds(bounds.removeFromTop(SPACER_HEIGHT));

    channels.setBounds(bounds.removeFromTop(CHANNELS_HEIGHT));

    spacer2.setBounds(bounds.removeFromTop(SPACER_HEIGHT));

    bass_mono.setBounds(bounds.removeFromTop(BASS_MONO_HEIGHT));
}
