#include "occupancy_logic.h"
#include "state_machine.h"
#include "config.h"
#include "utils.h"
#include <Arduino.h>

int peopleCount = 0;

void initOccupancyLogic() {}

void initBuzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void updateOccupancyLogic() {
    if (beamState == A_THEN_B) {
        peopleCount++;
        beamState = IDLE;
    }

    if (beamState == B_THEN_A) {
        peopleCount = max(0, peopleCount - 1);
        beamState = IDLE;
    }
}

void updateACReminder() {
    float t = getTemperature();

    if (peopleCount == 0 && t < AC_TEMP_THRESHOLD)
        digitalWrite(BUZZER_PIN, HIGH);
    else
        digitalWrite(BUZZER_PIN, LOW);
}
