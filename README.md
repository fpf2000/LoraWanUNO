# LoraWanUNO
ARDUINO UNO OVER TheThingsNetwork LoraWan
Der TTN UNO wurde mit dem  MQ2 FC-22 GAS Sensor angeschaltet.

Anschließend wurde über die r0test.ino versucht eine
annäherung an die entspr. Gas Werte zu schaffen.
Anschließend wurde der ermittelte Wert in den Code mq2GasWerte.ino eingetragen.

Nun können Wir die Gas Konzentration und Typ anhand der Grafik
aus dem datenblatt des MQ2 Sensores ermitteln:

Zum Datenblatt  https://www.pololu.com/file/0J309/MQ2.pdf 

Den Code haben Wir Anschließend in den TTN Code loraunomq2.ino eingebunden und die 
Payload Werte entsprechend angepasst.

Jetzt werden die Werte ueber das TTN Netzwerk entsprechend uebermittelt.
