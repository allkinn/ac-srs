#pragma once

// =============================
// Loop timing
// =============================
#define LOOP_INTERVAL_MS 20      // 50 Hz

// =============================
// PWM — Day Mode (editable)
// =============================
#define LASER_ON_MS_NORMAL   4      // <-- EDIT HERE
#define LASER_OFF_MS_NORMAL 16      // <-- EDIT HERE

// =============================
// PWM — Night Mode (editable)
// =============================
#define LASER_ON_MS_NIGHT    2      // <-- EDIT HERE
#define LASER_OFF_MS_NIGHT  98      // <-- EDIT HERE

// =============================
// Day/Night boundary (simulated)
// =============================
#define DAY_START_HOUR     6
#define NIGHT_START_HOUR  18

// =============================
// Pins
// =============================
#define LDR_A_PIN A0
#define LDR_B_PIN A1

#define LASER_A_PIN 5
#define LASER_B_PIN 6

#define BUZZER_PIN 9

// =============================
// Threshold analog (editable)
// =============================
#define BREAK_THRESHOLD 12           // <-- EDIT HERE
#define BASELINE_UPDATE_RATE 0.01

// =============================
// Temperature
// =============================
#define AC_TEMP_THRESHOLD 25.0f
