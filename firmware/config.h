#pragma once

// ==========================================
// PIN ASSIGNMENT
// ==========================================
// KY-008 uses digital pins (not PWM required, but can use PWM pins as digital)
#define LASER_A_PIN            9
#define LASER_B_PIN            10

#define LDR_A_PIN              A0
#define LDR_B_PIN              A1

// OPTIONAL: LDR tambahan buat ambient light detection
#define LDR_AMBIENT_PIN        A2

#define BUZZER_PIN             3

// ==========================================
// LASER CONTROL
// ==========================================
// KY-008 is digital ON/OFF only, no PWM dimming support
// These constants kept for compatibility but not used
#define LASER_DAY_PWM          255   // Not used with KY-008
#define LASER_NIGHT_PWM        180   // Not used with KY-008
#define NIGHT_THRESHOLD        50    // Not used (no auto dimming)
#define NIGHT_MODE_AUTO        false // KY-008 can't dim, always full power

// ==========================================
// FILTERING & BASELINE ADAPTATION
// ==========================================
#define FILTER_ALPHA           0.10f
#define BASELINE_ALPHA         0.001f

// ==========================================
// THRESHOLDS (with hysteresis)
// ==========================================
// CRITICAL: These MUST be calibrated in real conditions
// KY-008 laser intensity is fixed, so baseline should be stable
#define THRESHOLD_DROP         80    // ← CALIBRATE THIS
#define THRESHOLD_RECOVERY     40    // ← CALIBRATE THIS

// ==========================================
// OCCUPANCY CONFIG
// ==========================================
#define MAX_PEOPLE_COUNT       50

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
#define FRAME_DELAY_MS         20

// ==========================================
// SENSOR STRUCT
// ==========================================
typedef struct {
    int raw;
    float filtered;
    float baseline;
    float delta;
    bool broken;
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
