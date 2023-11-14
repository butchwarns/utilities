#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor &p, PluginParameters &params)
    : AudioProcessorEditor(&p), processor_ref(p), window_contents(params)
{
    // // Get (usable) screen size, might be useful later..
    // const juce::Displays::Display *display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    // juce::Rectangle<int> user_area = display->userArea;

    const auto width_saved = (int)processor_ref.get_saved_window_width();
    const auto height_saved = (int)processor_ref.get_saved_window_height();
    setSize(width_saved, height_saved);

    // Make window resizable only with corner resizer, not by host
    setResizable(false, true);

    // Constrain aspect ratio
    setFixedAspectRatio((float)WIN_WIDTH / (float)WIN_HEIGHT);
    setMinimumSize(WIN_WIDTH / 2, WIN_HEIGHT / 2);
    setConstrainer(this);

    setLookAndFeel(&look);

    addAndMakeVisible(&window_contents);

    startTimer(200); // Start tooltip update timer
}

PluginEditor::~PluginEditor()
{
    setLookAndFeel(nullptr);
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

    processor_ref.set_saved_window_size(getWidth(), getHeight());
}

void PluginEditor::timerCallback()
{
    Component *const component_under_mouse = Desktop::getInstance().getMainMouseSource().getComponentUnderMouse();
    auto *const tooltip_client = dynamic_cast<TooltipClient *>(component_under_mouse);

    String tooltip_msg;
    if ((tooltip_client != nullptr) && !(component_under_mouse->isMouseButtonDown() || component_under_mouse->isCurrentlyBlockedByAnotherModalComponent()))
    {
        tooltip_msg = tooltip_client->getTooltip();
    }

    window_contents.set_tooltip(tooltip_msg);
}