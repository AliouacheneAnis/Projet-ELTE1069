// Ajout des libraires necessaire pour le projet 
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>                  
#include <LoRa.h>

// Declaration Variable string qui va contenir la chaine de caractere recu par LoraWan 
String payload ;


void setup() {

	Serial.begin(9600);
	Serial.println("LoRa Receiver");
    
	// communication Lorawan
	if (!LoRa.begin(915E6)) {
		Serial.println("Starting LoRa failed!");
		while (1);
	}

	// Debut communication I2C 
  	Wire.begin();                       

}


void loop() {

	// try to parse packet
	int packetSize = LoRa.parsePacket();

	if (packetSize) {

		 payload = ""; // initialisation

		 Serial.print("Received packet : ");

		// Lecture de packet Lorawan recu tantqu'il est disponible caractere par caractere et construction du string 
		while (LoRa.available()) {
			char c = LoRa.read(); 
			payload  += c;      
		}
		Serial.println(payload);  // Affichage dans le moniteur serie la chaine de caractere recu 

		Serial.print("\t with RSSI ");
		Serial.println(LoRa.packetRssi()); // affichage signal LoraWan 

        // Debut communication I2C sur l'adresse 4 afin d'envoyer la chaine de caractere vers le peripherique mkr1010 : envoi caractere par caracter (Tableau de caractere)
		Wire.beginTransmission(4);

		for (unsigned int i = 0; i < payload.length(); i++)
		{
			Wire.write(payload[i]); // Envoi par I2C le caractere dans la case i 
		}

		Wire.endTransmission(); // fin communication I2C 
		Serial.println("Envoie via I2C réussie");
	}
}