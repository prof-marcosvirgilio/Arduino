#include <Servo.h>
// Porta Digital 6 PWM do SERVO
#define SERVO 6 
//Portas do sensor de cor
#define  s0 8       
#define s1 9
#define s2 10
#define s3 11
#define  out 12

//variaveis RGB
int vRed, vGreen, vBlue, vRGB = 0;
//Objeto servo       
Servo s; 
// Posicao Servo
int pos; 

void  setup() 
{
  Serial.begin(9600);  
  //pinos do sensor de cor
   pinMode(s0,OUTPUT);    
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);
   //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
   //LOW/LOW is off HIGH/LOW is 20% and  LOW/HIGH is  2%
   digitalWrite(s0,HIGH); 
   digitalWrite(s1,HIGH); 

  //SERVO
  s.attach(SERVO);
  // Inicia motor posição zero
  s.write(0);    
}


void loop()                 
{
   //S2/S3  levels define which set of photodiodes we are using LOW/LOW is for RED
   digitalWrite(s2,LOW);        
   digitalWrite(s3,LOW);
   //Executing GetData function to  get the value
   vRed=pulseIn(out,LOW);
   delay(10);
  //S2/S3  levels define which set of photodiodes we are using LOW/HIGH  is for Blue
   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   //Executing GetData function to  get the value
   vBlue=pulseIn(out,LOW);
   delay(10);
   //S2/S3  levels define which set of photodiodes we are using HIGH/HIGH is for green 
   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   //Executing GetData function to  get the value
   vGreen=pulseIn(out,LOW);
   delay(10);
  // Serial.println("R "+ (String)vRed + " G " + (String)vGreen + " B " + (String)vBlue);
  vRGB = vRed + vGreen + vBlue;
  Serial.println("RGB "+ (String) vRGB);
   
   delay(180);
   //VERMELHO
  if ( vRGB > 150 and vRGB < 200 ){
    Serial.println("Vermelho");
    //posiciona servo no valor 30
    s.write(0);
  } else {
    //VERDE
    if (vRGB > 100 and vRGB <= 150){
      Serial.println("Verde");
      //posiciona servo no valor 55
      s.write(25);    
    } else { 
      //BRANCA
      if ( vRGB < 100){
        Serial.println("Branco");
        //posiciona servo no valor 80
        s.write(55);
      }
    }
  }                    
   //Every 3s we select  a photodiodes set and read its data
   delay(2500);
   // Inicia motor posição zero
   
}


