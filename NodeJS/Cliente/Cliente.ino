/*
  Hardware Livre USP - Mastertech
  Enviando mensagens por um servidor
*/
#include <SPI.h>
#include <Ethernet.h>

#define ANALOG_PIN A0
#define LED_PIN 6
// Utilize o endereço MAC que está na etiqueta branca da
// sua Galielo
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IP do servidor e porta do servidor.
//IPAddress server(192,168,1,32);
char server[] = "0.tcp.ngrok.io";
int port = 4000;

EthernetClient client;
String line = "";

// Marcadores da string line
int lendo_valor = false;

// Variaveis para delay de envio de informacoes
const long interval = 1000;
unsigned long previousMillis = 0;

void setup() {
  pinMode(LED_PIN , OUTPUT);
  Serial.begin(9600);
  system("ifup eth0");
  Serial.println("Tentando obter um IP:");
  while (!Ethernet.begin(mac)) {
    Serial.println("Erro ao conectar");
  }
  Serial.print("Meu endereco:");
  Serial.println(Ethernet.localIP());

  // Reserva espaço para a string
  line.reserve(10);
}

void loop() {
  // Realiza a conexao e leitura do servidor
  if (client.connected()) {
    if (client.available()) {
      char c = client.read();
      line += c;
      if (c == '\n')
        line = "";

      if (line.endsWith("{")) {
        lendo_valor = true;
        line = "";
      }
      if (lendo_valor) {
        if (c == '}') {
          int valor = line.toInt();
          lendo_valor = false;
          Serial.print("Recebendo: ");
          Serial.println(valor);
          analogWrite(LED_PIN, valor);
        }
      }
    }
  } else {
    Serial.println("Conectando ao servidor");
    delay(1000);
    client.connect(server, port);
  }

  // Realiza o envio de informacoes
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (client.connected()) {
      int value = analogRead(ANALOG_PIN);
      client.println(value);
      Serial.print("Enviando: ");
      Serial.println(value);
    }
  }
}
