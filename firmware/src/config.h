#pragma once

// Loop timing
#define LOOP_INTERVAL_MS 20     // 50 Hz main loop

// LDR analog pins
#define LDR_A_PIN A0
#define LDR_B_PIN A1

// Filtering config
#define FILTER_WINDOW 10
#define MEDIAN_CLAMP_RANGE 20

// Detection config
#define BREAK_THRESHOLD 10        // dynamic threshold will override this
#define BASELINE_UPDATE_RATE 0.01 // slow drifting compensation

// Temperature
#define AC_TEMP_THRESHOLD 25.0f

// Buzzer pin
#define BUZZER_PIN 9
