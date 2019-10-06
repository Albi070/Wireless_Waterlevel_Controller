/*
Second eteration for Waterlevel controller
created by ALBERT P JOSHI
*/

#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(8, 10); // RX, TX


//For WaterLevel
int sensor = A0;
int wat_res = 0;
int level = 2;

String a;

//Transmission Details
unsigned long transmitInterval=1500;

//HeartBeat to show that the circuit is executing the loop,blinks every 1 sec
const int ledPin = A1;
const int tempHeartGround = A2;
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
  pinMode(sensor, INPUT);
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
  else if (level == 4)
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
