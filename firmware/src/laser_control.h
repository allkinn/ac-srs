#pragma once
#include <Arduino.h>

// Inisialisasi pin laser & timing
void initLaserPWM();

// Update PWM sesuai day/night mode
void updateLaserPWM();

// Fungsi untuk menentukan apakah saat ini night mode
bool isNightMode();
