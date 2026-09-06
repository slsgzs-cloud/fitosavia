# Esquema de conexiones — FITOSAVIA

Arquitectura lógica unificada a **3.3 V**. Nunca alimentar el ADS1115 desde 5 V / VIN del ESP32: los pines GPIO del ESP32 no toleran 5 V.

## Diagrama ASCII

```
                    +3V3 (ESP32)
                         |
         +---------------+---------------+
         |               |               |
      ADS1115          DHT22         Divisor 10k/10k
      VDD                VCC            (calibración / excitación)
      GND <----------- GND -------------+
      SDA ---- GPIO21 (D21)
      SCL ---- GPIO22 (D22)
      A0  <--- nodo de lectura (electrodo / divisor)

      ESP32 GPIO5 (D5) ---- MOSFET/excitación ---- electrodo tallo
                                                    (pulso 100 ms)

      Electrodos en tallo (Solanum lycopersicum):
        - Excitación: GPIO5
        - Lectura: canal A0 del ADS1115
        - Separación vertical ≈ 1.5 cm
        - Penetrar hasta médula sin atravesar el tallo
```

## Pinout resumido

| Señal | ESP32 | Módulo |
|-------|-------|--------|
| Alimentación lógica | 3V3 | ADS1115 VDD, DHT22 VCC |
| Tierra | GND | ADS1115 GND, DHT22 GND |
| I²C SDA | GPIO21 | ADS1115 SDA |
| I²C SCL | GPIO22 | ADS1115 SCL |
| Datos DHT22 | GPIO4 (configurable en firmware) | DHT22 DATA |
| Excitación electrodo | GPIO5 | Pulso anti-electrólisis |
| Lectura analógica | — | ADS1115 A0 |

## Divisor de tensión (calibración en vacío)

Dos resistencias 10 kΩ ±1% en serie entre 3.3 V y GND. El punto medio debe leer ≈ **1.652 V** en el ADS1115. Esa prueba valida linealidad antes de conectar la planta.

## Notas de manufactura

1. Protoboard solo para pruebas en seco.
2. Soldadura definitiva en placa perforada de puntos aislados.
3. Método de 3 fases: soldar un componente → limpiar resina → continuidad con multímetro.
4. Encapsular en caja IP55; aliviar tensión de Dupont con silicona caliente.
