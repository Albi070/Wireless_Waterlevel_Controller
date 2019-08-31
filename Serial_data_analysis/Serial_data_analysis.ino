//CURRENT sample data
//M124070V100.00L1P0E
 

String a="M124070V100.00L1P0E";
String temp;
char previousAlpha,currentAlpha;
int l;

struct sensorStruct {
  unsigned long _micros;
  float value=100;
  int level=1;;
  bool motor_pwr = 0;
} sendata;

void setup() {
Serial.begin(9600);
Serial.setTimeout(10);

}

void loop() {
//sendata._micros=millis();
//transmit();
//Serial.println(a);
//delay(2000);
 
receive();
Serial.println(sendata._micros);
Serial.println(sendata.value);
Serial.println(sendata.level);
Serial.println(sendata.motor_pwr);
delay(5000);

}

void transmit(){
a="";
a=a+"M";
a=a+sendata._micros;
a=a+" V";
a=a+sendata.value;
a=a+" L";
a=a+sendata.level;
a=a+" P";
a=a+sendata.motor_pwr;
}

void receive(){

for(int i=0;i<a.length();i++)
{
   if(isAlpha(a.charAt(i)))
 { previousAlpha=currentAlpha;
   currentAlpha=a.charAt(i);

   if(previousAlpha=='M')
   {
    sendata._micros= temp.toDouble();
   }

   if(previousAlpha=='V')
   {
    sendata.value= temp.toDouble();
   }

   if(previousAlpha=='L')
   {
    sendata.level= temp.toInt();
   }
   
   if(previousAlpha=='P')
   {
    sendata.motor_pwr= temp.toInt();
   }
 temp="";
 }
 else
 {
   temp+=a.charAt(i);
 }

 
}
}
