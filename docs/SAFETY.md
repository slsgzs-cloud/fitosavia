# Seguridad y uso responsable

FITOSAVIA es un **prototipo experimental escolar** (EUREKA 2026). No es un producto médico ni un dispositivo agrícola certificado.

## Electrodos en planta

* Desinfecta el tallo y las agujas con **alcohol isopropílico** antes de insertar.
* Separación aproximada **~1.5 cm**; no atravieses el tallo de lado a lado.
* Retira los electrodos con cuidado; inspecciona necrosis o infección en ensayos largos.
* El firmware usa un **pulso corto (~100 ms)** en GPIO5 para reducir electrólisis; aun así, limita el tiempo de ensayo y documenta lo que observes.

## Alimentación y lógica

* Toda la lógica del prototipo está pensada para **3.3 V**.
* **Nunca** alimentes ADS1115 / DHT22 / líneas de datos a **5 V**.
* Usa BMS adecuado con celdas 18650; no improvises packs de litio sin protección.

## Alcance

* No uses las lecturas para decidir tratamientos clínicos, nutrición humana o certificaciones.
* Interpreta los datos en el contexto del [método documentado](METODO.md) y del cuaderno de campo.

## English (short)

School experimental prototype only — not medical or certified ag gear. Disinfect electrodes, ~1.5 cm spacing, do not pierce through the stem. Keep logic at **3.3 V** (never 5 V). Short excitation pulse exists to reduce electrolysis; still treat plant tissue carefully.
