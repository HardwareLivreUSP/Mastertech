void setup() {
  
  pinMode(9, OUTPUT); /*saída*/
  pinMode(2, INPUT); /*entrada*/

  digitalWrite(9, LOW);
}

void loop() {

   if (digitalRead(2) == 1) {
      digitalWrite(9, HIGH);
   }
   else {
      digitalWrite(9, LOW);
   }
}
