#pragma once
#include <Arduino.h>

// Clamp nilai antara min dan max
int clamp(int value, int minVal, int maxVal);

// Map dengan clamp otomatis
int mapConstrain(int value, int inMin, int inMax, int outMin, int outMax);

// Debounce simple untuk digital input (opsional, kalau butuh button)
bool debounceRead(int pin, unsigned long debounceDelay = 50);
