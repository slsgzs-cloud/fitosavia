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

## Troubleshooting / Errores frecuentes

### 1. USB port or driver not detected

- **Windows:** Install the CP210x or CH340 driver from the ESP32 board package (Boards Manager).
- **Linux/macOS:** No driver needed. Check `/dev/ttyUSB*` or `/dev/ttyACM*` with `ls`.
- Verify the correct port is selected in Arduino IDE Tools → Port.
- If the port disappears after selecting it, the board may be in download mode — hold the **BOOT** button while clicking Upload.

### 2. Upload fails (wrong board / hold BOOT)

- Ensure the board is set to **ESP32 Dev Module** (not ESP8266).
- If "Failed to connect to ESP32," hold the **BOOT** button, click Upload, release BOOT when upload starts.
- Disable any USB-to-serial monitoring (close Serial Monitor before uploading).
- Try a different USB cable (some only supply power, no data).

### 3. `Error de comunicación con el ADS1115` (ADS1115 communication error)

- Check SDA on **GPIO21** and SCL on **GPIO22** are wired correctly.
- Ensure the ADS1115 logic is powered at **3.3 V** (not 5 V).
- Use the Arduino I2C Scanner sketch to confirm the ADS1115 responds at address **0x48**.
- Add pull-up resistors (4.7 kΩ) to SDA and SCL if signals are noisy.

### 4. DHT readings show `nan`

- Connect the DHT **DATA** pin to **GPIO4** (not GPIO3 or GPIO13).
- Add a 4.7 kΩ pull-up resistor between DATA and 3.3 V.
- Confirm you are using a **DHT22** (not DHT11) — the sketch expects DHT22 range.
- Power the DHT at **3.3 V** with a 10 kΩ resistor on VCC if noise appears.

### 5. Calibration voltage far from 1.652 V

- Verify the 10 kΩ / 10 kΩ voltage divider is wired to **3.3 V** (not 5 V).
- A reading of ~3.3 V means the divider output is shorted to VCC.
- A reading of ~0 V means the divider output is shorted to GND or the ADS1115 is disconnected.
- Deviation beyond ±0.05 V suggests component tolerance issues or wiring faults.
- Recalibrate by adjusting the gain in `firmware/fitosavia/fitosavia.ino` (default: GAIN_2_V).
