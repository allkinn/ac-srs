#pragma once
#include <Arduino.h>

extern int filteredA;
extern int filteredB;

void initFiltering();
void updateLDRFilteredValues();
