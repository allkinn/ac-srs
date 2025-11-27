#include <Arduino.h>
#include "config.h"

#include "filtering.h"
#include "sensor_processing.h"
#include "state_machine.h"
#include "occupancy_logic.h"
#include "utils.h"
#include "laser_control.h"

void setup() {
    Serial.begin(115200);

    initFilters();
    initSensors();
    initLaserControl();

    Serial.println("AC-SRS Firmware Boot OK");
}

void loop() {
    readRawSensors();
    processSensors();
    updateLaserControl();

    updateStateMachine();
    applyOccupancyLogic();

    delay(FRAME_DELAY_MS);
}
