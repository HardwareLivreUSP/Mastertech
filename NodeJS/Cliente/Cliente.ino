/*
  Hardware Livre USP - Mastertech
  Enviando mensagens pelo Twitter
*/
#include <SPI.h>
#include <Ethernet.h>

#define ENTRADA_ANALOGICA A0
#define LED_PIN 9
// Utilize o endereço MAC que está na etiqueta branca da
// sua Galielo
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IP do servidor e porta do servidor.
IPAddress server(192,168,1,32);
int port = 4000;

EthernetClient client;

// Unidade para armazenamento do que entra
char buffer[10] = "";

// Variaveis para delay de envio de informacoes
const long interval = 1000;
unsigned long previousMillis = 0;

void setup() {
	pinMode(LED_PIN , OUTPUT);
  Serial.begin(9600);
  //system("ifup eth0");
  Serial.println("Tentando obter um IP:");
  while (!Ethernet.begin(mac)) {
    Serial.println("Erro ao conectar");
  }
  Serial.print("Meu endereco:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Realiza a conexao e leitura do servidor
  if (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (c = '\n') {
        int leitura = atoi(buffer);
        Serial.print("Recebido do servidor: ");
        Serial.println(leitura);
        analogWrite(leitura);
        buffer = "";
      } else {
        buffer[sizeof(buffer)] = c;
      }
    }
  } else {
    Serial.print("Conectando ao servidor");
    client.connect(server, port);
  }

  // Realiza o envio de informacoes
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if(client.connected()) {
      int value = analogRead(ANALOG_PIN);
      client.println(value);
      Serial.print("Enviando para o servidor o valor: ");
      Serial.println(value);
    }
  }

}
