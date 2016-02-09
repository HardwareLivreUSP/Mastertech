/*Codigo Example PIR */
void setup() {
   Serial.begin(9600);
   /*Configura os pinos para entrada ou saida*/
   pinMode(3,INPUT);
   pinMode(13,OUTPUT); 
   pinMode(6,OUTPUT);   
   /*Coloca uma codicao inicial para os valores de saida*/
   digitalWrite(13,LOW);
   digitalWrite(6,LOW);
}

void loop() {
   /*Dectetou presença*/
   if(digitalRead(3) == 1) {
      Serial.println("ALARME");
      digitalWrite(13,LOW);
      digitalWrite(6,HIGH); 
   }
   /*Não encontrou nada*/
   else {
      Serial.println("nada");
      digitalWrite(13,HIGH);
      digitalWrite(6,LOW); 
   }
}

/*Obs: Modifiquei no shield os valores
de sensibilidade e tempo para melhores
resultados*/
