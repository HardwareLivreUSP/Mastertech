/*
 Esse código le mensagens enviadas no twiter.
*/
#include <SPI.h>
#include <Ethernet.h>


// Veja o dereço MAC da sua placa na etiqueta branca
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };

// Se sua placa não conseguir usar um IP dinâmico ela vai usar
// esse IP abaixo. Pode deixar desse modo até que seja orientado
// diferente.
IPAddress ip(0,0,0,0);

// Iniciando as bibliotecas
EthernetClient client;

// Intervamo em microsegundos entre requisições
const unsigned long requestInterval = 500;

char serverName[] = "api.twitter.com";  // twitter URL

boolean requested;                   // whether you've made a request since connecting
unsigned long lastAttemptTime = 0;   // last time you connected to the server, in milliseconds

String currentLine = "";            // string to hold the text from server
String tweet = "";                  // string to hold the tweet
boolean readingTweet = false;       // if you're currently reading the tweet

void setup() {
  // reserve space for the strings:
  currentLine.reserve(256);
  tweet.reserve(150);

 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // attempt a DHCP connection:
  Serial.println("Obtendo IP dinâmico");
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Serial.println("Tentando usar IP estático");
    Ethernet.begin(mac, ip);
  }
  Serial.print("IP obtido:");
  Serial.println(Ethernet.localIP());
  // connect to Twitter:
  connectToServer();
}



void loop()
{
  if (client.connected()) {
    if (client.available()) {
      // read incoming bytes:
      char inChar = client.read();

      // add incoming byte to end of line:
      currentLine += inChar;

      // if you get a newline, clear the line:
      if (inChar == '\n') {
        currentLine = "";
      }
      // if the current line ends with <text>, it will
      // be followed by the tweet:
      if ( currentLine.endsWith("<text>")) {
        // tweet is beginning. Clear the tweet string:
        readingTweet = true;
        tweet = "";
      }
      // if you're currently reading the bytes of a tweet,
      // add them to the tweet String:
      if (readingTweet) {
        if (inChar != '<') {
          tweet += inChar;
        }
        else {
          // if you got a "<" character,
          // you've reached the end of the tweet:
          readingTweet = false;
          Serial.println(tweet);
          // close the connection to the server:
          client.stop();
        }
      }
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
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}
