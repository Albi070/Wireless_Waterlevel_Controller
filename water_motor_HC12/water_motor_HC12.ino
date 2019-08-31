/*
3rd eteration for Waterlevel controller
created by ALBERT P JOSHI
*/

#include <SPI.h>

//For RADIO
int conn_led = A5; //Led showing network connectivity


//For message processing
String a = "";
String temp = "";
char previousAlpha, currentAlpha;
int l=0;

//For Heart
const int ledPin = A3;
const int ledPinGnd = A4;

const long interval = 1000;

//For CurrentSensor
int sensor = A1;
double current = 0;
double set_current = 37805;
double max_current = 37805;
double adc = 0;

//For Motor
int motor = A2;
bool motor_pwr = LOW;

//For storing Level
int level;

struct sensorStruct
{
  unsigned long _micros; //Starting time in microseconds.
  float value;           //ADC value given out from waterLevel sensor.
  int level;             //Stores the current level of water in tank.
  bool motor_pwr = 0;    //Determines wheather to switch the motor on/off.
} sendata;               //Struct for receiving sensor data

struct motorStruct
{
  double current;
  int state;
} motdata; //Struct for sending and storing motor status.

void setup()
{
  pinMode(ledPinGnd, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(conn_led, OUTPUT);
  digitalWrite(ledPinGnd, LOW);
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
  digitalWrite(ledPin, LOW);
}










void loop()
{
  heartbeat();
  getMotorStat();
  receive();
  process();
  getMotorStat();
  handlePower();

}
