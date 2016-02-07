void setup() {
  
  pinMode(9, OUTPUT);
  
}

void loop() {
  
   tone(9, 440);
   delay(1000);
   noTone(9);
   delay(1000);

}
