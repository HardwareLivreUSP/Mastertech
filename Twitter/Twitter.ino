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

Twitter twitter("<<< coloque seu token >>>");
String msg = "#mastertech_iot Oi gente, sou um robô e estou lendo ";

void setup() {
  Serial.begin(9600);
  system("ifup eth0");
  Serial.println("Tentando obter um IP:");
  while (!Ethernet.begin(mac)) {
    Serial.println("Erro ao conectar");
  }
  Serial.print("Meu endereco:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  Serial.println("Conectando ...");

  msg += analogRead(ENTRADA_ANALOGICA);
  int buffer_len = msg.length() + 1;
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
  // Mandar em intervalos maior do esse, nunca menor!
  delay(60000);
}
