#pragma once
#include <Arduino.h>

// Event dari sensor_processing
enum StateEvent {
    FEED_NONE,
    EVENT_BREAK_A,
    EVENT_BREAK_B,
    EVENT_CLEAR_BOTH
};

// Output state machine (hasil gerakan orang)
enum PeopleMovement {
    MOVEMENT_NONE,
    MOVEMENT_IN,
    MOVEMENT_OUT
};

void initStateMachine();
PeopleMovement updateStateMachine(StateEvent event);
