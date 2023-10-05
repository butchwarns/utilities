#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor &p, PluginParameters &params)
    : AudioProcessorEditor(&p), processor_ref(p), window_contents(params)
{
    juce::ignoreUnused(processor_ref);

    // Get (usable) screen size
    // const juce::Displays::Display *display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    // juce::Rectangle<int> user_area = display->userArea;

    setSize((int)processor_ref.get_saved_window_width(), (int)processor_ref.get_saved_window_height());
    setResizable(false, true);

    addAndMakeVisible(&window_contents);

    setLookAndFeel(&look);

    setFixedAspectRatio((float)WIN_WIDTH / (float)WIN_HEIGHT);
    setConstrainer(this);
}

void PluginEditor::paint(juce::Graphics &g)
{
    g.fillAll(BLUE);
}

void PluginEditor::resized()
{
    const float window_scale = (float)getWidth() / (float)WIN_WIDTH;

    window_contents.setBounds(0, 0, WIN_WIDTH, WIN_HEIGHT);
    window_contents.setTransform(AffineTransform::scale(window_scale));

    processor_ref.set_saved_window_size((float)getWidth(), (float)getHeight());
}