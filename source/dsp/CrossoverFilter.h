/*
CrossoverFilter.h
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

#ifndef CROSSOVER_FILTER_H
#define CROSSOVER_FILTER_H

#include "../../BDSP/source/filter/LP2_SallenKey_TPT.h"

struct CrossoverFilterOutput
{
    double lo;
    double hi;
};

class CrossoverFilter
{
public:
    CrossoverFilter();
    ~CrossoverFilter() = default;

    void reset(double sample_rate);

    void set_cutoff(double sample_rate);

    CrossoverFilterOutput process(double x);

private:
    double sample_rate;

    bdsp::filter::LP2_SallenKey_TPT lp;
};

#endif // CROSSOVER_FILTER_H