/*
  Hardware Livre USP - Mastertech
  Enviando mensagens pelo Twitter
*/
#include <SPI.h>
#include <Ethernet.h>
#define ENTRADA_ANALOGICA A0
// Utilize o endereço MAC que está na etiqueta branca da
// sua Galielo
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


char server[] = "0.tcp.ngrok.io";

void setup() {
  Serial.begin(9600);
  system("ifup eth0");
  Serial.println("Tentando obter um IP:");
  while (!Ethernet.begin(mac)) {
    Serial.println("Erro ao conectar");
  }
  Serial.print("Meu endereco:");
  Serial.println(Ethernet.localIP());

  // Tenta conectar
  if (client.connect(server, 80)) {
    Serial.println("Conectado ao servidor\n\n");
    client.println("GET /hi.html HTTP/1.0");
    client.println();
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}
