/*
CrossoverFilter.cpp
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

#include "CrossoverFilter.h"

CrossoverFilter::CrossoverFilter()
    : sample_rate(0.0)
{
}

void CrossoverFilter::reset(double _sample_rate)
{
    sample_rate = _sample_rate;

    for (int i = 0; i < 2; ++i)
    {
        lp[i].reset(_sample_rate);
        hp[i].reset(_sample_rate);
    }
}

void CrossoverFilter::set_cutoff(double cutoff)
{
    for (int i = 0; i < 2; ++i)
    {
        // Set equal cutoff for -6dB attenuation at crossover point
        lp[i].set_cutoff_prewarp(cutoff);
        hp[i].set_cutoff_prewarp(cutoff);
    }
}

CrossoverFilterOutput CrossoverFilter::process(double x)
{
    double lo = x;
    double hi = x;

    for (int i = 0; i < 2; ++i)
    {
        lo = lp[i].process(lo);
        hi = hp[i].process(hi);
    }

    // Invert high-pass output for phase correction
    CrossoverFilterOutput out = {lo, -hi};

    return out;
}