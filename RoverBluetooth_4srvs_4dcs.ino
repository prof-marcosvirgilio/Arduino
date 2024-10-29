#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h> 

/* SERVOS SHIELD AFMOTOR*/
// Cria servo objeto para controlar um servo
Servo servoFD;
Servo servoFE;
// Variável para guardar a posição do servo
int posFD = 0;
int posFE = 0;  

/* MODULO BLUETOOTH */
//Uno  SoftwareSerial mySerial (2, 3);
//mega SoftwareSerial mySerial(51, 50);
SoftwareSerial bluetooth(51, 50);
// Stores response of bluetooth device  
char comando = "";                    
             
/* SHIELD AFMOTOR  */
AF_DCMotor et(3);
AF_DCMotor ef(2);
AF_DCMotor df(1);
AF_DCMotor dt(4);
int velocidade = 254;            
   
void setup()   
{  
  /* MODULO BLUETOOTH */ 
  Serial.begin(9600);
  Serial.println("Digite comandos para o celular");
  bluetooth.begin(9600); 

  // Conecta o servo no pino 10 para o servo objeto
  servoFD.attach(10);
  servoFE.attach(9);

  /* SHIELD AFMOTOR  */
  parar();
  
  direita();
} 

void parar(){
  ef.setSpeed(0);
  ef.run(RELEASE);
  et.setSpeed(0);
  et.run(RELEASE); 
  df.setSpeed(0);
  df.run(RELEASE);
  dt.setSpeed(0);
  dt.run(RELEASE);  
}

void frente(){
  ef.setSpeed(velocidade);
  ef.run(BACKWARD);
  df.setSpeed(velocidade);
  df.run(FORWARD);
  et.setSpeed(velocidade);
  et.run(BACKWARD);
  dt.setSpeed(velocidade);
  dt.run(BACKWARD);
}


void traz(){
  ef.setSpeed(velocidade);
  ef.run(FORWARD);
  df.setSpeed(velocidade);
  df.run(BACKWARD);
  et.setSpeed(velocidade);
  et.run(FORWARD);
  dt.setSpeed(velocidade);
  dt.run(FORWARD);
}

void direita(){
  // Aumenta o ângulo de 0 graus até X graus
  /*for(int pos = 0; pos <= 15; pos += 1) 
  {
    servoFD.write(pos);
    delay(15);
  }*/
  // Diminui o ângulo de X graus até 0 graus
  /*for(int pos = 15; pos>=0; pos-=1)
  {*/
    
    //servoFE.write(0);
    //delay(1000);
    //servoFD.write(0);
    //delay(1000);
  //}
}

void centro(){
  
}


void loop()  
{  
  // Read device output if available.
  while (bluetooth.available()) {  
    comando = (char)bluetooth.read();
    delay(2);
    Serial.println(comando);  
    switch (comando){
      case 'f':  
        frente();
        Serial.println("frente...");
      break;
      case 'p':
        parar();
        Serial.println("parar...");
      break;
      case 't':
        traz();
        Serial.println("traz...");
      break;
      case 'd':
        //direita();
        Serial.println("direita...");
      break;
      case 'e':
        //esquerda();
        Serial.println("esquerda...");
      break;
      default : 
        parar();
        Serial.println("parar default...");
      break;
    }
    delay(1000);
    comando = ""; // No repeats  
    parar();
  }  
  
  // Read user input if available.  
  if (Serial.available())
  {  
    delay(10); // The DELAY!  
    bluetooth.write(Serial.read());  
  }  
   
}// END loop()  