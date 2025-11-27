#pragma once

#define LASER_DAY_PWM      255
#define LASER_NIGHT_PWM    180
#define NIGHT_THRESHOLD    50

// ==========================================
// PIN ASSIGNMENT
// ==========================================
#define LASER_A_PIN            5
#define LASER_B_PIN            6

#define LDR_A_PIN              A0
#define LDR_B_PIN              A1

#define BUZZER_PIN             9

// ==========================================
// FILTERING & BASELINE ADAPTATION
// ==========================================
// FILTER_ALPHA: 0.0 → no filter, 1.0 → completely smooth
// BASELINE_ALPHA: adaptasi baseline jangka panjang (laser drift)
#define FILTER_ALPHA           0.10f      // smoothing LDR
#define BASELINE_ALPHA         0.001f     // baseline drift tracking

// ==========================================
// THRESHOLDS (with hysteresis)
// ==========================================
// THRESHOLD_DROP: perbedaan intensitas saat sinar terputus
// THRESHOLD_RECOVERY: threshold balik supaya gak bouncing
#define THRESHOLD_DROP         80         // tanda: wajib kalibrasi real
#define THRESHOLD_RECOVERY     40         // tanda: histeresis kembali aman

// ==========================================
// OCCUPANCY CONFIG
// ==========================================
// Safety cap mencegah overflow counter kalau sensor glitch
#define MAX_PEOPLE_COUNT       50

// ==========================================
// TEMPERATURE CONFIG
// ==========================================
// Threshold suhu ruangan yang dianggap “dingin” (AC hidup)
#define TEMP_COLD_THRESHOLD    23.5f

// ==========================================
// AHT20 CONFIG
// ==========================================
#define AHT20_I2C_ADDR         0x38  // alamat default sensor

