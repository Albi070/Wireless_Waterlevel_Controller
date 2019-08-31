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
