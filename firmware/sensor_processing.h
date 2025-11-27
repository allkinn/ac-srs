#pragma once
#include <Arduino.h>
#include "config.h"

// Inisialisasi LDR
void initSensors();

// Update pembacaan sensor A
void updateLDR_A(LDRSensor &data);

// Update pembacaan sensor B
void updateLDR_B(LDRSensor &data);

// Baca suhu dari AHT20 (real sensor)
float getTemperature();
