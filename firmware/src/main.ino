#include <Arduino.h>
#include "config.h"
#include "sensor_processing.h"
#include "laser_control.h"
#include "state_machine.h"
#include "occupancy_logic.h"
#include "utils.h"

// ------------------------------------
// Global LDR states (A & B)
// ------------------------------------
LDRData ldrA = {0, 0, 0, 0, false};
LDRData ldrB = {0, 0, 0, 0, false};

// Timestamp loop control
unsigned long lastLoop = 0;

void setup() {
    Serial.begin(115200);
    delay(200);

    initLaserPWM();
    initSensors();
    initStateMachine();
    initOccupancy();

    Serial.println("AC-SRS system initialized.");
}

void loop() {
    unsigned long now = millis();
    if (now - lastLoop < LOOP_INTERVAL_MS) return;
    lastLoop = now;

    // ------------------------------------
    // Update laser PWM (day/night logic)
    // ------------------------------------
    updateLaserPWM();

    // ------------------------------------
    // Update both LDRs
    // ------------------------------------
    updateLDR_A(ldrA);
    updateLDR_B(ldrB);

    // ------------------------------------
    // Feed LDR event flags to state machine
    // ------------------------------------
    StateEvent event = FEED_NONE;

    if (ldrA.beamBroken) event = EVENT_BREAK_A;
    else if (ldrB.beamBroken) event = EVENT_BREAK_B;
    else event = EVENT_CLEAR_BOTH;

    PeopleMovement movement = updateStateMachine(event);

    // ------------------------------------
    // Counter logic
    // ------------------------------------
    if (movement == MOVEMENT_IN) {
        incrementPeople();
    } 
    else if (movement == MOVEMENT_OUT) {
        decrementPeople();
    }

    int people = getPeopleCount();

    // ------------------------------------
    // Temperature logic
    // ------------------------------------
    float temp = getTemperature();

    // Jika ruangan kosong + suhu dingin → AC reminder
    if (people == 0 && temp < TEMP_COLD_THRESHOLD) {
        buzzWarning();
    }

    // ------------------------------------
    // DEBUG OUTPUT
    // ------------------------------------
    Serial.print("A_raw:");      Serial.print(ldrA.raw);
    Serial.print(" A_f:");       Serial.print(ldrA.filtered);
    Serial.print(" A_base:");    Serial.print(ldrA.baseline);
    Serial.print(" A_d:");       Serial.print(ldrA.delta);
    Serial.print(" A_brk:");     Serial.print(ldrA.beamBroken);

    Serial.print(" | B_raw:");   Serial.print(ldrB.raw);
    Serial.print(" B_f:");       Serial.print(ldrB.filtered);
    Serial.print(" B_base:");    Serial.print(ldrB.baseline);
    Serial.print(" B_d:");       Serial.print(ldrB.delta);
    Serial.print(" B_brk:");     Serial.print(ldrB.beamBroken);

    Serial.print(" | People: "); Serial.print(people);
    Serial.print(" Temp: ");     Serial.println(temp);
}
