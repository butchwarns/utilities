#include "CrossoverFilter.h"

CrossoverFilter::CrossoverFilter()
    : sample_rate(0.0)
{
    for (int i = 0; i < 2; ++i)
    {
        lp[i].set_q(0.0);
        hp[i].set_q(0.0);
    }
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
    const double cutoff_prewarped = bdsp::mappings::prewarp(cutoff, sample_rate);
    for (int i = 0; i < 2; ++i)
    {
        // Set equal cutoff for -6dB attenuation at crossover point
        lp[i].set_cutoff(cutoff_prewarped);
        hp[i].set_cutoff(cutoff_prewarped);
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
    CrossoverFilterOutput out = {lo, -1.0 * hi};

    return out;
}