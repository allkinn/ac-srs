#pragma once

// ==========================================
// PIN ASSIGNMENT
// ==========================================
#define LASER_A_PIN            9
#define LASER_B_PIN            10

#define LDR_A_PIN              A0
#define LDR_B_PIN              A1

// OPTIONAL: LDR tambahan buat ambient light detection
#define LDR_AMBIENT_PIN        A2

#define BUZZER_PIN             3

// ==========================================
// LASER PWM CONTROL
// ==========================================
#define LASER_DAY_PWM          255
#define LASER_NIGHT_PWM        180
#define NIGHT_THRESHOLD        50

// Auto night mode detection
#define NIGHT_MODE_AUTO        false  // Set true kalau lo punya LDR ketiga

// ==========================================
// FILTERING & BASELINE ADAPTATION
// ==========================================
#define FILTER_ALPHA           0.10f
#define BASELINE_ALPHA         0.001f

// ==========================================
// THRESHOLDS (with hysteresis)
// ==========================================
#define THRESHOLD_DROP         80
#define THRESHOLD_RECOVERY     40

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
