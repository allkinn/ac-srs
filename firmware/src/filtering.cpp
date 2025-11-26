#include "filtering.h"
#include "config.h"

static int aBuf[FILTER_WINDOW];
static int aIndex = 0;
static long aSum = 0;

static int bBuf[FILTER_WINDOW];
static int bIndex = 0;
static long bSum = 0;

int filteredA = 0;
int filteredB = 0;

void initFiltering() {
    memset(aBuf, 0, sizeof(aBuf));
    memset(bBuf, 0, sizeof(bBuf));
}

int movingAvg(int newVal, int* buf, int size, int &idx, long &sum) {
    sum -= buf[idx];
    buf[idx] = newVal;
    sum += newVal;
    idx = (idx + 1) % size;
    return sum / size;
}

void updateLDRFilteredValues() {
    filteredA = movingAvg(analogRead(LDR_A_PIN), aBuf, FILTER_WINDOW, aIndex, aSum);
    filteredB = movingAvg(analogRead(LDR_B_PIN), bBuf, FILTER_WINDOW, bIndex, bSum);
}
