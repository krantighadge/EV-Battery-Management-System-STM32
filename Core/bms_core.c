
#include <stddef.h>
#include "bms_core.h"

#define BASE_THRESHOLD_MV       30.0f
#define SOC_FACTOR_MV           0.20f
#define DISCHARGE_FACTOR_MV     5.0f
#define MIN_THRESHOLD_MV        20.0f
#define MAX_THRESHOLD_MV        100.0f
#define TREND_DEADBAND_MV       1.0f

void BMS_Analyze(
    const float cell_voltage[BMS_NUM_CELLS],
    float state_of_charge_percent,
    float discharge_rate_c,
    float previous_imbalance_mv,
    BmsData *result
) {
    unsigned int i;
    float threshold;

    if (cell_voltage == NULL || result == NULL) {
        return;
    }

    result->weakest_cell = 0;
    result->strongest_cell = 0;
    result->weakest_voltage = cell_voltage[0];
    result->strongest_voltage = cell_voltage[0];

    for (i = 1; i < BMS_NUM_CELLS; i++) {
        if (cell_voltage[i] < result->weakest_voltage) {
            result->weakest_voltage = cell_voltage[i];
            result->weakest_cell = i;
        }

        if (cell_voltage[i] > result->strongest_voltage) {
            result->strongest_voltage = cell_voltage[i];
            result->strongest_cell = i;
        }
    }

    result->imbalance_mv =
        (result->strongest_voltage - result->weakest_voltage) * 1000.0f;

    if (state_of_charge_percent < 0.0f)
        state_of_charge_percent = 0.0f;
    if (state_of_charge_percent > 100.0f)
        state_of_charge_percent = 100.0f;
    if (discharge_rate_c < 0.0f)
        discharge_rate_c = 0.0f;

    result->state_of_charge_percent = state_of_charge_percent;
    result->discharge_rate_c = discharge_rate_c;

    threshold = BASE_THRESHOLD_MV
        + SOC_FACTOR_MV * (100.0f - state_of_charge_percent)
        + DISCHARGE_FACTOR_MV * discharge_rate_c;

    if (threshold < MIN_THRESHOLD_MV)
        threshold = MIN_THRESHOLD_MV;
    if (threshold > MAX_THRESHOLD_MV)
        threshold = MAX_THRESHOLD_MV;

    result->adaptive_threshold_mv = threshold;

    if (result->imbalance_mv >
        previous_imbalance_mv + TREND_DEADBAND_MV) {
        result->trend = BMS_TREND_INCREASING;
    }
    else if (result->imbalance_mv <
             previous_imbalance_mv - TREND_DEADBAND_MV) {
        result->trend = BMS_TREND_DECREASING;
    }
    else {
        result->trend = BMS_TREND_STABLE;
    }

    if (result->imbalance_mv > threshold) {
        result->status = BMS_STATUS_IMBALANCE_WARNING;
    }
    else {
        result->status = BMS_STATUS_NORMAL;
    }

    result->valid = 1;
}