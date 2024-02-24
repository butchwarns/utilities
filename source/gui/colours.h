/*
colours.h
Copyright (C) 2024 Butch Warns

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

#ifndef COLOURS_H
#define COLOURS_H

#include <JuceHeader.h>

const auto BLACK = Colour(0x40, 0x40, 0x40);
const auto RED_TRANSPARENT = Colour((uint8)0xB3, (uint8)0x00, (uint8)0x00, (uint8)0xCC);
const auto BLUE = Colour(0x73, 0x9D, 0xC3);
const auto BEIGE = Colour(0xD9, 0xD9, 0xD9);
const auto GREY_TRANSPARENT = Colour((uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x44);

#endif // COLOURS_H