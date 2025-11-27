#include "state_machine.h"
#include "config.h"

// ----------------------------------------------------
// DEFINISI STATE INTERNAL (tidak konflik dengan config.h)
// ----------------------------------------------------
enum InternalState {
    ST_IDLE,           // Tidak ada sinar terputus
    ST_WAIT_B,         // Sinar A terputus dulu → menunggu B → masuk
    ST_WAIT_A,         // Sinar B terputus dulu → menunggu A → keluar
    ST_CONFIRM_IN,
    ST_CONFIRM_OUT
};

static InternalState state = ST_IDLE;
static unsigned long stateTime = 0;

static const unsigned long STATE_TIMEOUT = 800; // ms

void initStateMachine() {
    state = ST_IDLE;
    stateTime = millis();
}

// ----------------------------------------------------
// STATE MACHINE INTI
// ----------------------------------------------------
PeopleMovement updateStateMachine(StateEvent event) {
    unsigned long now = millis();

    // Timeout proteksi (biar nggak nge-freeze di WAIT_B/WAIT_A)
    if (now - stateTime > STATE_TIMEOUT) {
        state = ST_IDLE;
        return MOVEMENT_NONE;
    }

    switch (state) {

    // ------------------------------------------------
    case ST_IDLE:
        if (event == EVENT_BREAK_A) {
            state = ST_WAIT_B;
            stateTime = now;
        }
        else if (event == EVENT_BREAK_B) {
            state = ST_WAIT_A;
            stateTime = now;
        }
        break;

    // ------------------------------------------------
    case ST_WAIT_B:
        if (event == EVENT_BREAK_B) {
            state = ST_CONFIRM_IN;
            stateTime = now;
        }
        else if (event == EVENT_CLEAR_BOTH) {
            state = ST_IDLE;
        }
        break;

    // ------------------------------------------------
    case ST_WAIT_A:
        if (event == EVENT_BREAK_A) {
            state = ST_CONFIRM_OUT;
            stateTime = now;
        }
        else if (event == EVENT_CLEAR_BOTH) {
            state = ST_IDLE;
        }
        break;

    // ------------------------------------------------
    case ST_CONFIRM_IN:
        if (event == EVENT_CLEAR_BOTH) {
            state = ST_IDLE;
            return MOVEMENT_IN;
        }
        break;

    // ------------------------------------------------
    case ST_CONFIRM_OUT:
        if (event == EVENT_CLEAR_BOTH) {
            state = ST_IDLE;
            return MOVEMENT_OUT;
        }
        break;
    }

    return MOVEMENT_NONE;
}
