#include "state_machine.h"
#include "sensor_processing.h"

BeamState beamState = IDLE;

void initStateMachine() {
    beamState = IDLE;
}

void updateBeamState() {
    bool aBroken = isLDR_ABroken();
    bool bBroken = isLDR_BBroken();

    switch (beamState) {
        case IDLE:
            if (aBroken) beamState = A_BROKEN;
            else if (bBroken) beamState = B_BROKEN;
            break;

        case A_BROKEN:
            if (bBroken) beamState = A_THEN_B;
            else if (!aBroken) beamState = IDLE;
            break;

        case B_BROKEN:
            if (aBroken) beamState = B_THEN_A;
            else if (!bBroken) beamState = IDLE;
            break;

        default:
            break;
    }
}
