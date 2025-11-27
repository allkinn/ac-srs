#include "state_machine.h"
#include "config.h"

// ----------------------------------------------------
// DEFINISI STATE
// ----------------------------------------------------
enum SMState {
    IDLE,           // Tidak ada sinar terputus
    WAIT_B,         // Sinar A terputus dulu → menunggu B → masuk
    WAIT_A,         // Sinar B terputus dulu → menunggu A → keluar
    CONFIRM_IN,
    CONFIRM_OUT
};

static SMState state = IDLE;
static unsigned long stateTime = 0;

static const unsigned long STATE_TIMEOUT = 800; // ms

void initStateMachine() {
    state = IDLE;
    stateTime = millis();
}

// ----------------------------------------------------
// STATE MACHINE INTI
// ----------------------------------------------------
PeopleMovement updateStateMachine(StateEvent event) {
    unsigned long now = millis();

    // Timeout proteksi (biar nggak nge-freeze di WAIT_B/W)
    if (now - stateTime > STATE_TIMEOUT) {
        state = IDLE;
        return MOVEMENT_NONE;
    }

    switch (state) {

    // ------------------------------------------------
    case IDLE:
        if (event == EVENT_BREAK_A) {
            state = WAIT_B;
            stateTime = now;
        }
        else if (event == EVENT_BREAK_B) {
            state = WAIT_A;
            stateTime = now;
        }
        break;

    // ------------------------------------------------
    case WAIT_B:
        if (event == EVENT_BREAK_B) {
            state = CONFIRM_IN;
            stateTime = now;
        }
        else if (event == EVENT_CLEAR_BOTH) {
            state = IDLE;
        }
        break;

    // ------------------------------------------------
    case WAIT_A:
        if (event == EVENT_BREAK_A) {
            state = CONFIRM_OUT;
            stateTime = now;
        }
        else if (event == EVENT_CLEAR_BOTH) {
            state = IDLE;
        }
        break;

    // ------------------------------------------------
    case CONFIRM_IN:
        if (event == EVENT_CLEAR_BOTH) {
            state = IDLE;
            return MOVEMENT_IN;
        }
        break;

    // ------------------------------------------------
    case CONFIRM_OUT:
        if (event == EVENT_CLEAR_BOTH) {
            state = IDLE;
            return MOVEMENT_OUT;
        }
        break;
    }

    return MOVEMENT_NONE;
}
