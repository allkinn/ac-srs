#include "utils.h"
#include <Arduino.h>

float getTemperature() {
    // TODO: integrate AHT20 later
    return 26.0;
}

void logDataCSV() {
    // Basic CSV format
    Serial.print("filteredA,filteredB,people,temp:");
    Serial.print(",");
    Serial.print("TODO");   // replace w/ real signals if needed
    Serial.println();
}
