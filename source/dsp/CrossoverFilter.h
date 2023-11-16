
#include "../../BDSP/source/filter/HP1_RC_TPT.h"
#include "../../BDSP/source/filter/LP1_RC_TPT.h"

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

    bdsp::filter::LP1_RC_TPT lp[2];
    bdsp::filter::HP1_RC_TPT hp[2];
};