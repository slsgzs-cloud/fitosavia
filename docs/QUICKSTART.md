# Quick start (≈ 30 minutos)

Objetivo: flashear el firmware, ver el Serial Monitor a **115200** baudios y, si puedes, verificar la calibración en vacío (~**1.652 V**).

## 1. Clonar

```bash
git clone https://github.com/haas26p-ctrl/fitosavia.git
cd fitosavia
```

## 2. Arduino IDE + core ESP32

1. Instala [Arduino IDE](https://www.arduino.cc/en/software) (2.x recomendado).
2. Añade el core **esp32** de Espressif (Boards Manager → busca `esp32`).
3. Placa: **ESP32 Dev Module** (o equivalente DevKit V1).
4. Puerto serie correcto; velocidad del Monitor: **115200**.

## 3. Librerías

Library Manager → instala:

* **Adafruit ADS1X15**
* **Adafruit BusIO** (dependencia)
* **DHT sensor library** (compatible con DHT22)

## 4. Abrir y subir

1. Abre [`firmware/fitosavia/fitosavia.ino`](../firmware/fitosavia/fitosavia.ino)
2. Conecta el ESP32 por USB
3. **Upload**
4. Abre el Serial Monitor a **115200**

Deberías ver una línea de arranque similar a:

```text
FITOSAVIA - Hardware verificado. Algoritmo Anti-Electrólisis Iniciado.
```

y luego lecturas periódicas:

```text
Temp: …°C | Humedad: …% | Lectura cruda: … | Voltaje (V): …
```

Si falla el ADS1115, el sketch se detiene con un mensaje pidiendo revisar SDA/SCL (GPIO21 / GPIO22).

## 5. Calibración en vacío (recomendado)

Sin planta, con dos resistencias **10 kΩ ±1%** en divisor a **3.3 V**, el punto medio debe leer ≈ **1.652 V**.

* Si no: revisa soldaduras, gain del ADS1115 y que la lógica esté a **3.3 V** (nunca 5 V).
* Detalle de pines: [`hardware/WIRING.md`](../hardware/WIRING.md)
* Lista de materiales: [`hardware/BOM.md`](../hardware/BOM.md)

## 6. Seguridad

Lee [`SAFETY.md`](SAFETY.md) antes de insertar electrodos en una planta.

## English (short)

Clone → install ESP32 core + Adafruit ADS1X15 / BusIO / DHT library → upload `firmware/fitosavia/fitosavia.ino` → Serial **115200**. Empty calibration with 10k/10k divider should read ≈ **1.652 V**. See SAFETY.md before using electrodes on a plant.
