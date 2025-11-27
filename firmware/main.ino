#include "config.h"
#include "sensor_processing.h"
#include "filtering.h"
#include "laser_control.h"
#include "state_machine.h"
#include "occupancy_logic.h"
#include "utils.h"

// Global sensor data (initialized to zero)
LDRSensor sensorA = {0};
LDRSensor sensorB = {0};

// Timing control
unsigned long lastFrameTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("=== Occupancy Counter System ===");
    
    // Initialize modules
    initSensors();
    initLaserPWM();
    initStateMachine();
    initOccupancy();
    
    Serial.println("System initialized. Ready.");
}

void loop() {
    unsigned long currentTime = millis();
    
    // Maintain 50 Hz loop rate
    if (currentTime - lastFrameTime < FRAME_DELAY_MS) {
        return;
    }
    lastFrameTime = currentTime;
    
    // =====================================
    // 1. UPDATE SENSORS
    // =====================================
    updateLDR_A(sensorA);
    updateLDR_B(sensorB);
    
    // =====================================
    // 2. UPDATE LASER PWM (day/night mode)
    // =====================================
    updateLaserPWM();
    
    // =====================================
    // 3. DETERMINE STATE EVENT
    // =====================================
    StateEvent event = FEED_NONE;
    
    if (sensorA.broken && sensorB.broken) {
        event = EVENT_CLEAR_BOTH;
    } 
    else if (sensorA.broken) {
        event = EVENT_BREAK_A;
    } 
    else if (sensorB.broken) {
        event = EVENT_BREAK_B;
    }
    
    // =====================================
    // 4. RUN STATE MACHINE
    // =====================================
    PeopleMovement movement = updateStateMachine(event);
    
    // =====================================
    // 5. UPDATE OCCUPANCY COUNT
    // =====================================
    updateOccupancy(movement);
    
    // =====================================
    // 6. TEMPERATURE CHECK (optional logic)
    // =====================================
    static unsigned long lastTempCheck = 0;
    if (currentTime - lastTempCheck > 5000) {  // every 5 seconds
        float temp = getTemperature();
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.println(" °C");
        
        if (temp < TEMP_COLD_THRESHOLD) {
            Serial.println("Warning: Temperature below threshold!");
        }
        
        lastTempCheck = currentTime;
    }
    
    // =====================================
    // 7. STATUS DISPLAY (optional debug)
    // =====================================
    static unsigned long lastDebug = 0;
    if (currentTime - lastDebug > 1000) {  // every 1 second
        Serial.print("Count: ");
        Serial.print(getCurrentCount());
        Serial.print(" | A:");
        Serial.print(sensorA.broken ? "BREAK" : "OK");
        Serial.print(" | B:");
        Serial.println(sensorB.broken ? "BREAK" : "OK");
        
        lastDebug = currentTime;
    }
}
