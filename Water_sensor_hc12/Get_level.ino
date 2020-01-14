void getlevel(){

wat_res = analogRead(A1);
  if (wat_res<300)
  {
    level = 1;
  }
  else level=0;

 wat_res = analogRead(A2);
  if (wat_res<300)
  {
    level = 2;
  }
  
  wat_res = analogRead(A3);
  if (wat_res<300)
  {
    level = 3;
  }
  
  wat_res = analogRead(A4);
  if (wat_res<300)
  {
    level = 4;
  }

  wat_res = analogRead(A5);
  if (wat_res<300)
  {
    level = 5;
  }
}
