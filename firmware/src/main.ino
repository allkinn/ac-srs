#include "config.h"
#include "state_machine.h"
#include "filtering.h"
#include "sensor_processing.h"
#include "occupancy_logic.h"
#include "utils.h"

unsigned long lastLoopTime = 0;

void setup() {
    Serial.begin(115200);
    initSensors();
    initStateMachine();
    initOccupancyLogic();
    initBuzzer();
}

void loop() {
    unsigned long now = millis();

    // Run tasks on a fixed loop time
    if (now - lastLoopTime >= LOOP_INTERVAL_MS) {
        lastLoopTime = now;

        // 1. Read sensors
        readAllSensors();

        // 2. Process raw LDR signals
        updateLDRFilteredValues();

        // 3. Update state machine (beam break logic)
        updateBeamState();

        // 4. Update occupancy counter
        updateOccupancyLogic();

        // 5. Run reminder logic
        updateACReminder();

        // 6. Logging for debugging
        logDataCSV();
    }
}
