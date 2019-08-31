struct sensorStruct
{
  unsigned char _micros=255;
  unsigned char value = 100;
  unsigned char level=1;
  bool motor_pwr = 0;
} sendata;

char *a[4]=(char*)sendata ;



void setup() {
  Serial.begin(9600);
  Serial.print(a);
}

void loop() {
  // put your main code here, to run repeatedly:

}
