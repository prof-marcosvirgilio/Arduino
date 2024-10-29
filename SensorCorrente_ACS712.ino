unsigned int x=0, acsValue=0,samples = 0, avgAcs=0;
float acsValueF=0.0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  samples = 0;
  for (int x = 0; x < 150; x++){ 
    //Leitura do valor do sensor
    acsValue = analogRead(A0);     
    //pegando 150 amostra para filtro 
    samples = samples + acsValue;  
    delay (3);
  }
  //PEGANDO UMA MEDIA
  avgAcs=samples/150.0; 
  //FORMULA DE AJUSTE DO VALOR LIDO
  acsValueF = (avgAcs * (5.0 / 1024.0)) * 6;
  Serial.println(acsValueF);
  delay(100);
}
