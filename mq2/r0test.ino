void setup() {
    Serial.begin(9600);
}
 
void loop() {
    float sensor_volt;
    float RS_air; //  moeglichst in sauberer Luft ermitteln
    float R0;  // Wert von R0 in H2
    float sensorValue;
 
  // Den Wert ueber 100 Messungen ermitteln
    for(int x = 0 ; x < 100 ; x++)
    {
        sensorValue = sensorValue + analogRead(A0);
    }
    sensorValue = sensorValue/100.0;
 
 
    sensor_volt = sensorValue/1024*5.0;
    RS_air = (5.0-sensor_volt)/sensor_volt; // omit * RL
    R0 = RS_air/9.8; // Das Verhältnis von RS/R0 beträgt 9,8 in einer klaren Luft von Tabelle (Gefunden mit WebPlotDigitizer)
 
    Serial.print("sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println("V");
 
    Serial.print("R0 = ");
    Serial.println(R0);
    delay(1000);
 
}
