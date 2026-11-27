
#include <stdio.h>
#include "bms_core.h"

int BatteryModel_GetReading(
    unsigned int profile,
    float output[BMS_NUM_CELLS]
);

unsigned int BatteryModel_GetProfileCount(void);

int main(void) {
    BmsData bms;
    float cell_voltage[BMS_NUM_CELLS];
    float previous_imbalance = 0.0f;

    unsigned int profile;
    unsigned int i;

    printf("\n====================================\n");
    printf("     EV BATTERY MANAGEMENT SYSTEM\n");
    printf("====================================\n");

    for (profile = 0;
         profile < BatteryModel_GetProfileCount();
         profile++) {

        if (!BatteryModel_GetReading(profile, cell_voltage)) {
            printf("Battery model error!\n");
            return 1;
        }

        BMS_Analyze(
            cell_voltage,
            65.0f,
            0.5f,
            previous_imbalance,
            &bms
        );

        printf("\n--- Battery Profile %u ---\n", profile + 1);

        for (i = 0; i < BMS_NUM_CELLS; i++) {
            printf("Cell %u: %.3f V\n",
                   i + 1, cell_voltage[i]);
        }

        printf("Weakest Cell: Cell %u (%.3f V)\n",
               bms.weakest_cell + 1, bms.weakest_voltage);

        printf("Strongest Cell: Cell %u (%.3f V)\n",
               bms.strongest_cell + 1, bms.strongest_voltage);

        printf("Voltage Imbalance: %.2f mV\n",
               bms.imbalance_mv);

        printf("Adaptive Threshold: %.2f mV\n",
               bms.adaptive_threshold_mv);

        printf("SoC: %.1f %%\n", bms.state_of_charge_percent);
        printf("Discharge Rate: %.2f C\n", bms.discharge_rate_c);

        printf("Trend: %s\n",
            bms.trend == BMS_TREND_INCREASING ? "INCREASING" :
            bms.trend == BMS_TREND_DECREASING ? "DECREASING" :
            "STABLE");

        printf("Status: %s\n",
            bms.status == BMS_STATUS_IMBALANCE_WARNING ?
            "IMBALANCE WARNING" : "NORMAL");

        previous_imbalance = bms.imbalance_mv;
    }

    printf("\nSimulation completed.\n");

    return 0;
}