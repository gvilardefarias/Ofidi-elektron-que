#include <LiquidCrystal.h>

// Portas utilizadas no arduino
#define VIDA01 11
#define VIDA02 10
#define VIDA03 9
#define VIDA11 8
#define VIDA12 7
#define VIDA13 6

#define E 5
#define D 4

#define EN 13
#define RS_0 12
#define RS_1 A0

#define D4_0 0
#define D5_0 1
#define D6_0 2
#define D7_0 3

#define D4_1 A1
#define D5_1 A2
#define D6_1 A3
#define D7_1 A4

LiquidCrystal LCD0(RS_0, EN, D4_0, D5_0, D6_0, D7_0); 
LiquidCrystal LCD1(RS_1, EN, D4_1, D5_1, D6_1, D7_1); 

// 2 grids 16x2
// O primeiro indice representa qual grid está sendo usado
// grid 0 é o LCD da esquerda
int grid[2][2][16];

//Definicao dos caracteres utilizados no LCD
byte customChar0[8] = {
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111
};  // espaco vazio

byte customChar1[8] = {
	0b11111,
	0b00000,
	0b10100,
	0b11111,
	0b11111,
	0b10100,
	0b00000,
	0b11111
};  // Carrinho

byte customChar2[8] = {
	0b11111,
	0b00000,
	0b01110,
	0b00100,
	0b00100,
	0b01110,
	0b00000,
	0b11111
};  // Barreira

byte customChar3[8] = {
	0b11111,
	0b00000,
	0b11111,
	0b10001,
	0b10001,
	0b11111,
	0b00000,
	0b11111
};  // Circulo

// As vidas para cada LCD
int vidas[2];

// Teclas
bool start, ativa, limparValores;
bool e, d; // Esquerda, direita

// Controle
unsigned long tempo;


void atualizaLCD(){
    for(int i=0;i<2;i++){
      for(int j=0;j<16;j++){
        LCD1.setCursor(j,i);    
        LCD1.write((byte) grid[1][i][15-j]);
        
        LCD0.setCursor(j,i);
        LCD0.write((byte) grid[0][i][15-j]);
      }
    }
}

// Mensagem para quando ganhar no modo de individual
void perderIndividual(){
	  LCD0.clear();
	  LCD1.clear();
	
    LCD0.setCursor(6,0);
		LCD0.print("Fim");
		LCD0.setCursor(2,1);
		LCD0.print("Do Jogo");
	
	  delay(5000);
}

// Mensagem para quando ganhar no modo de dupla
void ganhadorDupla(){
	LCD0.clear();
	LCD1.clear();
	
  if(vidas[0] && vidas[1]<=0){
     LCD0.setCursor(5,0);
		 LCD0.print("Voce");
		 LCD0.setCursor(4,1);
		 LCD0.print("Ganhou");
		
		 LCD1.setCursor(5,0);
		 LCD1.print("Voce");
		 LCD1.setCursor(4,1);
		 LCD1.print("Perdeu");
	} else if(vidas[1] && vidas[0]<=0){
		 LCD0.setCursor(5,0);
		 LCD0.print("Voce");
		 LCD0.setCursor(4,1);
		 LCD0.print("Perdeu");
		
     LCD1.setCursor(5,0);
		 LCD1.print("Voce");
		 LCD1.setCursor(4,1);
		 LCD1.print("Ganhou");
	} else{
		 LCD0.setCursor(4,0);
		 LCD0.print("Empate");
		
		 LCD1.setCursor(4,0);
		 LCD1.print("Empate");
	}
	
	delay(5000);
}

void desenhaMenu(){
	  LCD0.clear();
	  LCD0.setCursor(5,0);
		LCD0.print("Modo");
		LCD0.setCursor(2,1);
		LCD0.print("Individual    ");
	
	  LCD1.clear();
    LCD1.setCursor(5,0);
		LCD1.print("Modo");
		LCD1.setCursor(4,1);
		LCD1.print("Dupla");
}

void atualizaVidas(){
  if(vidas[0] == 3){
    digitalWrite(VIDA01, HIGH);
    digitalWrite(VIDA02, HIGH);
    digitalWrite(VIDA03, HIGH);
  }
  else if(vidas[0] == 2){
    digitalWrite(VIDA01, HIGH);
    digitalWrite(VIDA02, HIGH);
    digitalWrite(VIDA03, LOW);
  }
  else if(vidas[0] == 1){
    digitalWrite(VIDA01, HIGH);
    digitalWrite(VIDA02, LOW);
    digitalWrite(VIDA03, LOW);
  }
  else if(vidas[0] == 0){
    digitalWrite(VIDA01, LOW);
    digitalWrite(VIDA02, LOW);
    digitalWrite(VIDA03, LOW);
  }
  
  if(vidas[1] == 3){
    digitalWrite(VIDA11, HIGH);
    digitalWrite(VIDA12, HIGH);
    digitalWrite(VIDA13, HIGH);
  } 
  else if(vidas[1] == 2){
    digitalWrite(VIDA11, HIGH);
    digitalWrite(VIDA12, HIGH);
    digitalWrite(VIDA13, LOW);
  }
  else if(vidas[1] == 1){
    digitalWrite(VIDA11, HIGH);
    digitalWrite(VIDA12, LOW);
    digitalWrite(VIDA13, LOW);
  }
  else if(vidas[1] == 0){
    digitalWrite(VIDA11, LOW);
    digitalWrite(VIDA12, LOW);
    digitalWrite(VIDA13, LOW);
  }
}

void lerTeclas(){
  e = !digitalRead(E);
  d = !digitalRead(D);
}

void preencheGrid(int gridAux[2][16], int gridNum){
  for(int i=0;i<2;i++)
    for(int j=0;j<16;j++)
      grid[gridNum][i][j] = gridAux[i][j];
}

void limpaMenu(){
  int gridAux[2][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
  };
  preencheGrid(gridAux, 0);
  preencheGrid(gridAux, 1);
	
  vidas[0] = 3;
  vidas[1] = 3;

  atualizaLCD();
  atualizaVidas();
}

void carrinhos(int dupla){
  start = 0;
  e     = 0;
  d     = 0;
  
  
  while(1){
    lerTeclas();
    //Serial.println(start);
    if(start) return;    
    
    
    if(e && vidas[0]>0){
      if(grid[0][0][15]){ // se o carrinho se encontra na primeira linha passa para a segunda
        grid[0][0][15] = 0;
        grid[0][1][15] = 1;
      }
      else{
        grid[0][0][15] = 1;
        grid[0][1][15] = 0;
      }
    }
    
    if(d && vidas[1]>0){
      if(grid[1][0][15]){ // se o carrinho se encontra na primeira linha passa para a segunda
        grid[1][0][15] = 0;
        grid[1][1][15] = 1;
      }
      else{
        grid[1][0][15] = 1;
        grid[1][1][15] = 0;
      }
    }
    
    
    if((millis()-tempo)>1000){
      tempo = millis();
      
      // LCD da esquerda
      if(vidas[0]>0){
        if(grid[0][0][15]){
          if(grid[0][0][14]==2) vidas[0]  -= 1;
          if(grid[0][1][14]==3) vidas[0]  -= 1;
        }
        else{
          if(grid[0][0][14]==3) vidas[0]  -= 1;
          if(grid[0][1][14]==2) vidas[0]  -= 1;
        }
	      
	      
	// Deslocamento para esquerda e adicao de novos obstaculos
	for(int i=0;i<2;i++)
          for(int j=14;j>0;j--)
            grid[0][i][j] = grid[0][i][j-1];
	      
	grid[0][0][0] = random(0, 4);
      	grid[0][1][0] = random(0, 4);
	      
        // Nao se pode adicionar um novo carrinho
	if(grid[0][0][0]==1)  grid[0][0][0] = 0;
      	if(grid[0][1][0]==1)  grid[0][1][0] = 0;
	      
	// Nem ter dois obstaculos do mesmo tipo na mesma linha
      	if(grid[0][0][0]==2 && grid[0][1][0]==2) grid[0][random(0, 1)][0] = 3;
      	if(grid[0][0][0]==3 && grid[0][1][0]==3) grid[0][random(0, 1)][0] = 2;
      }

      // LCD da direita
      if(vidas[1]>0){
        if(grid[1][0][15]){
          if(grid[1][0][14]==2) vidas[1]  -= 1;
          if(grid[1][1][14]==3) vidas[1]  -= 1;
        }
        else{
          if(grid[1][0][14]==3) vidas[1]  -= 1;
          if(grid[1][1][14]==2) vidas[1]  -= 1;
        }
	  	
	 
	for(int i=0;i<2;i++)
          for(int j=14;j>0;j--)
            grid[1][i][j] = grid[1][i][j-1];
	      
	grid[1][0][0] = random(0, 4);
      	grid[1][1][0] = random(0, 4);  
      
      	if(grid[1][0][0]==1)  grid[1][0][0] = 0;
      	if(grid[1][1][0]==1)  grid[1][1][0] = 0;  

      	if(grid[1][0][0]==2 && grid[1][1][0]==2) grid[1][random(0, 1)][0] = 3;
      	if(grid[1][0][0]==3 && grid[1][1][0]==3) grid[1][random(0, 1)][0] = 2;
      }
      
      atualizaVidas();      
    }
    
    atualizaLCD();
    
    if(!dupla){
      if(vidas[1]<=0 && vidas[0]<=0)
        break;
    } else{
      if(vidas[1]<=0 || vidas[0]<=0)
        break;
    }
  }
}


void setup() {
  //Serial.begin(9600);
  
  pinMode(VIDA01, OUTPUT);
  pinMode(VIDA02, OUTPUT);
  pinMode(VIDA03, OUTPUT);
  pinMode(VIDA11, OUTPUT);
  pinMode(VIDA12, OUTPUT);
  pinMode(VIDA13, OUTPUT);
  
  pinMode(E, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  
  LCD0.begin(16, 2);
  LCD1.begin(16, 2);
	
  LCD0.createChar(0, customChar0);
  LCD0.createChar(1, customChar1);
  LCD0.createChar(2, customChar2);
  LCD0.createChar(3, customChar3);
	
  LCD1.createChar(0, customChar0);
  LCD1.createChar(1, customChar1);
  LCD1.createChar(2, customChar2);
  LCD1.createChar(3, customChar3);
  
  randomSeed(analogRead(5));
  
  vidas[0] = 3;
  vidas[1] = 3;
  
  limparValores = 1;
}

void loop() {
  if(limparValores){
    limparValores = 0;
    
    desenhaMenu();
  }
  lerTeclas();
	
  //Ajeita o treco do menu
    if(e){
      limpaMenu();
      carrinhos(0);
      
      limparValores = 1;
      perderIndividual();
    }
    if(d){
      limpaMenu();
      carrinhos(1);
      
      limparValores = 1;
      ganhadorDupla();
    }
}
