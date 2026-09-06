# Contribuir a FITOSAVIA

¡Gracias por tu interés! Buscamos cambios **pequeños, claros y comprobables**.  
Preferimos un PR útil de 20 líneas a un refactor cosmético de 2000.

**English:** Small, reviewable PRs welcome. Start from Issues labeled `good first issue` or `help wanted`. Read [`docs/QUICKSTART.md`](docs/QUICKSTART.md) and this guide. By participating you agree to our [Code of Conduct](CODE_OF_CONDUCT.md).

## Código de conducta

Participar implica aceptar el [Código de Conducta](CODE_OF_CONDUCT.md).

## Cómo ayudar **sin** hardware

Ideal para primeros PRs:

* Typos, claridad en README / docs
* Mejoras a [`hardware/BOM.md`](hardware/BOM.md) o [`hardware/WIRING.md`](hardware/WIRING.md)
* Traducciones ES ↔ EN
* Plantillas de ensayo / scripts que parseen Serial → CSV (ver Issues)

## Cómo ayudar **con** hardware

* Replicar la calibración en vacío (divisor 10 kΩ / 10 kΩ → ≈ **1.652 V**)
* Reportar lecturas Serial (temp, humedad, ADC, voltaje) y condiciones de la planta
* Abrir un issue tipo bug con log y foto/esquema si algo no cuadra

Guía de 30 minutos: [`docs/QUICKSTART.md`](docs/QUICKSTART.md)  
Seguridad: [`docs/SAFETY.md`](docs/SAFETY.md)

## Flujo

1. Fork del repo
2. Branch: `fix/descripcion-corta` (o `docs/...`)
3. Cambios pequeños y enfocados
4. Abre un Pull Request enlazando el Issue (`Fixes #N` si aplica)
5. Espera review (intentamos responder en &lt; 48 h)

## Estilo

* Diff pequeño; **no** reformatear archivos enteros “de pasada”
* Comentarios en el idioma del archivo que tocas (ES o EN)
* No hardcodear WiFi, tokens ni secretos
* No romper el algoritmo anti-electrólisis (pulso corto en GPIO5) sin justificación y medición

## Qué no mergeamos

* Credenciales o SSID/password en el código
* PRs solo cosméticos sin mejora real
* Scope creep (mezclar docs + rewrite grande de firmware en un solo PR)
* Uso presentado como producto médico o certificado agrícola

## Issues etiquetados

| Label | Significado |
|-------|------------|
| `good first issue` | Buen primer PR |
| `help wanted` | Necesitamos mano externa |
| `documentation` | Docs / i18n |
| `firmware` | Sketch / PlatformIO |
| `hardware` | BOM, wiring, electrodos |
| `calibration` | Divisor 10k, gain ADS |

¿Dudas? Abre un issue con la plantilla que mejor encaje. Gracias.
