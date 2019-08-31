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
