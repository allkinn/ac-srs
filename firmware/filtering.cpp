#include "filtering.h"
#include "config.h"

// ----------------------------------------------
// Low-Pass Filter (IIR 1st-order)
// filtered = prev * (1 - α) + raw * α
// ----------------------------------------------
float lowPassFilter(float raw, float prevFiltered) {
    return prevFiltered * (1.0f - FILTER_ALPHA) + raw * FILTER_ALPHA;
}


// ----------------------------------------------
// Baseline Drift Compensation
// baseline = baseline * (1 - α) + filtered * α
// ----------------------------------------------
float updateBaseline(float prevBaseline, float filteredValue) {
    return prevBaseline * (1.0f - BASELINE_ALPHA) + filteredValue * BASELINE_ALPHA;
}
