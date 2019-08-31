/*
Second eteration for Waterlevel controller
created by ALBERT P JOSHI
*/

#include <SPI.h>
#include "RF24.h"


//For WaterLevel
int sensor =A0;
double wat_res=0.0;
int level=2;

//For RADIO communtication
byte addresses[][6] = {"1Node", "2Node"};//Address of pipes we are 1Node
RF24 radio(8, 10);                       //spi pins to which radio hardware is connected
int txError=0;                           //Variable becomes 1 when packets are not acknowledged
int txrate=200;                          //interval between transmission in milli seconds
int connStatusLed=A5;                    //This led lights up when connection is proper and blinks proportionally with tx rates
int txErrorLed =A3;                      //When time between packets are higher than threshold period
int txErrorThreshold=2000;               //time between packets for error check, DEFAULT IS @ 2 SECONDS
unsigned long currentErrorTime=0;        //Millis at error
unsigned long previousErrorTime=0;       //Millis at previous error

//HeartBeat to show that the circuit is executing the loop,blinks every 1 sec
const int ledPin =  A1;
const int tempHeartGround =A2;
int heart = LOW;
unsigned long previousMillis = 0;
unsigned long currentMillis  = 0;
const long interval = 1000;

struct sensorStruct {
  unsigned long _micros;
  float value=100;
  int level;
  bool motor_pwr = 0;
} sendata;


void radioInt()
{
  
    //Serial.println("INSiDE init"); 
  
  radio.begin();
   // Serial.println("passed begin");
  
  sendata.value = 0.00;
   // Start the radio listening for data
  
  radio.startListening();
    //Serial.println("passed listening");
 
  radio.openWritingPipe(addresses[0]);
    //  Serial.println("Passed writing pipe");
  delay(200);
  
 radio.openReadingPipe(1, addresses[1]);
//  Serial.println("Passed reading pipe");
 delay(200);

}


void setup() {
 Serial.begin(9600);
 sendata.value = 0.00;  
 pinMode(ledPin,OUTPUT);
 pinMode(sensor,INPUT);
 pinMode(tempHeartGround,OUTPUT);
 digitalWrite(tempHeartGround,LOW);
 
 //Serial.println("init starting");
 
 radioInt();
 
 // Serial.println("Got back");
}



void getlevel(){

  wat_res = analogRead(A0);           //Read voltage from pin A0

  if ((240 <= wat_res) && (wat_res <= 265))
  {
    level = 0;
  }

  if ((270 <= wat_res) && (wat_res <= 310))
  {
    level = 1;
  }

  if ((315 <= wat_res) && (wat_res <= 380))
  {
    level = 2;
  }

  if ((400 <= wat_res) && (wat_res <= 490))
  {
    level = 3;
  }

  if ((520 <= wat_res) && (wat_res <= 700))
  {
    level = 4;
  }

  if ((900<= wat_res) && (wat_res <= 1000))
  {
    level = 5;
  }

  if (wat_res < 140 || wat_res > 650)   //if probe not connected properly or incorrect values fed
  {
    return 0;
  }
}


void heartbeat(){


  currentMillis=millis();
  if(currentMillis-previousMillis>=interval)
  {
    if(heart==LOW)
    {
      digitalWrite(ledPin,LOW);
      heart=HIGH;
    }else

    if(heart=HIGH)
    {
      digitalWrite(ledPin,HIGH);
      heart=LOW;
    }
    previousMillis=millis();
    }
}

void transmit(){
 radio.stopListening();
 
  if(!radio.write( &sendata, sizeof(sendata)))
  {
    txError=1; //Ack fail catching
    }
    else{
    txError=0;}
    
    radio.startListening();
}

void process(){
  sendata.value=wat_res;
  sendata._micros=micros();
  sendata.level=level;
  if(level<=1)
  sendata.motor_pwr=1;
  else
  if(level==5)
  sendata.motor_pwr=0;
}

void txErrorInd(){
  if (txError==1)
  {
    currentErrorTime=millis();
    if(currentErrorTime-previousErrorTime>=txErrorThreshold)
    {
      digitalWrite(txErrorLed,HIGH);
    }
      previousErrorTime=currentErrorTime;
  }
  else
  {
    digitalWrite(txErrorLed,LOW);
    previousErrorTime=millis();
  }
}

void loop() {
heartbeat();
getlevel();
process();
transmit();
Serial.print(sendata.value);
Serial.print(":  ");
Serial.print(sendata.level);
Serial.print("  ");
Serial.println(sendata.motor_pwr);
} // Loop
