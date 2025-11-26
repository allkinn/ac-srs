#include "laser_control.h"
#include "config.h"
#include <Arduino.h>

unsigned long laserTimer = 0;
bool laserState = false;

unsigned long systemStart = 0;

int currentOnTime = LASER_ON_MS_NORMAL;
int currentOffTime = LASER_OFF_MS_NORMAL;

void initLaserControl() {
    pinMode(LASER_A_PIN, OUTPUT);
    pinMode(LASER_B_PIN, OUTPUT);

    digitalWrite(LASER_A_PIN, LOW);
    digitalWrite(LASER_B_PIN, LOW);

    systemStart = millis();
}

bool isNightMode() {
    unsigned long msPassed = millis() - systemStart;
    unsigned long hours = (msPassed / 3600000UL) % 24;

    if (hours >= NIGHT_START_HOUR || hours < DAY_START_HOUR)
        return true;
    return false;
}

void updateLaserPWM() {
    if (isNightMode()) {
        currentOnTime  = LASER_ON_MS_NIGHT;
        currentOffTime = LASER_OFF_MS_NIGHT;
    } else {
        currentOnTime  = LASER_ON_MS_NORMAL;
        currentOffTime = LASER_OFF_MS_NORMAL;
    }

    unsigned long now = millis();

    if (!laserState) {
        if (now - laserTimer >= currentOffTime) {
            laserState = true;
            laserTimer = now;

            digitalWrite(LASER_A_PIN, HIGH);
            digitalWrite(LASER_B_PIN, HIGH);
        }
    } else {
        if (now - laserTimer >= currentOnTime) {
            laserState = false;
            laserTimer = now;

            digitalWrite(LASER_A_PIN, LOW);
            digitalWrite(LASER_B_PIN, LOW);
        }
    }
}
