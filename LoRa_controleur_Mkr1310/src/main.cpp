#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>                  
#include <LoRa.h>

String payload ;
void receiveEvent(int howMany)  ;

void setup() {
	Serial.begin(9600);

	while (!Serial);

	Serial.println("LoRa Receiver");

	if (!LoRa.begin(915E6)) {
		Serial.println("Starting LoRa failed!");
		while (1);
	}
  	Wire.begin();                       

}

void loop() {
	// try to parse packet
	int packetSize = LoRa.parsePacket();
	if (packetSize) {
		 payload = "";
		// received a packet
		Serial.print("Received packet : ");

		// read packet
		while (LoRa.available()) {
			char c = LoRa.read(); 
			payload  += c;      
		}
		Serial.println(payload);
		// print RSSI of packet
		Serial.print("\t with RSSI ");
		Serial.println(LoRa.packetRssi());

		Wire.beginTransmission(4);
		for (unsigned int i = 0; i < payload.length(); i++)
		{
			Wire.write(payload[i]);
		}
		Wire.endTransmission();
		Serial.println("Envoie via I2C réussie");
	}
}