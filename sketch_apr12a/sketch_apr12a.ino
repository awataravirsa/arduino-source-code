
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 4
#include <Adafruit_Sensor.h>

#define LED_TOO_COLD 21
#define LED_PERFECT 19
#define LED_TOO_HOT 22


char auth[] = "vhOqH8WITQX7kwkBqfQ9QMppRqaqZ0U4";
char ssid[] = "Awvirsa";
char pass[] = "picahehehe";

int speakerPin = 18;
int length = 1;


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}


void setup()
{

  Serial.begin(9600);
  Serial.println("DHT11 test!");

  // Debug console
  Serial.begin(9600);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  pinMode(speakerPin, OUTPUT);
  pinMode (21 , OUTPUT);
  pinMode (19 , OUTPUT);
  pinMode (22 , OUTPUT);
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  if (t <= 20) {
    Serial.println("Too cold!");
    digitalWrite(21, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (1000);
    digitalWrite(speakerPin, LOW);
    digitalWrite(21, LOW);
  }
  if (20 < t < 27) {
    Serial.println("Perfect temperature!");
    digitalWrite(19, HIGH);
    delay (2000);
    digitalWrite(19, LOW);
  }
  if (t >= 36) {
    Serial.println("Too hot!");
    digitalWrite(22, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (1000);
    digitalWrite(speakerPin, LOW);
    digitalWrite(22, LOW);
  }

  Blynk.run();
  timer.run();
}
