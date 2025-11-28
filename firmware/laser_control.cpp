#include "laser_control.h"
#include "config.h"

void initLaserPWM() {
    pinMode(LASER_A_PIN, OUTPUT);
    pinMode(LASER_B_PIN, OUTPUT);
    
    // KY-008 is digital ON/OFF, not PWM
    // Turn on both lasers at startup
    digitalWrite(LASER_A_PIN, HIGH);
    digitalWrite(LASER_B_PIN, HIGH);
}

// -----------------------------------------------------
// CEK DAY/NIGHT MODE
// KY-008 doesn't support dimming, so this returns false
// (always "day mode" = always ON)
// -----------------------------------------------------
bool isNightMode() {
    // KY-008 can't dim, so we just return false
    // Laser always runs at full power
    return false;
}

// -----------------------------------------------------
// UPDATE LASER STATE
// For KY-008: just keep them ON continuously
// No PWM adjustment needed
// -----------------------------------------------------
void updateLaserPWM() {
    // KY-008 doesn't support PWM
    // Lasers are set to HIGH in init and stay ON
    // This function is kept for API compatibility but does nothing
    
    // If you want to implement pulsing for power saving:
    // (Not recommended for counting, but here's the skeleton)
    /*
    static unsigned long lastToggle = 0;
    static bool laserState = true;
    
    if (millis() - lastToggle > 1000) {  // Toggle every 1 second
        laserState = !laserState;
        digitalWrite(LASER_A_PIN, laserState);
        digitalWrite(LASER_B_PIN, laserState);
        lastToggle = millis();
    }
    */
}
