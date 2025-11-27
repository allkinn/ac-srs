#include "laser_control.h"
#include "config.h"

void initLaserPWM() {
    pinMode(LASER_A_PIN, OUTPUT);
    pinMode(LASER_B_PIN, OUTPUT);
    
    // Start with day mode (full power)
    analogWrite(LASER_A_PIN, LASER_DAY_PWM);
    analogWrite(LASER_B_PIN, LASER_DAY_PWM);
}

// -----------------------------------------------------
// CEK DAY/NIGHT MODE (berdasarkan ambient light)
// Baca dari LDR_A sebagai reference ambient light
// -----------------------------------------------------
bool isNightMode() {
    int ambientLight = analogRead(LDR_A_PIN);
    
    // Kalau ambient light di bawah threshold → night mode
    return (ambientLight < NIGHT_THRESHOLD);
}

// -----------------------------------------------------
// UPDATE PWM UNTUK KEDUA LASER
// Adjust PWM berdasarkan ambient light condition
// -----------------------------------------------------
void updateLaserPWM() {
    static bool wasNightMode = false;
    bool nightMode = isNightMode();
    
    // Hanya update kalau ada perubahan mode
    if (nightMode != wasNightMode) {
        if (nightMode) {
            // Night mode: kurangi intensitas laser
            analogWrite(LASER_A_PIN, LASER_NIGHT_PWM);
            analogWrite(LASER_B_PIN, LASER_NIGHT_PWM);
        } else {
            // Day mode: full power
            analogWrite(LASER_A_PIN, LASER_DAY_PWM);
            analogWrite(LASER_B_PIN, LASER_DAY_PWM);
        }
        wasNightMode = nightMode;
    }
}
