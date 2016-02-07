
/*variável do tipo inteiro para controlar o brilho*/
int valorFade = 0;

void setup() {
  pinMode(9 ,OUTPUT);
}

void loop() {

  /*Aumentando o brilho*/
  for (valorFade = 0 ; valorFade <= 255; valorFade += 5) {
    analogWrite(9, valorFade);
    delay(30);
  }

  /*Diminuindo o brilho*/
  while (valorFade >= 0) {
     analogWrite(9, valorFade);
     delay(30);
     valorFade -= 5;
       
  }
}


