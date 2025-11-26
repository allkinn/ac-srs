#pragma once
#include <Arduino.h>

enum BeamState {
    IDLE,
    A_BROKEN,
    B_BROKEN,
    A_THEN_B,
    B_THEN_A
};

extern BeamState beamState;

void initStateMachine();
void updateBeamState();
