# FITOSAVIA

**Fitomonitoreo in-situ mediante biosensor de impedancia bioeléctrica** para diagnóstico de estrés hídrico temprano en *Solanum lycopersicum* (tomate).

Proyecto escolar — Feria EUREKA 2026 (soluciones tecnológicas).  
Autor: **Alessandro Sebastian Herrera Araoz** · I.E. Blas Pascal (Miraflores, Arequipa).  
Licencia: [MIT](LICENSE)

## Qué es

FITOSAVIA es un biosensor IoT de bajo costo y no destructivo. Mide la resistencia eléctrica de la savia en el tallo con un ADC de 16 bits (ADS1115) y un ESP32, compensando deriva térmica con un DHT22. La idea: detectar cavitación del xilema **antes** de la marchitez visual.

## Hardware

| Bloque | Pieza |
|--------|--------|
| MCU | ESP32 DevKit V1 (30 pines) |
| ADC | ADS1115 (I²C, 16 bits) |
| Ambiente | DHT22 |
| Electrodos | Agujas de acupuntura (acero inoxidable) |
| Energía | 18650 + BMS 2S |
| Caja | Registro IP55 |

Lista completa: [`hardware/BOM.md`](hardware/BOM.md)  
Esquema de pines y cableado: [`hardware/WIRING.md`](hardware/WIRING.md)

```
ESP32 3V3 ──► ADS1115 VDD, DHT22
ESP32 GND ──► tierras comunes
GPIO21/22 ──► ADS1115 SDA/SCL
GPIO5     ──► electrodo excitación (pulso 100 ms)
ADS1115 A0──► electrodo / nodo de lectura
GPIO4     ──► DHT22 DATA
```

## Firmware

Sketch Arduino (el que corre en el ESP32): [`firmware/fitosavia/fitosavia.ino`](firmware/fitosavia/fitosavia.ino)

### Dependencias

1. Core ESP32 en Arduino IDE  
2. Adafruit ADS1X15  
3. Adafruit BusIO  
4. DHT sensor library  

### Algoritmo Anti-Electrólisis

1. Encender GPIO5 (`pinAlimentacion`)  
2. Esperar 100 ms  
3. Leer ADS1115 canal A0  
4. Apagar GPIO5 de inmediato  
5. Leer DHT22 (temperatura/humedad para deriva térmica)  
6. Imprimir por Serial a **115200** baudios  

### Calibración en vacío

Con dos resistencias 10 kΩ ±1% en divisor a 3.3 V, el punto medio debe leer ≈ **1.652 V**. Si no, revisa soldaduras, gain del ADS1115 y alimentación a 3.3 V (nunca 5 V en la lógica).

### Salida Serial

```
Temp: …°C | Humedad: …% | Lectura cruda: … | Voltaje (V): …
```

El factor `0.1875` mV/LSB corresponde al gain por defecto del ADS1115 (±6.144 V).

## Alcance (sin maquillaje)

**Hecho y documentado en el cuaderno de campo**

- Arquitectura ESP32 + ADS1115 + DHT22  
- Calibración del ADC con divisor 10k/10k  
- Soldadura en placa perforada y encapsulado IP55  
- Prueba in vivo en tomate hidratado: ciclo estable, sin necrosis en el tallo  
- Línea base de planta sana  

**Aún no hecho**

- Ensayo longitudinal de sequía controlada y curvas de decadencia  
- Validación estadística multi-planta en campo  

Método y notas: [`docs/METODO.md`](docs/METODO.md)

## Uso responsable

Insertar electrodos con higiene (alcohol isopropílico), ~1.5 cm de separación, sin atravesar el tallo. El pulso corto existe para reducir electrólisis; aun así es un prototipo experimental escolar, no un producto médico ni certificado agrícola.

## Estructura del repo

```
fitosavia/
├── LICENSE
├── README.md
├── firmware/fitosavia/fitosavia.ino
├── hardware/BOM.md
├── hardware/WIRING.md
└── docs/METODO.md
```

## Contribuir

Issues y PRs sobre firmware, docs, calibración o hardware son bienvenidos. Preferimos cambios pequeños y comprobables (bugs, claridad en el esquema, mejoras del algoritmo anti-electrólisis) frente a ruido cosmético.
