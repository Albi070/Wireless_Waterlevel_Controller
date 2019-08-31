void pack(){
a="";
a=a+"M";
a=a+sendata._micros;
a=a+"V";
a=a+sendata.value;
a=a+"L";
a=a+sendata.level;
a=a+"P";
a=a+sendata.motor_pwr;
}

void transmit(){
static unsigned long previousMillis;
static unsigned long currentMillis;
currentMillis=millis();

 if (currentMillis - previousMillis >= transmitInterval)
  {
    Serial.println(a);
    previousMillis = millis();
  }
  
}
