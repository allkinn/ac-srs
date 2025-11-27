#pragma once
#include <Arduino.h>
#include "config.h" 

// Struktur data pembacaan LDR
struct LDRData {
    int raw;             // nilai ADC mentah
    float filtered;      // nilai setelah low-pass filter
    float baseline;      // baseline laser jangka panjang
    float delta;         // selisih baseline vs filtered
    bool beamBroken;     // status sinar terputus
};

// Inisialisasi LDR
void initSensors();

// Update pembacaan sensor A
void updateLDR_A(LDRSensor &data); 

// Update pembacaan sensor B
void updateLDR_B(LDRSensor &data);

// Baca suhu dari AHT20
float getTemperature();
