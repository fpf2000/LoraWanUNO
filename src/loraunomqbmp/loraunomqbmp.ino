#include <TheThingsNetwork.h>
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

// Set your AppEUI and AppKey
//Die Datei config.h bitte mit den Zugangsdaten erstellen und in dem src VZ speichern:
//const char *appEui = "You-APPEUI";
//const char *appKey = "You-APPKEY";

#include "config.h"


#define loraSerial Serial1
#define debugSerial Serial
 
// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868
 
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

#define MQ2pin (0)

float sensorValue;  //variable to store sensor value

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-2 to warm up
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);

// Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void tempbmp() {
  debugSerial.println("-- gasDetailR0");

  float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit * RL
 
          /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio = RS_gas/0.10;  // ratio = RS/R0
          /*-----------------------------------------------------------------------*/
    Serial.print("Sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);
 
    Serial.print("\n\n");

    int rgs = ((RS_gas)*100);
    int rto = ((ratio)*100);

  sensors_event_t temp_event, pressure_event;
  float temperature = (temp_event.temperature);
  float airpressure = (pressure_event.pressure);
  
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();

  int tmp = ((int)(temperature * 100))+5000;
  int pre = (int)(airpressure * 100);

  //Prepare payload of 7bis10 byte of LED/Gas Dedektor
    byte payload[9];
    //uint8_t payload[8];
    payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;
    payload[1] = (sensorValue);
    payload[2] = ((sensor_volt)*100);
   // Umwandeln von int in einen Payload pro Sensor (rgs , rto) von je 2 
    payload[3] = rgs >> 8;
    payload[4] = rgs;
    payload[5] = rto >> 8;
    payload[6] = rto;
    payload[7] = tmp >> 8;
    payload[8] = tmp;
    payload[9] = pre >> 8;
    payload[10] = pre;
  
  
    // Send it off
   ttn.sendBytes(payload, sizeof(payload));
 
 

  delay(2000);
}

void loop()
{
  
  debugSerial.println("-- LOOP");
  
  sensorValue = analogRead(MQ2pin); // read analog input pin 0

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  if(sensorValue > 200)
  {
    Serial.print(" | Smoke detected!");
  }
  
  Serial.println("");
  
  //gasdetailr0();

  tempbmp();

  delay(20000);
}