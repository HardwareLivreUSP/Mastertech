## Exemplo PubNub
Vamos usar uma plataforma muito interessante chamado PubNub. Resumidamente, essa é uma plataforma para conectar diversos tipos de dispositivos.

Para começar, faça o cadastro na plataforma [aqui](https://admin.pubnub.com/#/register).

Nesse repositório você terá um arquivo .html, abra ele em seu navegador. Você terá a capacidade de mudar o estado de um pino e de ler uma porta analógica.

Como nesse exemplo precisamos enviar e receber informação e o nosso microcontrolador é limitado, devemos ablitar a opção Storage & Playback no site do PubNub.

#### Desafio
Escolha um outro grupo da sala. Na biblioteca do PubNub, veja a função subscribe. Agora um grupo será o interruptor e o outro será o atuador, ou seja, em uma Galileo você deve apertar um botão e quando isso acontecer na outra deve ascender um led. É legal ter uma interface web para visualizar o status atual (se a LED está acesso ou apagado).
