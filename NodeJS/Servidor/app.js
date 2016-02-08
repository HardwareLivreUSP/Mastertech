var net = require('net');
var inquirer = require("inquirer");
var ngrok = require('ngrok');
var clients = [];
var authtoken = '3VF2Ln9PfRjRYwcsGQ6Pe_4rZqDcKrB1Srzrs1CGkFr';

// -------------------------------   Servidor   -------------------------------
var PORT =  process.env.PORT || 8080;
var HOST = process.env.IP || '0.0.0.0';

var server = net.createServer(function(socket) {
  // Qunado um cliente entra no servidor, salvamos ele na lista (data em UNIX)
  socket.date =  (new Date).getTime();

  // Adiciona ele na lista
  clients.push(socket);

  // Quando um clientes desconectar, tiramos ele da lista
  socket.on('end', function () {
    clients.splice(clients.indexOf(socket), 1);
  });

  // Quando um cliente manda uma informação
  socket.on('data', function (data) {
    var valor = parseInt(data.toString());
    if (Number.isInteger(valor)) {
      // Essa parte é onde você adiciona a inteligência
      valor = Math.floor((1023 - valor)/4);
      socket.write("{" + valor + "}");
      socket.write("\n");
    }
  });
});

server.on('error', function(err){
  console.log(err);
});

ngrok.connect({proto: 'tcp', addr: PORT, authtoken:authtoken}, function (err, url) {
  server.listen(PORT, HOST, function() {
    address = server.address();
    console.log("\nServidor em %s\n", url);
    pergunta();
  });
});

// -------------------------------     Menu     -------------------------------
var pergunta = function () {
  inquirer.prompt([{
    type: "list",
    name: "opcao",
    message: "O que você quer saber?",
    choices: [
      {"name": "Lista de clientes conectados.", "value": 1},
      {"name": "Número de clientes conectados.", "value": 2},
    ]
  }], function( answers ) {
    switch(answers.opcao) {
    case 2:
        console.log("\nExistem %s clientes conectados.\n", clients.length);
        break;
    case 1:
        if (clients.length > 0) {
          var data_atual = (new Date).getTime();
          console.log("\nCliente \t\t\t Tempo Conexão");
          clients.forEach(function (client) {
            console.log("%s:%s \t\t %d s", client.remoteAddress, client.remotePort, (data_atual-client.date)/1000);
          });
          console.log("\n");
        } else {
          console.log("\nNão existem clientes conectados!\n");
        }
        break;
    default:
    }
    pergunta();
  });
}
