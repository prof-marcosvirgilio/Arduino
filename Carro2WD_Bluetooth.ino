#include <SoftwareSerial.h>
#include <AFMotor.h>
// remove the inverted commas after you copy the code to the IDE
// creates a "virtual" serial port/UART
// connect BT module TX to D51
// connect BT module RX to D50
// connect BT Vcc to 5V, GND to GND

SoftwareSerial mySerial(51, 50);
//Uno  SoftwareSerial mySerial (2, 3);
//mega SoftwareSerial mySerial(51, 50);  
char comando = ""; // Stores response of bluetooth device  
            // which simply allows \n between each  
            // response.  
//motores
AF_DCMotor et(3);
AF_DCMotor ef(2);
AF_DCMotor df(1);
AF_DCMotor dt(4);
int velocidade = 254;            
   
void setup()   
{  
  // Open serial communications and wait for port to open:  
  Serial.begin(9600);  
  Serial.println("Digite comandos para o celular");  
  // SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.  
  mySerial.begin(9600); 
  //motores
  parar();
  
   
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
  df.run(BACKWARD);
  et.setSpeed(velocidade);
  et.run(BACKWARD);
  dt.setSpeed(velocidade);
  dt.run(BACKWARD);
}


void traz(){
  ef.setSpeed(velocidade);
  ef.run(FORWARD);
  df.setSpeed(velocidade);
  df.run(FORWARD);
  et.setSpeed(velocidade);
  et.run(FORWARD);
  dt.setSpeed(velocidade);
  dt.run(FORWARD);
}

void direita(){
  ef.setSpeed(velocidade);
  ef.run(FORWARD);
  df.setSpeed(velocidade);
  df.run(BACKWARD);
  et.setSpeed(velocidade);
  et.run(FORWARD);
  dt.setSpeed(velocidade);
  dt.run(BACKWARD);
}

void esquerda(){
  ef.setSpeed(velocidade);
  ef.run(BACKWARD);
  df.setSpeed(velocidade);
  df.run(FORWARD);
  et.setSpeed(velocidade);
  et.run(BACKWARD);
  dt.setSpeed(velocidade);
  dt.run(FORWARD);
}



void loop()  
{  
  // Read device output if available.
  while (mySerial.available()) {  
    comando = (char)mySerial.read();
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
        direita();
        Serial.println("direita...");
      break;
      case 'e':
        esquerda();
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
    mySerial.write(Serial.read());  
  }  
   
}// END loop()  