/*Código exemplo TILT*/
void setup() {
  /*Inicia comunicação serial pinos 0 e 1 com velocidade 9600 bits/segundo*/
  Serial.begin(9600);
  /*Define pinos d eentrada e saída*/
  pinMode(2,INPUT);
  pinMode(13, OUTPUT);
  /*Coloca um valor inicial para saída*/
  digitalWrite(13, LOW);
  /*Ativa o resistor PULL*/
  digitalWrite(2, HIGH);
}

void loop() {
  /*Se o sensor estiver em "pé"*/
  if (digitalRead(2) == 0) { 
    Serial.println("de pe");
    digitalWrite(13,HIGH);
  }
  else {
    Serial.println("ponta cabeca");
    digitalWrite(13,LOW);
  }
  delay(150);  
}
