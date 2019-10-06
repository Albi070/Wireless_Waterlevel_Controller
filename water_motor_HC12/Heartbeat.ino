void heartbeat()
{
 static int heart = LOW;
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
