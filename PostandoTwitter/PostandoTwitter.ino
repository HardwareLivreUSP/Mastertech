/*
  Hardware Livre USP - Mastertech
  Enviando mensagens pelo Twitter
*/
#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h>
#define ENTRADA_ANALOGICA A0
// Utilize o endereço MAC que está na etiqueta branca da
// sua Galielo
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Isse IP será usudo caso não consiga obter um IP
// dinâmico
IPAddress ip(0,0,0,0);

Twitter twitter("<<< coloque seu token >>>");
String msg = "Oi gente, sou um robô e estou lendo ";

void setup() {
  Serial.begin(9600);

  Serial.println("Tentando obter um IP:");
  if (!Ethernet.begin(mac)) {
    Serial.println("tentado manualmente");
    Ethernet.begin(mac, ip);
  }
  Serial.print("Meu endereço:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  Serial.println("Conectando ...");

  msg += analogRead(ENTRADA_ANALOGICA);
  int buffer_len = msg.length()+1;
  char buffer[buffer_len];
  msg.toCharArray(buffer, buffer_len);

  if (twitter.post(buffer)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("Erro ao enviar: ");
      Serial.println(status);
    }
  } else {
    Serial.println("Erro.");
  }
  // Mandar em intervalos maior do esse, nunca menor
  delay(60000);
}
