/*
  Hardware Livre USP - Mastertech
  Solicitando página web
*/
#include <SPI.h>
#include <Ethernet.h>

// Utilize o endereço MAC que está na etiqueta branca da
// sua Galielo
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char server[] = "capella.pro";

EthernetClient client;

void setup() {
  Serial.begin(9600);
  system("ifup eth0");
  Serial.println("Tentando obter um IP:");
  while (!Ethernet.begin(mac)) {
    Serial.println("Erro ao conectar");
  }
  Serial.print("Meu endereco:");
  Serial.println(Ethernet.localIP());

  // Para dar tempo de abrir o terminal
  delay(3000);

  // Tenta conectar
  if (client.connect(server, 80)) {
    Serial.println("Conectado ao servidor\n\n");
    client.println("GET /mastertech/hi.html HTTP/1.0");
    client.println("Host: capella.pro");

    client.println();
  }
  else {
    // Problema na conexão
    Serial.println("connection failed");
  }
}

void loop()
{
  // Mostrar toda a resposta
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // Se o servidor desconectar
  if (!client.connected()) {
    Serial.println();
      Serial.println();
    Serial.println("Desconectando.");
    client.stop();

    // Não fazer nada jamais
    for(;;)
      ;
  }
}
