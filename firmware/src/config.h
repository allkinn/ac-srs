#pragma once

// ==========================================
// LOOP TIMING (core heartbeat)
// ==========================================
// Sistem berjalan 50 Hz (20 ms per loop)
#define LOOP_INTERVAL_MS       20

// ==========================================
// PWM CONFIGURATION
// ==========================================
// Dua mode: Day Mode & Night Mode
// - Day mode = PWM cepat, laser stabil
// - Night mode = PWM lambat, hemat panas & power

// --- DAY MODE (editable) ---
#define LASER_ON_MS_NORMAL     4       // tanda: atur sesuai intensitas
#define LASER_OFF_MS_NORMAL    16      // tanda: respons cepat

// --- NIGHT MODE (editable) ---
#define LASER_ON_MS_NIGHT      1       // tanda: sangat rendah (hemat)
#define LASER_OFF_MS_NIGHT     40      // tanda: duty cycle rendah

// ==========================================
// DAY/NIGHT TIME BOUNDARY
// ==========================================
// Jam dalam format 24h
#define NIGHT_START_HOUR       19      // 19:00 → start night mode
#define NIGHT_END_HOUR          6      // 06:00 → back to day mode

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
