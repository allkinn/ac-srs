#pragma once

// ==========================================
// PIN ASSIGNMENT
// ==========================================
// KY-008 Laser modules (digital control)
#define LASER_A_PIN            9
#define LASER_B_PIN            10

// LM393 Analog Output (AO pins)
#define LDR_A_PIN              A0
#define LDR_B_PIN              A1

// AHT20 I2C (fixed pins on Nano)
// SDA = A4, SCL = A5 (hardware defined)

#define BUZZER_PIN             3   // Optional

// ==========================================
// LASER CONTROL
// ==========================================
// KY-008 is digital ON/OFF only (no PWM dimming)
#define LASER_DAY_PWM          255   // Not used
#define LASER_NIGHT_PWM        180   // Not used
#define NIGHT_THRESHOLD        50    // Not used
#define NIGHT_MODE_AUTO        false

// ==========================================
// FILTERING & BASELINE ADAPTATION
// ==========================================
#define FILTER_ALPHA           0.10f      // 10% new, 90% history (smoothing)
#define BASELINE_ALPHA         0.001f     // Slow drift adaptation

// ==========================================
// THRESHOLDS (with hysteresis)
// ==========================================
// CRITICAL: LM393 AO logic is INVERTED
// - High value (~700-950) = Light detected (beam present)
// - Low value (~50-200)   = Light blocked (beam interrupted)
// - Delta = filtered - baseline
// - When blocked: delta becomes NEGATIVE (drops below baseline)

// Based on your test: normal >700, blocked <100
// Drop magnitude: 700 - 100 = 600
// Recommended thresholds:

#define THRESHOLD_DROP         200   // Delta must drop below -200 to trigger (blocked)
#define THRESHOLD_RECOVERY     100   // Delta must rise above -100 to clear (hysteresis)

// Adjust these after real-world testing if needed

// ==========================================
// STATE MACHINE TIMEOUTS
// ==========================================
#define STATE_TIMEOUT_MS       800   // Max time for A→B or B→A sequence

// ==========================================
// OCCUPANCY CONFIG
// ==========================================
#define MAX_PEOPLE_COUNT       60

// ==========================================
// TEMPERATURE CONFIG
// ==========================================
#define TEMP_COLD_THRESHOLD    23.5f

// ==========================================
// AHT20 CONFIG
// ==========================================
#define AHT20_I2C_ADDR         0x38

// ==========================================
// LOOP TIMING
// ==========================================
#define FRAME_DELAY_MS         20    // 50 Hz main loop

// ==========================================
// SENSOR STRUCT
// ==========================================
typedef struct {
    int raw;           // ADC reading 0-1023 from LM393 AO
    float filtered;    // Low-pass filtered value
    float baseline;    // Long-term baseline (drift tracking)
    float delta;       // filtered - baseline (negative when blocked)
    bool broken;       // TRUE = beam blocked, FALSE = beam clear
} LDRSensor;

// ==========================================
// STATE MACHINE ENUMS
// ==========================================
enum SystemState {
    IDLE,
    BREAK_A,
    BREAK_B,
    CONFIRM_AB,
    CONFIRM_BA,
    RECOVERY
};
