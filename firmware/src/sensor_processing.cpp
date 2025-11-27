#include "sensor_processing.h"
#include "config.h"
#include "filtering.h"

#include <Wire.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

// -----------------------------------------
// Sensor Storage (internal state)
// -----------------------------------------
static LDRSensor ldrA = {0};
static LDRSensor ldrB = {0};


// -----------------------------------------
// INIT
// -----------------------------------------
void initSensors() {
    // Init I2C
    Wire.begin();
    Wire.setClock(10000);   // 10 kHz → aman untuk kabel 13 meter

    // Init AHT20
    aht.begin();

    // Init baseline awal (ambil setelah 100ms runtime)
    delay(200);
    ldrA.baseline = analogRead(LDR_A_PIN);
    ldrB.baseline = analogRead(LDR_B_PIN);
}


// -----------------------------------------
// GENERIC LDR UPDATE (fungsi inti)
// -----------------------------------------
static void updateLDR_Generic(int pin, LDRSensor &d) {
    d.raw = analogRead(pin);

    // Filter low-pass
    d.filtered = lowPassFilter(d.raw, d.filtered);

    // Baseline drift tracking
    d.baseline = updateBaseline(d.baseline, d.filtered);

    // Hitung delta
    d.delta = d.baseline - d.filtered;

    // Tentukan apakah sinar putus (hysteresis)
    if (!d.broken) {
        // Kondisi awal → menunggu sinar turun cukup jauh
        if (d.delta > THRESHOLD_DROP) {
            d.broken = true;
        }
    } else {
        // Sinar sudah putus → tunggu kembali ke baseline
        if (d.delta < THRESHOLD_RECOVERY) {
            d.broken = false;
        }
    }
}


// -----------------------------------------
// PUBLIC WRAPPERS
// -----------------------------------------
void updateLDR_A(LDRSensor &data) {
    updateLDR_Generic(LDR_A_PIN, data);
}

void updateLDR_B(LDRSensor &data) {
    updateLDR_Generic(LDR_B_PIN, data);
}


// -----------------------------------------
// TEMPERATURE (AHT20)
// -----------------------------------------
float getTemperature() {
    sensors_event_t hum, temp;
    aht.getEvent(&hum, &temp);

    return temp.temperature;   // °C
}
