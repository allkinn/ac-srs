#include "sensor_processing.h"
#include "filtering.h"
#include "config.h"

int baselineA = 0;
int baselineB = 0;

void initSensors() {
    baselineA = analogRead(LDR_A_PIN);
    baselineB = analogRead(LDR_B_PIN);
}

void readAllSensors() {
    // filtering handles actual sampling
}

bool isLDR_ABroken() {
    return (baselineA - filteredA) > BREAK_THRESHOLD;
}

bool isLDR_BBroken() {
    return (baselineB - filteredB) > BREAK_THRESHOLD;
}
