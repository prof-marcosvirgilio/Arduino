#include <Stepper.h> 
 
const int stepsPerRevolution = 500; 

enum sentido_rotacao {HORARIO, ANTI_HORARIO};
 
//Inicializa a biblioteca utilizando as portas de 8 a 11 para 
//ligacao ao motor 
Stepper motorP1(stepsPerRevolution, 8,10,9,11); 
 
void setup() 
{ 
 //Determina a velocidade inicial do motor 
 motorP1.setSpeed(60);
 Serial.begin(9600); //Enviar e receber dados em 9600 baud
} 

void giraMotor(int graus, int velocidade, sentido_rotacao sentido){
  float referenciaUmGrau = 5.7;
  if (sentido == ANTI_HORARIO){
    referenciaUmGrau = referenciaUmGrau * -1;
  } 
  Serial.println(referenciaUmGrau);
  int steps = graus * referenciaUmGrau; 
  motorP1.setSpeed(velocidade); 
  motorP1.step(steps); 
  delay(1000); 
}

void testaMotorPasso(){
  int graus = 0;
  for (graus = 45; graus <= 360; graus = graus + 45){
    giraMotor(graus,60, HORARIO);
    delay(2000);
    giraMotor(graus,60, ANTI_HORARIO);
    delay(2000);
  }
}
 
void loop() 
{ 
  //testaMotorPasso();
}
