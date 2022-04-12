#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"
#include <Wire.h>

void receiveEvent(int howMany)  ;
void setup()
{
	Serial.begin(9600);
	while (!Serial);
	wifiConnect();
	MQTTConnect();

	Serial.println("I2C Receiver");
	Wire.begin(4);
	Wire.onReceive(receiveEvent);
}


void loop()
{
	
}


void receiveEvent(int howMany)      
{  
 	Payload = "";
	while(Wire.available())       
	{
		char c = Wire.read(); 
		Payload  += c;       
	}
	Serial.print("Chaine recue --> ");
	Serial.println(Payload);        
	sendPayload();     
	
}