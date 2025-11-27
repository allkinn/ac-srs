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
// CEK DAY/NIGHT MODE
// -----------------------------------------------------
bool isNightMode() {
    #if NIGHT_MODE_AUTO
        // Pakai LDR tambahan khusus ambient light (A2)
        int ambientLight = analogRead(LDR_AMBIENT_PIN);
        return (ambientLight < NIGHT_THRESHOLD);
    #else
        // Hardcode: selalu day mode (laser full power)
        return false;
    #endif
}

// -----------------------------------------------------
// UPDATE PWM UNTUK KEDUA LASER
// Adjust PWM berdasarkan ambient light condition
// -----------------------------------------------------
void updateLaserPWM() {
    static bool wasNightMode = false;
    bool nightMode = isNightMode();
    
    // Hanya update kalau ada perubahan mode (hemat CPU)
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
