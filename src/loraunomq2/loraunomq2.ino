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

// Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void gasdetail()
{
    float sensor_volt;
    float sensorValue;
 
    sensorValue = analogRead(A0);
    sensor_volt = sensorValue/1024*5.0;
 
    Serial.print("Sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println("V");
    delay(1000);
 
}

void gasdetailr0()

{
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

  // Prepare payload of 7 byte of LED/Gas Dedektor
    byte payload[7];
    payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;
    payload[1] = (sensorValue);
    payload[2] = ((sensor_volt)*100);
    payload[3] = rgs >> 8;
    payload[4] = rgs;
    payload[5] = rto >> 8;
    payload[6] = rto;



  // Send it off
    ttn.sendBytes(payload, sizeof(payload));
 
    delay(1000);
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
  
  gasdetailr0();

  delay(10000);
}