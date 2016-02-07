#define  led 9

void setup() {

   pinMode(led, OUTPUT);
   digitalWrite(led,LOW);

}


void loop() {

  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(1000);

}
