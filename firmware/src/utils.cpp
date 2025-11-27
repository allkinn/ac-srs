#include "utils.h"

// Clamp nilai antara min dan max
int clamp(int value, int minVal, int maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

// Map dengan clamp otomatis
int mapConstrain(int value, int inMin, int inMax, int outMin, int outMax) {
    int mapped = map(value, inMin, inMax, outMin, outMax);
    return clamp(mapped, outMin, outMax);
}

// Debounce simple untuk digital input
bool debounceRead(int pin, unsigned long debounceDelay) {
    static unsigned long lastDebounceTime = 0;
    static bool lastState = LOW;
    static bool stableState = LOW;

    bool reading = digitalRead(pin);

    if (reading != lastState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != stableState) {
            stableState = reading;
        }
    }

    lastState = reading;
    return stableState;
}
