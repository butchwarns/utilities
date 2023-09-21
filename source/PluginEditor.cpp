#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);

    // Set window size
    const juce::Displays::Display *display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    juce::Rectangle<int> user_area = display->userArea;
    juce::Rectangle<int> user_area_scaled = user_area.transformed(juce::AffineTransform::scale(0.25f));
    const int width = user_area_scaled.getWidth();
    const int height = user_area_scaled.getHeight();
    const int dim = width < height ? width : height;
    setSize(dim, 1.5f * dim);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint(juce::Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(25.0f);
    g.drawFittedText("hello bw_utility!", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginEditor::resized()
{
}