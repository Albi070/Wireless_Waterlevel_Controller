/*
Second eteration for Waterlevel controller
created by ALBERT P JOSHI
*/

#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 8); // RX, TX


//For WaterLevel
int wat_res = 0;
int level = 2;

String a;

//Transmission Details
unsigned long transmitInterval=100;

//HeartBeat to show that the circuit is executing the loop,blinks every 1 sec
const int ledPin = 4;
const int tempHeartGround = 5;
const short interval = 100;

struct sensorStruct
{
  unsigned long _micros;
  int value = 100;
  int level;
  bool motor_pwr = 0;
} sendata;



void setup()
{ HC12.begin(9600);
  Serial.begin(9600);
  sendata.value = 0.00;
  pinMode(ledPin, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(tempHeartGround, OUTPUT);
  digitalWrite(tempHeartGround, LOW);

}



void process()
{
  sendata.value = wat_res;
  sendata._micros = micros();
  sendata.level = level;
  if (level <= 1)
  {
    sendata.motor_pwr = 1; // @ major :: 
  }    
  else if (level == 5)
  { 
    sendata.motor_pwr = 0;
  }  
}



void loop()
{
  heartbeat();
  getlevel();
  process();
  pack();
  transmit();
} // Loop
