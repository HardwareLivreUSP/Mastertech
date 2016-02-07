/*
  Hardware Livre USP - Mastertech
  Enviando mensagens e recebendo mensagens pelo PubNub
*/
#include <SPI.h>
#include <Ethernet.h>
#include <PubNub.h>
#define LED_PIN 9
#define ANALOG_PIN A0

// Some Ethernet shields have a MAC address printed on a sticker on the shield;
// fill in that address here, or choose your own at random:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char pubkey[] = "demo";
char subkey[] = "demo";
char channel_send[] = "tutorial1";
char channel_receive[] = "tutorial2";

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

	PubNub.begin(pubkey, subkey);
}

void loop() {
	send_analog_value ();
  check_for_updates ();
}

void send_analog_value () {
  EthernetClient *client;

  char msg[4] = "";
  sprintf(msg, "%d", analogRead(ANALOG_PIN));

  client = PubNub.publish(channel_send, msg);
  if (!client) {
    Serial.println("Erros ao publicar");
  } else {
    Serial.println("Dado enviado com sucesso. ");
  }
  client->stop();
}

void check_for_updates () {
  EthernetClient *client;
  client = PubNub.history(channel_receive, 1);
  if (client) {
		while (client->connected() && !client->available()); // Espera caractar
    int c;
    client->read();
    client->read();
    c = client->read() - 48;
    if (c == 1 || c == 0) {
      digitalWrite(LED_PIN, c);
      Serial.println(c);
    }
  }
  client->stop();
}
