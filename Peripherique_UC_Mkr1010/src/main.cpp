#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"
#include <Wire.h>

// Fonction 
void receiveEvent(int howMany)  ;

// Setup 
void setup()
{
	Serial.begin(9600);

	wifiConnect();  // Conncecter au wifi 
	MQTTConnect();  // connecter au broker mqtt 

	Serial.println("I2C Receiver");
	Wire.begin(4);  // debut communication I2C 
	Wire.onReceive(receiveEvent);  // apeler la fonction a chaque fois on recois une donnees  par I2C 
}


void loop(){}

// fonction appller a chaque fois y a une donnees envoyer par I2C du la part du controleur 
void receiveEvent(int howMany)      
{  
 	Payload = "";

	while(Wire.available())    // Tantque y a des donnees a recevoir via I2C 
	{
		char c = Wire.read();  // lire le caractere recu 
		Payload  += c;     // contruction de la chaine de caractere MQTT   
	}
	Serial.print("Chaine recue --> ");
	Serial.println(Payload);        // affichage de la chaine de caractere MQTT 
	sendPayload();     // Envoi de la chaine de caractere MQTT sur ThingsBoard 
	
}