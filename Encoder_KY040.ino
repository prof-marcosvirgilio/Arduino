 const int pinoCLK = 3; //PINO DIGITAL (CLK)
 const int pinoDT = 4;  //PINO DIGITAL (DT)
 const int pinoSW = 5; //PINO DIGITAL (SW)
 
 int contadorPos = 0;  //CONTADOR DE POSIÇÕES DO ENCODER
 int contadorVoltas = 0;  //CONTADOR DE POSIÇÕES DO ENCODER
 int ultPosicao; //REGISTRA A ÚLTIMA POSIÇÃO DO ENCODER
 int leituraCLK; //VARIÁVEL PARA ARMAZENAR LEITURA DO PINO CLK
 boolean bCW; //VARIÁVEL DE CONTROLE DO SENTIDO (HORÁRIO / ANTI-HORÁRIO)

 void setup() {
   Serial.begin (9600); //INICIALIZA A SERIAL
   pinMode (pinoCLK,INPUT); //DEFINE O PINO COMO ENTRADA
   pinMode (pinoDT,INPUT); //DEFINE O PINO COMO ENTRADA
   pinMode (pinoSW,INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
   ultPosicao = digitalRead(pinoCLK); //VARIÁVEL RECEBE A LEITURA DO PINO CLK  
 } 

 void loop() { 
  //VARIÁVEL RECEBE A LEITURA DO PINO CLK
  leituraCLK = digitalRead(pinoCLK);  
  //VERIFICA SE VARIÁVEL FOR DIFERENTE DO VALOR DE "ultPosicao"
  if (leituraCLK != ultPosicao){ 
    if (digitalRead(pinoDT) != leituraCLK) { 
      /*SE LEITURA DO PINO FOR DIFERENTE DA LEITURA DE "leituraCLK",
      SIGNIFICA QUE O EIXO ESTÁ SENDO GIRADO NO SENTIDO HORÁRIO */
      //INCREMENTA CONTAGEM DA VARIÁVEL EM +1
      contadorPos++; 
      bCW = true; //VARIÁVEL BOOLEANA RECEBE VERDADEIRO (SENTIDO HORÁRIO)
    } else { 
      //SENÃO, SIGNIFICA QUE O EIXO ESTÁ SENDO GIRADO NO SENTIDO ANTI-HORÁRIO E FAZ
      bCW = false; //VARIÁVEL BOOLEANA RECEBE FALSO (SENTIDO ANTI-HORÁRIO)
      contadorPos--; //DECREMENTA CONTAGEM DA VARIÁVEL EM -1
    }
    Serial.print(" / Posição do encoder: "); //IMPRIME O TEXTO NA SERIAL
    Serial.println(contadorPos); //IMPRIME NO MONITOR SERIAL A POSIÇÃO ATUAL DO ENCODER
   }
   //Atualiza ultima posição do encoder
   ultPosicao = leituraCLK; 
   //VERIFICA SE JA COMPELTOU UMA VOLTA COMPLETA NO EIXO
   if (contadorPos >= 40){
      //VOLTA COMPLETA
      contadorVoltas++;
      //Zera contador de posição para contar outra volta
      contadorPos = 0;
      //IMPRIME CONTADOR DE VOLTAS DO ENCODER
      Serial.print(" / Voltas do eixo do encoder: ");
      Serial.println(contadorVoltas); 
   }
   
 }