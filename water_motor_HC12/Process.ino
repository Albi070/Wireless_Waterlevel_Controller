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
