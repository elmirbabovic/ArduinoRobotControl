
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
char prijemniText[60] = "";
int robotID;

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
int radioNumber = 2;


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"C1","R1","R2","R3","R4"};

// Used to control whether this node is sending or receiving
bool role = 0;

void setup() {

  robotID=2; //1-4
  
  Serial.begin(115200);
  Serial.print(F("Start izvrsnog: Robot ID "));
  Serial.println(robotID);
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber==2){
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[2]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
 pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  /*
  pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  */
  digitalWrite(2,HIGH);
  delay(200);
  digitalWrite(2,LOW);
  delay(10);
  digitalWrite(3,HIGH);
  delay(200);
  digitalWrite(3,LOW);
  delay(10);
  digitalWrite(4,HIGH);
  delay(200);
  digitalWrite(4,LOW);
  delay(10);
  digitalWrite(5,HIGH);
  delay(200);
  digitalWrite(5,LOW);
  delay(10);
}

void loop() {
    radio.startListening();

    if( radio.available()){
      while (radio.available()) {  
    radio.read(&prijemniText, sizeof(prijemniText));
      }
      Serial.println(prijemniText);
      String prijemniString(prijemniText);
      int robotCharsStart = (robotID -1) * 10;
      int lijevoStart = robotCharsStart + 3;
      int desnoStart = robotCharsStart + 7;
      int izbor = prijemniString.substring(robotCharsStart+1,robotCharsStart+2).toInt();
      if(izbor==robotID){
      int desniKomanda=prijemniString.substring(lijevoStart,lijevoStart+3).toInt();
      int lijeviKomanda=prijemniString.substring(desnoStart,desnoStart+3).toInt();

      Serial.print("lijeviKomanda na 3 ");
      Serial.println(lijeviKomanda);
      analogWrite(3,lijeviKomanda);
      Serial.print("desniKomanda na 5 ");
      Serial.println(desniKomanda);
      analogWrite(5,desniKomanda);
   Serial.println(prijemniString);
      delay(100);
      digitalWrite(5,LOW);
     digitalWrite(3,LOW);
      }
   prijemniString="";
   for(int i=0; i<13;i++)
   {
      prijemniText [i]=' ';
   }
 
      
    }
     // Serial.println("Kraj komande");
//radio.flush_rx();
//radio.flush_tx();
  
   for(int i=0; i<13;i++)
   {
      prijemniText [i]=' ';
   }

} // Loop
