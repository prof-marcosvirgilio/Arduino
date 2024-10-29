#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ModbusIP.h>
#include <Modbus.h>

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
ModbusIP mb;

//registrador emulado
const int DIST_CM = 0;
const int DIST_IN = 0;
//variaveis do sensor de distancia
float cmMsec = 0, inMsec = 0;
long microsec = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
   /*
   * Bloco 1 ModBus
   * configuração dos parâmetros de comunicação do protocolo 
   * (deve-se ficar atento apenas à escolha de um endereço de ip compatível com a rede local que está sendo utilizada) 
   * e à inicialização da comunicação propriamente dita.
   */
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
    byte ip[] = { 192, 168, 0, 66 };   
    mb.config(mac, ip);
    //Bloco 2 - criação das instancias utilizados do tipo Input register.
    mb.addIreg(DIST_CM);
    mb.addIreg(DIST_IN);
    
}

void loop() {
      //função task(), utilizada para gerenciar a comunicação e a troca de dados entre os dispositivos que estão conectados através do protocolo Modbus.
      mb.task();
      //Le as informacoes do sensor, em cm e pol
      microsec = ultrasonic.timing();
      cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
      inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
      //definindo valores para os registradores  
      mb.Ireg(DIST_CM, cmMsec);
      mb.Ireg(DIST_IN, inMsec);
       //Exibe informacoes no serial monitor
      Serial.print("Distancia em cm: ");
      Serial.print(cmMsec);
      Serial.print(" - Distancia em polegadas: ");
      Serial.println(inMsec);
      delay(2000);

}
