/*
 Esse código le mensagens enviadas no twiter.
*/
#include "Base64.h"

#include <SPI.h>
#include <Ethernet.h>

// Veja o dereço MAC da sua placa na etiqueta branca
byte mac[] = { 0x98, 0x4F, 0xEE, 0x00, 0xC5, 0x46 };

// Se sua placa não conseguir usar um IP dinâmico ela vai usar
// esse IP abaixo. Pode deixar desse modo até que seja orientado
// diferente.
IPAddress ip(0,0,0,0);

// Iniciando as bibliotecas
EthernetClient client;

// Intervamo em microsegundos entre requisições

const unsigned long requestInterval = 500;

char serverName[] = "api.twitter.com";  // twitter URL

void setup() {
  Serial.begin(9600);
  
  // attempt a DHCP connection:
  Serial.println("Obtendo IP dinamico");
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Serial.println("Tentando usar IP estatico");
    Ethernet.begin(mac, ip);
  }
  system("ifup eth0");
  
  Serial.print("IP obtido: ");
  Serial.println(Ethernet.localIP());
}



void loop() {
  
  if (client.connected()) {
    if (client.available()) {
      // read incoming bytes:
      char inChar = client.read();
      Serial.print(inChar);
    }
  }
  else if (millis() - lastAttemptTime > requestInterval) {
    // if you're not connected, and two minutes have passed since
    // your last connection, then attempt to connect again:
    connectToServer();
  }
}

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(serverName, 80)) {
    Serial.println("making HTTP request...");
    // make HTTP GET request to twitter:
    client.println("GET /1/statuses/user_timeline.xml?screen_name=arduino&count=1 HTTP/1.1");
    client.println("HOST: api.twitter.com");
    client.println("HOST: api.twitter.com");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

