void receive()
{//This Function Loads the Sensor Struct in the global space
 //with data received from HC12.
 
  static unsigned long previousMillis = 0;
  static unsigned long currentMillis = 0;
  static bool error = false;
  currentMillis = millis();
  while (HC12.available())
  {Serial.println(a);
   // Serial.println("REceiving");
    a = HC12.readString();
    Serial.println(a);
    previousMillis = currentMillis;
  }

  if ((currentMillis - previousMillis) >= 3000)
  {
    error = true;
    digitalWrite(conn_led,LOW);
  }
  else
  {
    error = false;
    digitalWrite(conn_led,HIGH);
  }

  if (error == true)
  {
    sendata.motor_pwr = false;
    motor_pwr = false;
  }
}
