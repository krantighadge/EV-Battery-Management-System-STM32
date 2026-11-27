
#ifndef BMS_CORE_H
#define BMS_CORE_H

#define BMS_NUM_CELLS 16

typedef enum {
    BMS_TREND_STABLE = 0,
    BMS_TREND_INCREASING,
    BMS_TREND_DECREASING
} BmsTrend;

typedef enum {
    BMS_STATUS_NORMAL = 0,
    BMS_STATUS_IMBALANCE_WARNING
} BmsStatus;

typedef struct {
    float cell_voltage[BMS_NUM_CELLS];
    unsigned int weakest_cell;
    unsigned int strongest_cell;
    float weakest_voltage;
    float strongest_voltage;
    float imbalance_mv;
    float state_of_charge_percent;
    float discharge_rate_c;
    float adaptive_threshold_mv;
    BmsTrend trend;
    BmsStatus status;
    int valid;
} BmsData;

void BMS_Analyze(
    const float cell_voltage[BMS_NUM_CELLS],
    float state_of_charge_percent,
    float discharge_rate_c,
    float previous_imbalance_mv,
    BmsData *result
);

#endif