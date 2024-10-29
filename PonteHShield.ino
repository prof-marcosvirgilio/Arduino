
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
#include <AFMotor.h>

# define velocidade 180

//Inicializa os dispositivos
Ultrasonic sonicT(44, 46);
Ultrasonic sonicF(30, 28);
AF_DCMotor motorFD(4); //Seleciona o motor 1
AF_DCMotor motorFE(3); //Seleciona o motor 2
AF_DCMotor motorTD(1); //Seleciona o motor 3
AF_DCMotor motorTE(2); //Seleciona o motor 4

enum Direcoes { FRENTE, TRAS, DIREITA, ESQUERDA, PARADO};
enum Direcoes movimento = FRENTE;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    motorFD.setSpeed(velocidade);
    //motorFD.run(FORWARD); 
    motorTD.setSpeed(velocidade);
    //motorTD.run(FORWARD);   
    motorFE.setSpeed(velocidade);
    //motorFE.run(FORWARD);  
    motorTE.setSpeed(velocidade);
    //motorTE.run(FORWARD);

}
