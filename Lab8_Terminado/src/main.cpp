#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

unsigned long contador = 0;

void setup() {

    Serial.begin(115200);

    dht.begin();

    if (!bmp.begin(0x76)) {
        Serial.println("ERROR BMP280");
        while (1);
    }

    Serial.println("ESP32 INICIADO");
}

void loop() {

    contador++;

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    float pres = bmp.readPressure() / 100.0;
    float alt = bmp.readAltitude(1013.25);

    if (isnan(temp) || isnan(hum)) {
        Serial.println("ERROR DHT");
        delay(1000);
        return;
    }

    Serial.print(contador);
    Serial.print(",");

    Serial.print(temp, 2);
    Serial.print(",");

    Serial.print(pres, 2);
    Serial.print(",");

    Serial.print(hum, 2);
    Serial.print(",");

    Serial.println(alt, 2);

    delay(1000);
}