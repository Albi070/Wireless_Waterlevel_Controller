void getlevel(){

wat_res = analogRead(A1);
  if (wat_res<500)
  {
    level = 1;
  }

 wat_res = analogRead(A2);
  if (wat_res<500)
  {
    level = 2;
  }
  
  wat_res = analogRead(A3);
  if (wat_res<500)
  {
    level = 3;
  }
  
  wat_res = analogRead(A4);
  if (wat_res<500)
  {
    level = 4;
  }

  wat_res = analogRead(A5);
  if (wat_res<500)
  {
    level = 5;
  }
}
