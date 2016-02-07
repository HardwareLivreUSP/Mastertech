/*------------DESAFIO GENIUS------------
|LEMBRE-SE VOCÊ VAI PRECISAR DE 
|4 PINOS PARA LEDS 4 PARA TECLAS E
|UM PARA O BUZZER PARA O SOM DAS TECLAS
-----------------------------------------
|Dicas: Faça uma função para observar a
|jogada e verificar se ela está correta.
|Caso sim continue caso não resseta os valores
|dos vetores, e começa de novo
-----------------------------------------*/

/*Vetor para gardar cada jogada*/
int sequencia[100] = {};

int rodada_atual = 0;

/*Vetor para gardar os pinos digitais para os LEDs
caso queira colocar algum led em outro pino,basta
trocar*/
int pinosLeds[4] = { 8, 9, 10, 11 };

/*Vetor para guardar os pinos que irão ler
entrada dos botões*/
int pinosBotoes[4] = { 2, 3, 4, 5 };

/*PROTÓTIPOS DE FUNCOES*/
void proximaRodada();
/*---------------------*/

void setup() {
   
  // Definindo o modo dos pinos dos Leds como saída.
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }   

  // Definindo o modo dos pinos dos Botões como entrada.
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosBotoes[i], INPUT);
  }
  
  /*Truque para "gerar" numero aleatŕoios*/
  randomSeed(analogRead(0));

}

/*Loop Principal*/
void loop() {
  
}
/*-------------*/


/*Corpo das funcoes*/
/*Sorteia um novo item e adiciona na sequência.*/
void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}
/*-----------------*/
