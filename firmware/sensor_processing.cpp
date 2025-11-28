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
    // LM393 AO pins are analog, no pinMode needed (analogRead auto-configures)
    
    // Init I2C for AHT20 (will use later)
    Wire.begin();
    Wire.setClock(10000);   // 10 kHz → aman untuk kabel 13 meter

    // Init AHT20 (comment out if not connected yet)
    if (!aht.begin()) {
        Serial.println("Warning: AHT20 not found. Temperature disabled.");
    }

    // Init baseline awal (ambil setelah 200ms runtime)
    delay(200);
    ldrA.baseline = analogRead(LDR_A_PIN);
    ldrB.baseline = analogRead(LDR_B_PIN);
    
    Serial.print("Baseline A: "); Serial.println(ldrA.baseline);
    Serial.print("Baseline B: "); Serial.println(ldrB.baseline);
}

// -----------------------------------------
// GENERIC LDR UPDATE (fungsi inti)
// -----------------------------------------
static void updateLDR_Generic(int pin, LDRSensor &d) {
    // Read analog value from LM393 AO pin
    d.raw = analogRead(pin);

    // Filter low-pass
    d.filtered = lowPassFilter(d.raw, d.filtered);

    // Baseline drift tracking
    d.baseline = updateBaseline(d.baseline, d.filtered);

    // Hitung delta
    // LM393 AO: HIGH value when light detected, LOW when blocked
    // So delta is POSITIVE when beam is present, NEGATIVE/ZERO when blocked
    d.delta = d.filtered - d.baseline;

    // Tentukan apakah sinar putus (hysteresis)
    // INVERTED LOGIC compared to bare LDR:
    // When beam blocked → value drops → delta becomes NEGATIVE
    if (!d.broken) {
        // Kondisi awal → menunggu value turun drastis (beam blocked)
        if (d.delta < -THRESHOLD_DROP) {  // Note: NEGATIVE threshold
            d.broken = true;
        }
    } else {
        // Sinar sudah putus → tunggu kembali ke baseline
        if (d.delta > -THRESHOLD_RECOVERY) {  // Note: NEGATIVE threshold
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
    if (aht.getEvent(&hum, &temp)) {
        return temp.temperature;   // °C
    }
    return -999.0;  // Error value if sensor not responding
}
