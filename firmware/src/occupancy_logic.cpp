#include "occupancy_logic.h"
#include "config.h"

// Static variable untuk menyimpan jumlah orang
static int peopleCount = 0;

void initOccupancy() {
    peopleCount = 0;
}

void updateOccupancy(PeopleMovement movement) {
    if (movement == MOVEMENT_IN) {
        peopleCount++;
        if (peopleCount > MAX_PEOPLE_COUNT) {
            peopleCount = MAX_PEOPLE_COUNT;  // Safety cap
        }
        Serial.print("IN  -> Count: ");
        Serial.println(peopleCount);
    } 
    else if (movement == MOVEMENT_OUT) {
        peopleCount--;
        if (peopleCount < 0) {
            peopleCount = 0;  // Prevent negative count
        }
        Serial.print("OUT -> Count: ");
        Serial.println(peopleCount);
    }
}

int getCurrentCount() {
    return peopleCount;
}

void resetOccupancy() {
    peopleCount = 0;
    Serial.println("Occupancy reset to 0");
}

bool isRoomFull() {
    return peopleCount >= MAX_PEOPLE_COUNT;
}
