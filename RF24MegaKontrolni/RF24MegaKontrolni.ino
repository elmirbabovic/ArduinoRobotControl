
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
const int analogInPin1 = A4;
const int analogInPin2 = A5;
String poruka="TST-123456";
String ulazSaSerijskogPorta = ""; 
bool krajUlazaSaSerijskogPorta = false;
char tekstZaSlanje[60];
/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"C1","R1","R2","R3","R4"};

// Used to control whether this node is sending or receiving
bool role = 1;
unsigned long naprnaz=127,lijdes=127;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Start kontrolnog"));
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[2]);
    radio.openReadingPipe(1,addresses[0]);
  }
  
  // Start the radio listening for data
  radio.startListening();
  radio.stopListening();
}

void loop() {
    
if(krajUlazaSaSerijskogPorta){
  //Serial.println("String: "+ulazSaSerijskogPorta);
/*  for(int i = 0; i<sizeof(ulazSaSerijskogPorta);i++)
{tekstZaSlanje[i]=ulazSaSerijskogPorta[i];
  }*/
  ulazSaSerijskogPorta.toCharArray(tekstZaSlanje,60);
  //int izbor = ulazSaSerijskogPorta.substring(1,2).toInt();
  ulazSaSerijskogPorta="";
   //radio.openWritingPipe(addresses[izbor]);
   //radio.openReadingPipe(1,addresses[0]);
 // Serial.print("char[] = (");
// Serial.print(tekstZaSlanje);
 //Serial.println(")");
 //ulazSaSerijskogPorta.toCharArray(tekstZaSlanje,50);
 int s = sizeof(tekstZaSlanje);
  //Serial.println("s: "+ String(s));
  
 bool a=radio.write(&tekstZaSlanje, s);
 //Serial.println("povratna : "+ String(a));
//radio.flush_rx();
//radio.flush_tx();

 delay(100);
 krajUlazaSaSerijskogPorta=false;
/*for(int i = 0; i<50;i++)
{tekstZaSlanje[i]="\0";
  }*/
}
        /*
  naprnaz=analogRead(analogInPin1);
  lijdes=analogRead(analogInPin2);
 naprnaz = map(naprnaz, 0, 1023, 0, 500);
 lijdes= map(lijdes, 0, 1023, 0, 500);
 
   Serial.println(naprnaz);
    Serial.println(lijdes);
  if(naprnaz<240)
  {
  naprnaz=map(naprnaz, 0, 240, 255, 0);
  naprnaz*=10;
  naprnaz+=1;
     Serial.println(F("Ravno"));
     if (!radio.write(&naprnaz, sizeof(unsigned long) )){
       Serial.println(F("failed"));
     }
        delay(5);
  }
  else if(naprnaz>260)
  {
  naprnaz=map(naprnaz, 260, 500, 0, 255);
  naprnaz*=10;
  naprnaz+=2;
     Serial.println(F("Ravno"));
     if (!radio.write(&naprnaz, sizeof(unsigned long) )){
       Serial.println(F("failed"));
     }
      delay(5);
  }
  else
  {

      if(lijdes<240)
      {
      lijdes=map(lijdes,0, 240, 255, 0);
      lijdes*=10;
      lijdes+=3;
      Serial.println(F("Bocno"));
   if (!radio.write(&lijdes, sizeof(unsigned long) )){
       Serial.println(F("failed"));
     }
    delay(5);
      }
      else if(lijdes>260)
      {
      lijdes = map(lijdes, 260, 500, 0, 255);
      lijdes*=10;
      lijdes+=4;
    Serial.println(F("Bocno"));
   if (!radio.write(&lijdes, sizeof(unsigned long) )){
   Serial.println(F("failed"));
     }
    delay(5);
      }
      else
      {
    
      }

  }


  if((lijdes>=240&&lijdes<=260)&&(naprnaz>=240&&naprnaz<=260))
  {
  naprnaz*=0;
  naprnaz+=5; 
  lijdes*=0;
  lijdes+=6;
  Serial.println(F("Stop"));
   if (!radio.write(&lijdes, sizeof(unsigned long) )){
    Serial.println(F("failed"));
     }
    delay(5);  
  }
  

    radio.stopListening();                                    // First, stop listening so we can talk.
    


    Serial.println(naprnaz);
    Serial.println(lijdes);
*/

} // Loop

void serialEvent() {

  while (Serial.available()) {
  //  int velicinaPoruke = Serial.available();
    // get the new byte:     
/*  for(int i=0; i<velicinaPoruke; i++)
{
   tekstZaSlanje[i] = Serial.read();
   tekstZaSlanje[i+1] = '\0'; 
} */
    char inChar = (char)Serial.read();
  // tekstZaSlanje[i]=(char)Serial.read();

    // add it to the inputString:
   ulazSaSerijskogPorta +=  inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      krajUlazaSaSerijskogPorta = true;
    }
 
  } 

 //ulazSaSerijskogPorta="";
} 
