#pragma once
#include <Arduino.h>

float lowPassFilter(float raw, float prevFiltered);
float updateBaseline(float prevBaseline, float filteredValue);
