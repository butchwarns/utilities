/*
PluginEditor.h
Copyright (C) 2023 Butch Warns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PLUGIN_EDITOR_H
#define PLUGIN_EDITOR_H

#include "PluginProcessor.h"
#include "gui/colours.h"
#include "gui/Look.h"
#include "typedefs.h"
#include "PluginParameters.h"
#include "gui/WindowContents.h"

class PluginEditor
    : public AudioProcessorEditor,
      public ComponentBoundsConstrainer
{
public:
    explicit PluginEditor(PluginProcessor &, PluginParameters &params);
    ~PluginEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    PluginProcessor &processor_ref;

    Look look;

    WindowContents window_contents;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};

#endif // PLUGIN_EDITOR_H