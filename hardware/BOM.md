# Lista de materiales (BOM) — FITOSAVIA

Presupuesto aproximado de referencia: **S/ 150** (Arequipa, Perú).

| # | Componente | Cant. | Notas |
|---|------------|------:|-------|
| 1 | ESP32 DevKit V1 (ESP32-WROOM-32, 30 pines) | 1 | MCU IoT |
| 2 | ADS1115 (ADC 16 bits, I²C) | 1 | Lectura de precisión; no usar solo el ADC interno del ESP32 |
| 3 | DHT22 (AM2302) | 1 | Temperatura/humedad; **no** sustituir por DHT11 |
| 4 | Resistencias de película metálica 10 kΩ ±1% | 2 | Divisor de tensión de calibración / lectura |
| 5 | Electrodos: agujas de acupuntura de acero inoxidable | 2 | Excitación (D5) y lectura (hacia ADS1115) |
| 6 | Cobre fino + flux + termocontraíble | — | Unión estaño–acero en electrodos |
| 7 | Cables Dupont / jumpers | 1 set | Prototipo y cableado final |
| 8 | Protoboard AJ-PT03 (o similar) | 1 | Solo fase de pruebas en seco |
| 9 | Placa perforada universal (puntos aislados) | 1 | Soldadura definitiva (**no** placa tipo protoboard con columnas) |
| 10 | Baterías 18650 (calidad verificada) | 2 | Evitar celdas con mAh falsos |
| 11 | Módulo BMS 2S | 1 | Protección de litio |
| 12 | Caja de registro estanca IP55 | 1 | Encapsulado de campo |
| 13 | Silicona caliente | — | Sellado e alivio de tensión en conectores |
| 14 | Alcohol isopropílico + algodón | — | Desinfección del tallo |
| 15 | Multímetro digital | 1 | Continuidad y diagnóstico |
| 16 | Cautín punta fina, estaño Rosin Core, flux | — | Soldadura |

## Dependencias de software (Arduino IDE)

- Core ESP32 (Espressif)
- [Adafruit ADS1X15](https://github.com/adafruit/Adafruit_ADS1X15)
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)
- Librería DHT sensor (compatible con DHT22)

## Advertencias de compra

- Exigir DHT22 (blanco), no DHT11 (azul).
- Preferir resistencias de película metálica ±1% frente a carbón ±5%.
- Verificar capacidad real de baterías 18650; descartar etiquetas genéricas dudosas.
