# Diverse Links:
https://www.aeq-web.com/so-funktioniert-die-lora-payload-encoder-decoder-ttn/

https://www.bjoerns-techblog.de/2018/04/payload-sparen-im-ttn/


# Hier wird es zum Versand vorbereitet:
...
	float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit * RL
 
          /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio = RS_gas/0.10;  // ratio = RS/R0
          /*-----------------------------------------------------------------------*/

...

    int rgs = ((RS_gas)*100);
    int rto = ((ratio)*100);

   // Prepare payload of 7 byte of LED/Gas Dedektor
    byte payload[7];
    payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;
    payload[1] = (sensorValue);
    payload[2] = ((sensor_volt)*100); >>>> aus den float werden wird eine int Zahl 
   // Umwandeln von int in einen Payload pro Sensor (rgs , rto) von je 2 byte 
    payload[3] = rgs >> 8;
    payload[4] = rgs;
	payload[5] = rto >> 8;>> HEX 34 Hier wurde der wert ZB von 13333 auf 2 Byte aufgeteilt >> HEX 34 15
    payload[6] = rto; >> HEX 15
...

# Nun noch auf der TheThinkNetwork Console den Payload zur Applikation Anpassen
https://eu1.cloud.thethings.network/console/applications
# Hier lang:
Applications > End devices > "Applications" > "Applikation" > Payload formatters > Uplink :

...
function Decoder(bytes, port) {
  var led = (bytes[0]);
  var sensor = (bytes[1]);
  var s_volt = (bytes[2]);
  var ratio = (bytes[3])<<8 | bytes [4];von HEX 34 15  zur 13333 
  var rsr0 = (bytes[5])<<8 | bytes [6];
  
     return {
      LED: led ,
      SENSOR: sensor,
      S_VOLT: s_volt/100,
      RATIO: ratio/100, von 13333 zur 133,33
      RSR0: rsr0/100,
  }   
}
...