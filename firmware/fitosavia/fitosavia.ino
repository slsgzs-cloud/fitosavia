/**
 * FITOSAVIA — Fitomonitoreo in-situ por impedancia bioeléctrica
 * Estrés hídrico temprano en Solanum lycopersicum (tomate).
 *
 * Hardware: ESP32 + ADS1115 (I2C) + DHT22
 * Algoritmo Anti-Electrólisis: pulso corto en GPIO5, lectura, corte inmediato.
 *
 * Autor: Alessandro Sebastian Herrera Araoz
 * Licencia: MIT
 *
 * Librerías (Arduino Library Manager / ZIP):
 *   - Adafruit ADS1X15
 *   - Adafruit BusIO
 *   - DHT sensor library (Adafruit)
 */

#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <DHT.h>

// ---- Pines ----
static const int PIN_EXCITATION = 5;   // GPIO5 — electrodo de excitación
static const int PIN_DHT = 4;          // GPIO4 — DHT22 DATA
static const int PIN_SDA = 21;         // I2C SDA → ADS1115
static const int PIN_SCL = 22;         // I2C SCL → ADS1115

// ---- Muestreo ----
static const uint16_t EXCITATION_MS = 100;     // duración del pulso (anti-electrólisis)
static const uint32_t SAMPLE_INTERVAL_MS = 5000;
static const uint32_t SERIAL_BAUD = 115200;

// ---- Sensor ambiental ----
#define DHTTYPE DHT22
DHT dht(PIN_DHT, DHTTYPE);
Adafruit_ADS1115 ads;

// Resistencia de referencia del divisor (ohms). Ajustar si usas otro valor.
static const float R_REF_OHMS = 10000.0f;
static const float V_EXC = 3.3f;

// Coeficiente simple de normalización térmica (placeholder empírico).
// R_norm ≈ R_meas / (1 + alpha * (T - T0))
static const float T0_C = 25.0f;
static const float ALPHA_PER_C = 0.02f;

bool adsOk = false;

void setup() {
  pinMode(PIN_EXCITATION, OUTPUT);
  digitalWrite(PIN_EXCITATION, LOW);

  Serial.begin(SERIAL_BAUD);
  delay(500);
  Serial.println();
  Serial.println(F("FITOSAVIA — arranque"));
  Serial.println(F("Anti-Electrolisis: pulso 100 ms en GPIO5"));

  Wire.begin(PIN_SDA, PIN_SCL);
  adsOk = ads.begin(0x48);
  if (!adsOk) {
    Serial.println(F("ERROR: ADS1115 no responde en I2C (0x48). Revisa SDA/SCL y 3V3."));
  } else {
    // ±4.096 V → buen margen sobre 3.3 V de excitación
    ads.setGain(GAIN_ONE);
    Serial.println(F("ADS1115 OK (GAIN_ONE, ±4.096 V)"));
  }

  dht.begin();
  Serial.println(F("DHT22 iniciado"));
  Serial.println(F("ts_ms,temp_C,hum_%,v_A0,R_est_ohm,R_norm_ohm,exc_ms"));
}

float readStemVoltage() {
  // Ciclo Anti-Electrólisis
  digitalWrite(PIN_EXCITATION, HIGH);
  delay(EXCITATION_MS);
  int16_t raw = ads.readADC_SingleEnded(0);
  digitalWrite(PIN_EXCITATION, LOW);

  return ads.computeVolts(raw);
}

float estimateResistance(float vNode) {
  // Modelo simple tipo divisor: electrodo/tejido vs R_REF hacia GND.
  // Si vNode ≈ V_EXC/2 con dos 10k, R_est ≈ R_REF.
  if (vNode <= 0.001f || vNode >= (V_EXC - 0.001f)) {
    return NAN;
  }
  return R_REF_OHMS * (vNode / (V_EXC - vNode));
}

float normalizeThermal(float rOhms, float tempC) {
  if (isnan(rOhms) || isnan(tempC)) {
    return NAN;
  }
  float denom = 1.0f + ALPHA_PER_C * (tempC - T0_C);
  if (fabs(denom) < 1e-3f) {
    return NAN;
  }
  return rOhms / denom;
}

void loop() {
  static uint32_t lastSample = 0;
  uint32_t now = millis();
  if (now - lastSample < SAMPLE_INTERVAL_MS) {
    return;
  }
  lastSample = now;

  if (!adsOk) {
    Serial.println(F("SKIP: sin ADS1115"));
    return;
  }

  float tempC = dht.readTemperature();
  float hum = dht.readHumidity();
  float vA0 = readStemVoltage();
  float rEst = estimateResistance(vA0);
  float rNorm = normalizeThermal(rEst, tempC);

  Serial.print(now);
  Serial.print(',');
  if (isnan(tempC)) Serial.print(F("nan")); else Serial.print(tempC, 2);
  Serial.print(',');
  if (isnan(hum)) Serial.print(F("nan")); else Serial.print(hum, 1);
  Serial.print(',');
  Serial.print(vA0, 4);
  Serial.print(',');
  if (isnan(rEst)) Serial.print(F("nan")); else Serial.print(rEst, 1);
  Serial.print(',');
  if (isnan(rNorm)) Serial.print(F("nan")); else Serial.print(rNorm, 1);
  Serial.print(',');
  Serial.println(EXCITATION_MS);
}
