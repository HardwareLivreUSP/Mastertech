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

// Indica o passo atual dentro da sequência, é usado enquanto a sequência
// está sendo reproduzida.
int passo_atual_na_sequencia = 0;

/*
   Indica o pino de áudio, leds e botões.
   Os pinos de leds e botões estão em ordem, relacionados uns aos outros, ou
   seja, o primeiro led está relacionado ao primeiro botão. A ordem destas
   sequências também estão relacionadas a ordem dos tons.
*/
int pinoAudio = 2;

// Indica se um botão foi pressionado durante o loop principal.
int botao_pressionado = 0;

// Flag indicando se o jogo acabou.
int perdeu_o_jogo = false;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  // Definindo o modo do pino de Áudio como saída.
  pinMode(pinoAudio, OUTPUT);
  // Inicializando o random através de uma leitura da porta analógica.
  // Esta leitura gera um valor variável entre 0 e 1023.
  randomSeed(analogRead(5));
}

void loop() {
  // Se perdeu o jogo reinicializamos todas as variáveis.
  if (perdeu_o_jogo) {
    int sequencia[100] = {};
    rodada_atual = 0;
    passo_atual_na_sequencia = 0;
    perdeu_o_jogo = false;
  } else {
    lcd.print("Jogada: ");
    lcd.print(rodada_atual);
    delay(1000);
    lcd.clear();
  }

  // Toca um som de início para anúnicar que o jogo está começando quando é a primeira rodada.
  if (rodada_atual == 0) {
    tocarSomDeInicio();
    delay(500);
  }

  // Chama a função que inicializa a próxima rodada.
  proximaRodada();
  // Reproduz a sequência atual.
  reproduzirSequencia();
  // Aguarda os botões serem pressionados pelo jogador.
  lcd.print("Agora sua vez!");
  delay(1000);
  lcd.clear();
  aguardarJogador();
  // Aguarda 1 segundo entre cada jogada.
  delay(1000);
}


// Sorteia um novo item e adiciona na sequência.
void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}

// Reproduz a sequência para ser memorizada.
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

// Aguarda o jogador iniciar sua jogada.
void aguardarJogador() {

  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();
    verificarJogada();
    if (perdeu_o_jogo) {
      break;
    }
    passo_atual_na_sequencia++;
  }
  // Redefine a variável para 0.
  passo_atual_na_sequencia = 0;
}


void aguardarJogada() {

  boolean jogada_efetuada = false;

  while (!jogada_efetuada) {

    int i = -1;
    int botao = analogRead (0);  //Leitura do valor da porta analógica A0
    if (botao < 50) i = 0;
    else if (botao < 150) i = 2;
    else if (botao < 300) i = 3;
    else if (botao < 400) i = 1;
    if (i != -1) {
      // Dizendo qual foi o botao pressionado.
      botao_pressionado = i;
      tone(pinoAudio, tons[i]);
      lcd.print(texto[i]);
      delay(300);
      lcd.clear();
      lcd.setCursor(0, 0);
      noTone(pinoAudio);
      jogada_efetuada = true;
    }
    delay(100);
  }
}


void verificarJogada() {
  if (sequencia[passo_atual_na_sequencia] != botao_pressionado) {
    // GAME OVER.

    lcd.print("Voce Perdeu... :(");
    for (int i = 0; i <= 3; i++) {
      tone(pinoAudio, tons[i]);
      delay(200);
      noTone(pinoAudio);
    }
    tone(pinoAudio, tons[3]);
    delay(600);
    noTone(pinoAudio);
    lcd.clear();
    lcd.setCursor(0, 0);
    perdeu_o_jogo = true;
  }
}

void tocarSomDeInicio() {
  lcd.print("Vamos comecar!");
  tone(pinoAudio, tons[0]);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  delay(500);
  noTone(pinoAudio);
}
