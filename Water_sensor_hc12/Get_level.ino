void getlevel(){

  wat_res = analogRead(A0);           //Read voltage from pin A0

  if ((240 <= wat_res) && (wat_res <= 265))
  {
    level = 0;
  }

  if ((270 <= wat_res) && (wat_res <= 310))
  {
    level = 1;
  }

  if ((315 <= wat_res) && (wat_res <= 380))
  {
    level = 2;
  }

  if ((400 <= wat_res) && (wat_res <= 490))
  {
    level = 3;
  }

  if ((520 <= wat_res) && (wat_res <= 700))
  {
    level = 4;
  }

  if ((900<= wat_res) && (wat_res <= 1000))
  {
    level = 5;
  }

  if (wat_res < 140 || wat_res > 650)   //if probe not connected properly or incorrect values fed
  {
    return 0;
  }
}
