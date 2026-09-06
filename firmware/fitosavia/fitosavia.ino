#include <Wire.h>

#include <Adafruit_ADS1X15.h>

#include "DHT.h"

Adafruit_ADS1115 ads; 

// --- CONFIGURACIÓN DE PINES ---

#define DHTPIN 4         // DHT22 conectado al pin D4

#define DHTTYPE DHT22    // Modelo exacto de tu sensor

DHT dht(DHTPIN, DHTTYPE);

const int pinAlimentacion = 5; // Pin D5 para enviar energía a la planta (Agujas)

void setup() {

  Serial.begin(115200);

  delay(1000); // Freno de 1 segundo para darle tiempo al Monitor Serie de despertar

  

  // Configuramos el pin de la planta como salida de energía

  pinMode(pinAlimentacion, OUTPUT);

  digitalWrite(pinAlimentacion, LOW); // Lo mantenemos apagado por seguridad biológica

  // Inicializamos el sensor ambiental

  dht.begin();

  // Inicializamos la comunicación I2C a 3.3V (SDA = 21, SCL = 22)

  Wire.begin(21, 22); 

  

  if (!ads.begin()) {

    Serial.println("Error de comunicación con el ADS1115. Revisa los cables SDA y SCL.");

    while (1); // Si hay error, el programa se detiene aquí

  }

  Serial.println("FITOSAVIA - Hardware verificado. Algoritmo Anti-Electrólisis Iniciado.");

}

void loop() {

  // --- LECTURA AMBIENTAL (DERIVA TÉRMICA) ---

  float temperatura = dht.readTemperature();

  float humedad = dht.readHumidity();

  // --- INICIO DEL ALGORITMO ANTI-ELECTRÓLISIS ---

  // 1. Encender la corriente hacia los micro-electrodos

  digitalWrite(pinAlimentacion, HIGH);

  

  // 2. Esperar a que la corriente se estabilice en el tejido (100 ms)

  delay(100); 

  

  // 3. Tomar la lectura analógica en el ADS1115 (Canal A0)

  int16_t lecturaADC = ads.readADC_SingleEnded(0);

  

  // 4. APAGAR INMEDIATAMENTE para evitar polarización y daño celular

  digitalWrite(pinAlimentacion, LOW);

  // --- FIN DEL ALGORITMO ---

  // Procesamiento matemático para la consola

  float voltaje = (lecturaADC * 0.1875) / 1000.0;

  

  // Imprimir los resultados completos en el Monitor Serie

  Serial.print("Temp: "); Serial.print(temperatura); Serial.print("°C | ");

  Serial.print("Humedad: "); Serial.print(humedad); Serial.print("% | ");

  Serial.print("Lectura cruda: "); Serial.print(lecturaADC);

  Serial.print(" | Voltaje (V): "); Serial.println(voltaje, 4);

  

  // 5. Esperar hasta la siguiente medición (5 segundos para pruebas)

  delay(5000); 

}
