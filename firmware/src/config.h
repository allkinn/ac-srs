#ifndef CONFIG_H
#define CONFIG_H

// =========================
// PIN DEFINITIONS
// =========================
#define LDR_A_PIN          A0
#define LDR_B_PIN          A1

#define LASER_A_PIN        5     // PWM-capable pin
#define LASER_B_PIN        6     // PWM-capable pin

#define SDA_PIN            A4
#define SCL_PIN            A5


// =========================
// LOOP TIMING
// =========================
#define FRAME_DELAY_MS     20    // 50 Hz main loop


// =========================
// FILTERING PARAMETERS
// =========================
#define FILTER_ALPHA       0.20f     // Low-pass filter strength
#define BASELINE_RATE      0.001f    // baseline drift adaptation
#define DELTA_THRESHOLD    80        // difference from baseline to consider beam broken
#define DELTA_HYSTERESIS   40        // recovery threshold


// =========================
// LASER CONTROL PARAMETERS
// =========================
#define LASER_DAY_PWM      255
#define LASER_NIGHT_PWM    180

#define NIGHT_THRESHOLD    50    // ambient light below this → night mode


// =========================
// STATE MACHINE TIMEOUTS
// =========================
#define BREAK_TIMEOUT_MS   600
#define RECOVERY_TIME_MS   300


// =========================
// OCCUPANCY PARAMETERS
// =========================
#define MAX_PEOPLE_COUNT       99
#define TEMP_COLD_THRESHOLD    25


// =========================
// SENSOR STRUCT DEFINITIONS
// =========================
typedef struct {
    int raw;
    float filtered;
    float baseline;
    float delta;
    bool broken;
} LDRSensor;


// =========================
// STATE MACHINE ENUMS
// =========================
enum SystemState {
    IDLE,
    BREAK_A,
    BREAK_B,
    CONFIRM_AB,
    CONFIRM_BA,
    RECOVERY
};

#endif
