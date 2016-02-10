### Desafio
Programe sua Galileo para acessar esse site:

```
http://developers.agenciaideias.com.br/tempo/json/sao-paulo-SP
```

Agora acenda um LED se a temperatura está acima de 22°C. Mais informações sobre essa API, [aqui](http://developers.agenciaideias.com.br/tempo).

#### Dica

Veja também a seguite documentação do Arduino sobre Strings:

```
https://www.arduino.cc/en/Reference/StringObject
```

#### Requisição POST
Segue abaixo um pedaço de código, que realiza uma conexão POST - me parece que o slack aceita esse tipo de requisição para realizar postagens (não tenho certeza).

```cpp
byte postPage(char* domainBuffer, int thisPort, char* page, char* thisData) {
  int inChar;
  char outBuf[64];

  Serial.print(F("connecting..."));

  if (client.connect(domainBuffer, thisPort) == 1)
  {
    Serial.println(F("connected"));

    // send the header
    sprintf(outBuf, "POST %s HTTP/1.1", page);
    client.println(outBuf);
    sprintf(outBuf, "Host: %s", domainBuffer);
    client.println(outBuf);
    client.println(F("Connection: close\r\nContent-Type: application/x-www-form-urlencoded"));
    sprintf(outBuf, "Content-Length: %u\r\n", strlen(thisData));
    client.println(outBuf);

    // send the body (variables)
    client.print(thisData);
  }
  else
  {
    Serial.println(F("failed"));
    return 0;
  }

  int connectLoop = 0;

  while (client.connected())
  {
    while (client.available())
    {
      inChar = client.read();
      Serial.write(inChar);
      connectLoop = 0;
    }

    delay(1);
    connectLoop++;
    if (connectLoop > 10000)
    {
      Serial.println();
      Serial.println(F("Timeout"));
      client.stop();
    }
  }

  Serial.println();
  Serial.println(F("disconnecting."));
  client.stop();
  return 1;
}
```
