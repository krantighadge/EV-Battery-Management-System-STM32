
#include <stddef.h>
#include "bms_core.h"

static const float battery_profiles[][BMS_NUM_CELLS] = {
    {3.75f, 3.76f, 3.74f, 3.75f},
    {3.74f, 3.78f, 3.70f, 3.79f},
    {3.72f, 3.82f, 3.65f, 3.88f},
    {3.70f, 3.84f, 3.62f, 3.92f},
    {3.69f, 3.85f, 3.60f, 3.94f}
};

#define PROFILE_COUNT \
    (sizeof(battery_profiles) / sizeof(battery_profiles[0]))

int BatteryModel_GetReading(
    unsigned int profile,
    float output[BMS_NUM_CELLS]
) {
    unsigned int i;

    if (output == NULL || profile >= PROFILE_COUNT) {
        return 0;
    }

    for (i = 0; i < BMS_NUM_CELLS; i++) {
        output[i] = battery_profiles[profile][i];
    }

    return 1;
}

unsigned int BatteryModel_GetProfileCount(void) {
    return (unsigned int)PROFILE_COUNT;
}
