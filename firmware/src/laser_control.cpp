#include "laser_control.h"
#include "config.h"
#include "utils.h"

// Timing internal
static unsigned long lastToggleTime = 0;

// Mode PWM
static bool laserOn = false;

// ON/OFF timing aktif sekarang
static unsigned long currentOnTime  = LASER_ON_MS_NORMAL;
static unsigned long currentOffTime = LASER_OFF_MS_NORMAL;

void initLaserPWM() {
    pinMode(LASER_A_PIN, OUTPUT);
    pinMode(LASER_B_PIN, OUTPUT);

    digitalWrite(LASER_A_PIN, LOW);
    digitalWrite(LASER_B_PIN, LOW);

    lastToggleTime = millis();
}


// -----------------------------------------------------
// CEK DAY/NIGHT MODE (berdasarkan jam lokal)
// -----------------------------------------------------
bool isNightMode() {
    int hour = getCurrentHour();

    // Jam malam: >= NIGHT_START_HOUR atau < NIGHT_END_HOUR
    if (hour >= NIGHT_START_HOUR || hour < NIGHT_END_HOUR) {
        return true;
    } 
    return false;
}


// -----------------------------------------------------
// UPDATE PWM UNTUK KEDUA LASER
// Tanpa delay, non-blocking, aman di loop 50 Hz
// -----------------------------------------------------
void updateLaserPWM() {
    unsigned long now = millis();

    // Tentukan ON/OFF time berdasar mode
    if (isNightMode()) {
        currentOnTime  = LASER_ON_MS_NIGHT;
        currentOffTime = LASER_OFF_MS_NIGHT;
    } else {
        currentOnTime  = LASER_ON_MS_NORMAL;
        currentOffTime = LASER_OFF_MS_NORMAL;
    }

    // Hitung berapa lama telah berjalan
    unsigned long elapsed = now - lastToggleTime;

    if (laserOn) {
        // Kalau sedang ON dan sudah melewati ON-time → matikan
        if (elapsed >= currentOnTime) {
            laserOn = false;
            digitalWrite(LASER_A_PIN, LOW);
            digitalWrite(LASER_B_PIN, LOW);
            lastToggleTime = now;
        }
    } else {
        // Kalau sedang OFF dan sudah melewati OFF-time → hidupkan
        if (elapsed >= currentOffTime) {
            laserOn = true;
            digitalWrite(LASER_A_PIN, HIGH);
            digitalWrite(LASER_B_PIN, HIGH);
            lastToggleTime = now;
        }
    }
}
