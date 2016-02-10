### Utilizando node.js
Nesse exemplo vocês vão montar o seu próprio servidor para poder responder as solicitações do seu dispositivo. O primeiro passo para isso é entrar na pasta servidor e executar o seguinte comando:
```
npm install
```
Esse comando irá instalar todas os pacotes necessários para o nosso exemplo. Depois de instalados, ligar o servidor.
```
node app.js
```
##### Dicas
Se você não quiser ter o trabalho de usar o node.js na sua máquina, pode usar tranquilamente o Cloud9.

Além disso, seria adequado usar fazer o cadastro no [ngrok](https://dashboard.ngrok.com/get-started) e gerar o seu token. No exemplo estamos usando um tokem público que pode apresentar alguns problemas.

#### Desafio
Reduzir o número de pacotes enviados. Dica, não mande valores repetidos. Um jeito de aprimorar essa aplicação é fazer com que os pacotes não trafeguem até pelo mundo, mas somente na rede local.
