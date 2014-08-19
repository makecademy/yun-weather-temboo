# Cloud-Connected Weather Station

Link to the complete article: [http://www.openhomeautomation.net/yun-weather-temboo/](http://www.openhomeautomation.net/yun-weather-temboo/)

## Hardware Requirements

* Arduino Yun board
* [DHT11 sensor](https://github.com/adafruit/DHT-sensor-library)
* BMP085 sensor
* Photocell
* 10K Ohm resistor
* Breadboard and jumper wires

## Software Requirements

* Download & install the [Arduino IDE 1.5.x](http://arduino.cc/en/Main/Software#toc3)
* Download & install the following Arduino libraries
 * [DHT library]()
 * [BMP085 library](https://github.com/adafruit/Adafruit-BMP085-Library)
 * [Unified sensor library](https://github.com/adafruit/Adafruit_Sensor)
* Create a Google Drive account 
* Set up an account on [Temboo](https://www.temboo.com/) and write down your account name, app name, and API key

## Hardware Configuration

1. Connect the Arduino Yun +5V pin to the red rail on the breadboard, and the ground pin to the blue rail
1. Connect pin number 1 of the DHT11 sensor to the red rail on the breadboard, and pin number 4 the blue rail
1. Connect pin number 2 to pin number 8 of the Arduino Yun
1. Connect the 4.7k Ohm between pin number 1 and 2 of the sensor
1. Place the photocell in series with the 10k Ohm resistor on the breadboard
1. Connect the other end of the photocell to the red rail on the breadboard, and the other end of the resistor to the ground
1. Connect the common pin to the Arduino Yun analog pin A0
1. Connect the VIN pin of the BMP085 to the +5V, GND to Ground, SCL to Arduino Yun pin number 3, and SDA pin to Arduino Yun pin number 2

## Test

1. Get the sensors test code at [https://github.com/openhomeautomation/yun-weather-temboo](https://github.com/openhomeautomation/yun-weather-temboo)
1. Upload the code to the Arduino Yun
1. Open the Serial monitor to check the results

## Cloud Weather Station

1. Create a new Google Docs spreadsheet at the root of your Google Drive, and give names to the columns inside the first row: Time, Humidity, Light Level, Pressure, Temperature, Altitude
1. Get the weather station code at [https://github.com/openhomeautomation/yun-weather-temboo](https://github.com/openhomeautomation/yun-weather-temboo)
1. Modify the `TembooAccount.h` file with your Temboo credentials
1. Modify the Arduino sketch with your Google account information and your Google Docs spreadsheet name
1. Upload the code to the Arduino Yun
1. Check your Google Docs spreadsheet again to see the results being logged in live