/*
Second eteration for Waterlevel controller
created by ALBERT P JOSHI
*/

#include <SPI.h>
#include "RF24.h"

//For RADIO
 byte addresses[][6] = {"1Node","2Node"};
RF24 radio(8,10);
int conn_led=A5;                  //Led showing network connectivity
unsigned long currentRxTime;
unsigned long previousRxTime;
unsigned long rxThreshold=1000;
int rxError;

//For Heart
const int ledPin =  A3;
const int ledPinGnd=A4;
int heart = LOW;
unsigned long previousMillis = 0;
unsigned long currentMillis  = 0;
const long interval = 1000;


//For CurrentSensor
int sensor=A1;
double current=0;
double set_current=37805;
double max_current=37805;
double adc=0;

//For Motor
int motor =A2;
bool motor_pwr=LOW;

//For storing Level
int level;



struct sensorStruct
{
  unsigned long _micros; //Starting time in microseconds.
  float value;           //ADC value given out from waterLevel sensor.
  int level;             //Stores the current level of water in tank.
  bool motor_pwr=0;      //Determines wheather to switch the motor on/off.
} sendata;           //Struct for receiving sensor data 

struct motorStruct
{
  double current;
  int state;
} motdata;           //Struct for sending and storing motor status. 

void radioInt(){
  radio.begin();
  if(radio.isChipConnected())
     Serial.print("HARDWARE CONNECTED");
    
    else
    { 
      digitalWrite(motor,LOW);      
      Serial.print("HARDWARE ERROR");  
    }
    
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();
}

void setup() {
  pinMode(ledPinGnd,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(conn_led,OUTPUT);
  digitalWrite(ledPinGnd,LOW);
 Serial.begin(9600);
  pinMode(sensor,INPUT);
  pinMode(motor,OUTPUT);
  digitalWrite(motor,LOW);
  digitalWrite(ledPin,LOW);
 radioInt();
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

void receive(){
   
 if( radio.available())
     { currentRxTime=millis();
      while (radio.available()) {                                   // While there is data ready
       radio.read( &sendata, sizeof(sendata) );                    // Get the payload  
      }
      Serial.print(sendata._micros);
  }
  if((currentRxTime-previousRxTime>=rxThreshold)||(currentRxTime==previousRxTime)){
    rxError=1;
    digitalWrite(conn_led,LOW);
  }
  else{
    rxError=0;
    digitalWrite(conn_led,HIGH);
      }
      
      Serial.print("   ");
      Serial.print(currentRxTime);
      Serial.print("   ");
      Serial.print(previousRxTime);
      Serial.print("   ");
      Serial.println(rxError);
      previousRxTime=currentRxTime;
}

void process(){
  level = sendata.level;
 
 if(sendata.motor_pwr==1){
  motor_pwr=1;
 }
 
 if(sendata.motor_pwr==false){
  motor_pwr=0;
 }
motor_pwr=sendata.motor_pwr;
 
}

void handlePower(){

  if(motor_pwr==1){
  digitalWrite(motor,HIGH);
  }
  else
  {digitalWrite(motor,LOW);}
  
  if(current>set_current)
  {
    digitalWrite(motor,LOW);
    motor_pwr=0;
    sendata.motor_pwr=0;
  }
  
}

void getMotorStat(){
 for(int i=0;i<250;i++)
  {adc=analogRead(sensor);
    if(max_current<adc)
      max_current=adc;
  }
 
  max_current= max_current-512;
  current=(float)(((max_current/1024)*5000)*1000)/66;
  

  if(current<20000);  //under current

    if(current>60000); //over current
 }

void loop() {
heartbeat(); 
getMotorStat();
receive();
process();
getMotorStat();
handlePower();
 // Serial.print("LEVEL: ");
 // Serial.print(level);
 // Serial.print("  ");
 // Serial.print("MotorPower: ");
 // Serial.print(sendata.motor_pwr);
 // Serial.print("  ");
 // Serial.print("Current: ");
 // Serial.println(current);
}
