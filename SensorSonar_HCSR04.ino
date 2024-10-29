//Autor: Marcos Virgilio
 
//Carrega bibliotecas
#include <Ultrasonic.h>
#include <AFMotor.h>
#include <Servo.h>

//constantes
//distancia em cm entre o sensor sonar e os obstaculos detectados
#define limiteDistancia 30 
// tempo em milisegundos entre as rotacoes do servo motor
#define delayRotacao 750 
// tempo em milisegundos de acionamento dos motores das rodas
#define delayFrente 400 
#define delayDireita 550
#define delayEsquerda 550
#define delayTras 300
// forca do motor para rotacao das rodas
#define velocidadeRotacao 180
#define velocidadeMovimento 180
// angulos para deslocamento dos servo motores
#define anguloFrente 95
#define anguloDireita 50
#define anguloEsquerda 140

//enumerador
enum Direcoes { FRENTE, TRAS, DIREITA, ESQUERDA, PARADO};
//FRENTE = 0, TRAS = 1, DIREITA = 2, ESQUERDA = 3, PARADO = 4
  
//Inicializa os dispositivos
Ultrasonic sonicF(39, 41);
//Ultrasonic sonicT(40, 38);
AF_DCMotor motorE(4);
AF_DCMotor motorD(3);
Servo motorF;
//Servo motorT;

void setup()
{
  motorF.attach(10);
  //motorT.attach(9);
  Serial.begin(9600);
  Serial.println("Robo ligado...");  
}

//procedimento para parar o robo
void parar(){
  motorD.run(RELEASE);
  motorE.run(RELEASE);
  logarSerialMonitor("Motores parados");
}

//procedimento para log 
void logarSerialMonitor(String info){
  //Exibe informacoes no serial monitor
  Serial.print(info + "\n");
}

//procedimento para movimentar o robo
void movimentar(enum Direcoes direcao,int velocidade, int tempo){
  //velocidade maxima = 255
  switch (direcao) {
  case 0: //FRENTE
    motorD.setSpeed(velocidade);
    motorD.run(FORWARD); 
    motorE.setSpeed(velocidade);
    motorE.run(FORWARD); 
    delay(tempo);
    parar();
  break;
  case 1: //TRAS
    motorD.setSpeed(velocidade);
    motorD.run(BACKWARD);  
    motorE.setSpeed(velocidade);
    motorE.run(BACKWARD);
    delay(tempo);
    parar();   
  break;
  case 3: //ESQUERDA
    motorD.setSpeed(velocidade);
    motorD.run(FORWARD);
    motorE.setSpeed(velocidade);
    motorE.run(BACKWARD);
    delay(tempo);
    parar();  
  break;
  case 2: //DIREITA
    motorD.setSpeed(velocidade);
    motorD.run(BACKWARD);    
    motorE.setSpeed(velocidade);
    motorE.run(FORWARD);
    delay(tempo);
    parar();  
  break;
  }
}

//procedimento para ler as informacoes dos sensores sonares
float verificarObstaculos(enum Direcoes direcao){
  int distanciaMicrosegundos = 0;
  float distanciaCentimetros = 0;
  float menorDistanciaMedida = 0;
  switch(direcao) {
  case 0: 
    // FRENTE
    motorF.write(anguloFrente);
    delay (delayRotacao);
    distanciaMicrosegundos = sonicF.timing();
    distanciaCentimetros = sonicF.convert(distanciaMicrosegundos, Ultrasonic::CM);
    logarSerialMonitor("Distancia lida frente = "  + (String)distanciaCentimetros); 
    menorDistanciaMedida = distanciaCentimetros;
    //FRENTE DIREITA
    motorF.write(anguloDireita);
    delay (delayRotacao);
    distanciaMicrosegundos = sonicF.timing();
    distanciaCentimetros = sonicF.convert(distanciaMicrosegundos, Ultrasonic::CM);
    logarSerialMonitor("Distancia lida frente direita = "  + (String)distanciaCentimetros);
    if (distanciaCentimetros > 0 && distanciaCentimetros < menorDistanciaMedida){
      menorDistanciaMedida = distanciaCentimetros; 
    }
    //FRENTE ESQUERDA
    motorF.write(anguloEsquerda);
    delay (delayRotacao);
    distanciaMicrosegundos = sonicF.timing();
    distanciaCentimetros = sonicF.convert(distanciaMicrosegundos, Ultrasonic::CM);
    logarSerialMonitor("Distancia lida frente esquerda = "  + (String)distanciaCentimetros);
    if (distanciaCentimetros > 0 && distanciaCentimetros < menorDistanciaMedida){
      menorDistanciaMedida = distanciaCentimetros; 
    }
  break;
  case 1: //TRAS   
    
  break;  
  case 2: //DIREITA   
    
  break;
  case 3: //ESQUERDA   
    
  break;  
  }
  motorF.write(anguloFrente);
  return menorDistanciaMedida;  
}

void executar(){
     if (verificarObstaculos(FRENTE) > limiteDistancia){
        movimentar(FRENTE,velocidadeMovimento,delayFrente);
     } else {
        //ROTACIONA DIREITA 45 GRAUS
        movimentar(TRAS,velocidadeMovimento,delayTras);
        movimentar(DIREITA,velocidadeMovimento,delayDireita);
     }
}
 
void loop()
{
  
  //logarSerialMonitor("retorno funcao = " + (String)verificarObstaculos(FRENTE));
  //delay(1000);
  executar();
}
