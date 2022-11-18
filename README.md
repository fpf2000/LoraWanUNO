# LoraWanUNO mit MQ2 Sensores
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

Im zweiten step wurde noch ein bmp Sensor (temparatur / luftdruck) angeschaltet.
Hierzu wurde die loraunobmp.ino erstellt.

Die Zugangsdaten zum TTN Netzwerk müssen in einer extra erstellten config.h datei
hinterlegt werden.

Jetzt werden die Werte ueber das TTN Netzwerk entsprechend uebermittelt.

Inzwischen gibt es hier im Git VZ auch eine Dokumentation 
https://github.com/fpf2000/LoraWanUNO/blob/main/Dok/LoraWan%20UNOV001.pdf