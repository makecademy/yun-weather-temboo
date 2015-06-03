// Include required libraries
#include <Bridge.h>
#include <Temboo.h>
#include <Process.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Contains Temboo account information
#include "TembooAccount.h" 

// Variables
int lightLevel;
float humidity;
float temperature;
unsigned long time;

// Process to get the measurement time
Process date;

// Your Google Docs data
const String GOOGLE_CLIENT_ID = "your-google-client-id";
const String GOOGLE_CLIENT_SECRET = "your-google-client-secret";
const String GOOGLE_REFRESH_TOKEN = "your-google-refresh-token";

const String SPREADSHEET_TITLE = "your-spreadsheet-title";

// Include required libraries
#include "DHT.h"

// DHT11 sensor pins
#define DHTPIN 8 
#define DHTTYPE DHT11

// DHT & BMP instances
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// Debug mode ?
boolean debug_mode = false;

void setup() {
  
  // Start Serial
  if (debug_mode == true){
    Serial.begin(115200);
    delay(4000);
    while(!Serial);
  }
  
  // Initialize DHT sensor
  dht.begin();

  // Start bridge
  Bridge.begin();
  
  // Start date process
  time = millis();
  if (!date.running())  {
    date.begin("date");
    date.addParameter("+%D-%T");
    date.run();
  }

  if (debug_mode == true){
    Serial.println("Setup complete. Waiting for sensor input...\n");
  }
  
  // Initialise the sensor
  if(!bmp.begin())
  {
    while(1);
  }
}

void loop() {
  
  // Measure the humidity & temperature
  humidity = dht.readHumidity();
    
  // Measure light level
  int lightLevel = analogRead(A0);
  
  // Measure pressure & temperature from BMP sensor
  sensors_event_t event;
  bmp.getEvent(&event);
  float pressure = event.pressure;
    
   bmp.getTemperature(&temperature);

   float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
   float altitude;
   altitude = bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure,
                                        temperature); 

  if (debug_mode == true){
    Serial.println("\nCalling the AppendRow Choreo...");
  }
  
  // Append data to Google Docs sheet
  runAppendRow(humidity, lightLevel, pressure, temperature, altitude);
        
  // Repeat every 10 minutes
  delay(600000);
}

// Function to add data to Google Docs
void runAppendRow(float humidity, int lightLevel, 
  float pressure, float temperature, float altitude) {
  TembooChoreo AppendRowChoreo;

  // Invoke the Temboo client
  AppendRowChoreo.begin();

  // Set Temboo account credentials
  AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
  AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);
  
  // Identify the Choreo to run
  AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");

  // your Google Client ID
  AppendRowChoreo.addInput("ClientID", GOOGLE_CLIENT_ID);

  // your Google Client Secret
  AppendRowChoreo.addInput("ClientSecret", GOOGLE_CLIENT_SECRET);

  // your Google Refresh Token
  AppendRowChoreo.addInput("RefreshToken", GOOGLE_REFRESH_TOKEN);

  // the title of the spreadsheet you want to append to
  AppendRowChoreo.addInput("SpreadsheetTitle", SPREADSHEET_TITLE);
  
  // Restart the date process:
  if (!date.running())  {
    date.begin("date");
    date.addParameter("+%D-%T");
    date.run();
   }
  
  // Get date
  String timeString = date.readString(); 
  
  // Format data
  String data = "";
  data = data + timeString + "," + 
  String(humidity) + "," + 
  String(lightLevel) + "," + 
  String(pressure) + "," + 
  String(temperature) + "," + 
  String(altitude);

  // Set Choreo inputs
  AppendRowChoreo.addInput("RowData", data);

  // Run the Choreo
  unsigned int returnCode = AppendRowChoreo.run();

  // A return code of zero means everything worked
  if (returnCode == 0) {
    if (debug_mode == true){
      Serial.println("Completed execution of the AppendRow Choreo.\n");
    }
  } else {
    // A non-zero return code means there was an error
    // Read and print the error message
    while (AppendRowChoreo.available()) {
      char c = AppendRowChoreo.read();
      if (debug_mode == true){ Serial.print(c); }
    }
    if (debug_mode == true){ Serial.println(); }
  }
  AppendRowChoreo.close();
}
