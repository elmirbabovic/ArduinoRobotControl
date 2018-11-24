
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

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
  Serial.begin(115200);
  Serial.println(F("Start izvrsnog"));
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_HIGH);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber==2){
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[3]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
    pinMode(2,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
  digitalWrite(2,HIGH);
  delay(200);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(200);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  delay(200);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  delay(200);
  digitalWrite(5,LOW);
}

void loop() {
    radio.startListening();
    unsigned long prijemnaPoruka;

    String priTex;
    char prijemniText[13] = "";
    if( radio.available()){
      while (radio.available()) {  
    radio.read(&prijemniText, sizeof(prijemniText));
      }
      Serial.println(prijemniText);
    }
     // Serial.println("Kraj komande");
/*  radio.flush_rx();
radio.flush_tx();*/
    
  /*  if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &prijemnaPoruka, sizeof(unsigned long) );             // Get the payload
      }*/
    /*  radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( &prijemnaPoruka, sizeof(unsigned long) );              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      Serial.print(F("Sent response "));
      Serial.println(prijemnaPoruka); 
 */

   //}
        //Serial.println(prijemnaPoruka); 
        /* 
if(prijemnaPoruka<10000)
{
if (prijemnaPoruka%10==6)
{
  Serial.println("Bocno stop");

    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
        analogWrite(10,0);
  analogWrite(11,0);
  
  }
else if (prijemnaPoruka%10==5)
{
  Serial.println("Ravno stop");

    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
            analogWrite(10,0);
  analogWrite(11,0);
 
  }
  else if (prijemnaPoruka%10==1)
{
  
  Serial.println("Naprijed");
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    analogWrite(10,prijemnaPoruka/10);
  analogWrite(11,prijemnaPoruka/10);
  }
    else if (prijemnaPoruka%10==2)
{
  Serial.println("Nazad");
    digitalWrite(3,HIGH);
      digitalWrite(5,HIGH);
          analogWrite(10,prijemnaPoruka/10);
  analogWrite(11,prijemnaPoruka/10);
  }
    else if (prijemnaPoruka%10==3)
{
  Serial.println("Lijevo");
    digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
          analogWrite(10,prijemnaPoruka/10);
  analogWrite(11,prijemnaPoruka/10);
  }
    else if (prijemnaPoruka%10==4)
{
  Serial.println("Desno");
    digitalWrite(2,HIGH);
      digitalWrite(5,HIGH);
      analogWrite(10,prijemnaPoruka/10);
  analogWrite(11,prijemnaPoruka/10);
  }
    else 
{
  Serial.println(prijemnaPoruka);
  }
}
//radio.stopListening();
delay(50);*/
} // Loop
