/* This code works with GY-31 TCS3200 TCS230 color sensor module
 *  It select a photodiode set and read its value (Red Set/Blue set/Green set) and displays  it on the Serial monitor
 * Refer to www.surtrtech.com for more details
 */

#define  s0 8       //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define  out 12

int vRed, vGreen, vBlue=0;        //This is where we're going to stock our values

void  setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and  LOW/HIGH is  2%
   
}


void loop()                 
{
   //S2/S3  levels define which set of photodiodes we are using LOW/LOW is for RED
   digitalWrite(s2,LOW);        
   digitalWrite(s3,LOW);
   //Executing GetData function to  get the value
   vRed=pulseIn(out,LOW);
   delay(20);
  //S2/S3  levels define which set of photodiodes we are using LOW/HIGH  is for Blue
   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   //Executing GetData function to  get the value
   vBlue=pulseIn(out,LOW);
   delay(20);
   //S2/S3  levels define which set of photodiodes we are using HIGH/HIGH is for green 
   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   //Executing GetData function to  get the value
   vGreen=pulseIn(out,LOW);
   delay(20);
   Serial.println("R "+ (String)vRed + " G " + (String)vGreen + " B " + (String)vBlue);
   if (vRed <= 25 and vGreen >= 20 and vBlue >= 20){
     Serial.println("Vermelho");
   }
   if (vRed <= 20 and vGreen <= 20 and vBlue <= 20){
     Serial.println("Verde");
   } 
   if (vRed >= 20 and vGreen >= 20 and vBlue <= 20){
     Serial.println("Azul");
   }
   //Every 2s we select  a photodiodes set and read its data
   delay(2000);
}


