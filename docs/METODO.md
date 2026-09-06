# Método y alcance

## Principio

Si la planta entra en estrés hídrico, baja el agua en el xilema y aparecen microburbujas de aire (cavitación). El aire es dieléctrico; la savia con iones es conductora. Por tanto, la **resistencia eléctrica (Ω)** entre dos electrodos en el tallo **aumenta** antes de la marchitez visual.

## Algoritmo Anti-Electrólisis

Para no dañar el tejido por electrólisis continua:

1. Encender excitación en GPIO5.
2. Esperar **100 ms** a estabilizar.
3. Leer diferencial / canal A0 con ADS1115 (16 bits).
4. Apagar excitación de inmediato.
5. Leer DHT22 y (opcional) normalizar por temperatura.
6. Emitir lectura por Serial a **115200** baudios.
7. Repetir con intervalo de muestreo configurable.

## Alcance validado (honesto)

- **Validado:** ensamblaje, calibración del ADS1115 (1.652 V en divisor 10k/10k), ciclo anti-electrólisis in vivo en tomate hidratado, ausencia de necrosis en el tallo tras la prueba.
- **Línea base:** resistencia de planta sana hidratada.
- **Pendiente:** ensayo longitudinal de sequía controlada y curvas de decadencia. El prototipo queda listo para esa fase biológica.

## Contexto

Proyecto escolar EUREKA 2026 (Feria Escolar Nacional de Ciencia y Tecnología), categoría soluciones tecnológicas. Investigador: Alessandro Sebastian Herrera Araoz — I.E. Blas Pascal, Miraflores (Arequipa).
