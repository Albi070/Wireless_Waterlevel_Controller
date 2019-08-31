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

void handlePower()
{

  if (motor_pwr == 1)
  {
    digitalWrite(motor, HIGH);
  }
  else
  {
    digitalWrite(motor, LOW);
  }

  if (current > set_current)
  {
    digitalWrite(motor, LOW);
    motor_pwr = 0;
    sendata.motor_pwr = 0;
  }
}

void getMotorStat()
{
  for (int i = 0; i < 250; i++)
  {
    adc = analogRead(sensor);
    if (max_current < adc)
      max_current = adc;
  }

  max_current = max_current - 512;
  current = (float)(((max_current / 1024) * 5000) * 1000) / 66;

  if (current < 20000)
    ; //under current

  if (current > 60000)
    ; //over current
}


void heartbeat()
{
int heart = LOW;
static unsigned long previousMillis = 0;
static unsigned long currentMillis = 0;
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    if (heart == LOW)
    {
      digitalWrite(ledPin, LOW);
      heart = HIGH;
    }
    else

        if (heart = HIGH)
    {
      digitalWrite(ledPin, HIGH);
      heart = LOW;
    }
    previousMillis = millis();
  }
}


void process()
{
  for (int i = 0; i < a.length(); i++)
  {
    if (isAlpha(a.charAt(i)))
    {
      previousAlpha = currentAlpha;
      currentAlpha = a.charAt(i);

      if (previousAlpha == 'M')
      {
        sendata._micros = temp.toDouble();
      }

      if (previousAlpha == 'V')
      {
        sendata.value = temp.toDouble();
      }

      if (previousAlpha == 'L')
      {
        sendata.level = temp.toInt();
      }

      if (previousAlpha == 'P')
      {
        sendata.motor_pwr = temp.toInt();
      }
      temp = "";
    }
    else
    {
      temp += a.charAt(i);
    }
  }

  level = sendata.level;

  if (sendata.motor_pwr == 1)
  {
    motor_pwr = 1;
  }

  if (sendata.motor_pwr == false)
  {
    motor_pwr = 0;
  }
  motor_pwr = sendata.motor_pwr;
}

void receive()
{
static unsigned long previousMillis=0;
static unsigned long currentMillis=0;
static bool error=false;
currentMillis=millis();
  while (Serial.available())
  {
    a = Serial.readString();
    previousMillis=currentMillis;
  }

  
  if((currentMillis-previousMillis)>=1000){
     error=true;
      }
  else{
    error=false;}

if(error==true)
{sendata.motor_pwr=false;
motor_pwr=false;
  }
  
  
}
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
