#pragma once
#include <Arduino.h>
#include "state_machine.h"

// Inisialisasi occupancy counter
void initOccupancy();

// Update counter berdasarkan movement event dari state machine
void updateOccupancy(PeopleMovement movement);

// Ambil jumlah orang saat ini
int getCurrentCount();

// Reset counter ke 0 (manual reset kalau perlu)
void resetOccupancy();

// Cek apakah ruangan penuh (optional safety check)
bool isRoomFull();
