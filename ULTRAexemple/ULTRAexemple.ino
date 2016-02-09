const int outPin = 2; 
const int inPin = 3;

void setup() {

  Serial.begin(115200);
  pinMode(outPin, OUTPUT_FAST);
  pinMode(inPin, INPUT_FAST);
}

void loop()
{

  long duration, inches, cm;

  /*Ativa o trig com um pulso em alto*/
  fastDigitalWrite(outPin, LOW);
  waitMicros(2);
  fastDigitalWrite(outPin, HIGH);
  waitMicros(10);
  fastDigitalWrite(outPin, LOW);

  /*espera por um sinal alto e guarda o tempo que demorou*/
  duration = pulseIn(inPin, HIGH); // calls fastGpioPciDigitalRead

  /*converte o tempo para centimetros*/
  cm = microsecondsToCentimeters(duration);
  

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

void waitMicros(int val)
{
  unsigned long a = micros();
  unsigned long b = micros();
  while((b-a) < val)
  {
    b = micros();
    if(a>b)
    {
      break;
    }
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
