/*-----------Desafio GENIUS---------
  Neste desafio vocês terão que criar o jogo da memória de
vocês, configurações iniciais já forão feitas porém vocês 
terão que continuar.
  Tentem pensar no passo a passo do jogo e o que terá de ser
feito em cada etapa. Usem funções, loops(for, whiles), 
vetores outras variáveis e etc. VocÊs podem tambêm olhar
a reposta final para comparar ou ver um caminho para solução
Lembre-se qualquer coisa basta perguntar
*--------------------------------------------------------*/
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
/*
  NORMAL: 799
  SELECT: 546
  RIGHT: 1
  DOWN: 242
  UP: 100
  LEFT: 370
*/

//Vamos começar definindo as notas para os sons
#define NOTE_D4  294
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_A5  880

// criando o array para os 4 sons para sortear um som
int tons[4] = { NOTE_A5, NOTE_A4, NOTE_G4, NOTE_D4 };

// Texto que vai aparecer na tela
String texto[4] = { "right", "left", "up", "down" };

// Nossa sequência de até 100 itens vai começar vazia.
int sequencia[100] = {};

// Indica a rodada atual que o jogo se encontra.
int rodada_atual = 0;

//Pino do buzzer - alto falante
int pinoAudio = 2;




void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  // Definindo o modo do pino de Áudio como saída.
  pinMode(pinoAudio, OUTPUT);
  // Inicializando o random através de uma leitura da porta analógica.
  // Esta leitura gera um valor variável entre 0 e 1023.
  randomSeed(analogRead(5));
}
/*LOOP PRINCIPAL*/
void loop() {
   proximaRodada();
   delay(1000);
   reproduzirSequencia(); 
}
/*--------------*/

/*---FUNÇÕES---*/
// Sorteia um novo item e adiciona na sequência.
void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}

// Reproduz a sequência para ser memorizada pelo jogador.
void reproduzirSequencia() {
  for (int i = 0; i < rodada_atual; i++) {
    tone(pinoAudio, tons[sequencia[i]]);
    lcd.print(texto[sequencia[i]]);
    delay(500);
    noTone(pinoAudio);
    lcd.clear();
    lcd.setCursor(0, 0);
    delay(100);
  }
  noTone(pinoAudio);
}
