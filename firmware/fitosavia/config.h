#ifndef CONFIG_H
#define CONFIG_H

// --- Pines ---
#define DHTPIN 4
#define PIN_ALIMENTACION 5

// --- Sensor tipo ---
#define DHTTYPE DHT22

// --- Serial ---
#define SERIAL_BAUD 115200

// --- Delay de estabilización (ms) ---
#define STABILIZATION_DELAY_MS 100

// --- Intervalo entre muestras (ms) ---
#define SAMPLE_INTERVAL_MS 5000

#endif  // CONFIG_H
