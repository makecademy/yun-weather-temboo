// Test sketch for the DHT11, BMP085 & photocell sensors

// Include required libraries
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Variables
int lightLevel;
float humidity;
float temperature;

unsigned long time;

// DHT11 sensor pins
#define DHTPIN 8 
#define DHTTYPE DHT11

// DHT & BMP instances
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
                                         
void setup(void)
{
 
  // Initialize DHT sensor
  dht.begin();
  
  // Init serial
  Serial.begin(115200);
  
  // Initialise the sensor
  if(!bmp.begin())
  {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
}
  
void loop(void)
{
  
    // Measure the humidity
    float humidity = dht.readHumidity();
    
    // Measure light level
    int lightLevel = analogRead(A0);
    
    // Measure pressure & temperature from BMP sensor
    sensors_event_t event;
    bmp.getEvent(&event);
    float pressure = event.pressure;
    
    float temperature;
    bmp.getTemperature(&temperature);

    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    float altitude;
    altitude = bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure,
                                        temperature); 
    
    // Print measurements
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Light level: ");
    Serial.println(lightLevel);
    Serial.print("Barometric pressure: ");
    Serial.println(pressure);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Altitude: ");
    Serial.println(altitude);
    Serial.println("");
    
    // Repeat 50 ms
    delay(50);
  
}
