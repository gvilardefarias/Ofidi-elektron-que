/*

  Aqui temos um exemplo de representação dos valores do grid
  
  | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 |
  | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 1 |

  Consideramos o jogo do carrinho nesse exemplo, nesse caso temos:
    1 - Representa o carrinho
    2 - Perde uma vida se bater
    3 - Perde uma vida se não bater

*/


// 2 grids 16x2
// O primeiro indice representa qual grid está sendo usado
// grid 0 é o LCD da esquerda
int grid[2][2][16];

// As vidas para cada LCD
int vidas[2];

// Teclas
int start;
int e, d; // Esquerda, direita


void atualizaLCD(){
  for(int k=0;k<2;k++)
    for(int i=0;i<2;i++)
      for(int j=0;j<16;j++){
        // TODO hardware
        grid[k][i][j]
      }
}

void atualizaVidas(){
  if(vidas[0] == 3){
    digitalWrite(VIDA01, HIGH);
    digitalWrite(VIDA02, HIGH);
    digitalWrite(VIDA03, HIGH);
  }
  else if(vidas[0] == 2)
    digitalWrite(VIDA03, LOW);
  else if(vidas[0] == 1)
    digitalWrite(VIDA02, LOW);
  else if(vidas[0] == 0)
    digitalWrite(VIDA01, LOW);
  
  if(vidas[1] == 3){
    digitalWrite(VIDA11, HIGH);
    digitalWrite(VIDA12, HIGH);
    digitalWrite(VIDA13, HIGH);
  } 
  else if(vidas[1] == 2)
    digitalWrite(VIDA13, LOW);
  else if(vidas[1] == 1)
    digitalWrite(VIDA12, LOW);
  else if(vidas[1] == 0)
    digitalWrite(VIDA11, LOW);
  // TODO hardware
}

void lerTeclas(){
  e = !digitalRead(E);
  d = !digitalRead(D);
  start = !digitalRead(START);
  // Nao limpa a tecla de start
  // TODO hardware
}

void preencheGrid(int gridAux[2][16], int gridNum){
  for(int i=0;i<2;i++)
    for(int j=0;j<16;j++)
      grid[gridNum][i][j] = gridAux[i][j];
}

void desenhaMenu(){
  int gridAux[2][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
  };
  preencheGrid(gridAux);

  atualizaVidas();
}

void carrinhosIndividual(){
  start = 0;
  e     = 0;
  d     = 0;
  
  
  while(1){
    lerTeclas();
    if(start) return;
    
    delay(150);
    
    
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
    }
    
    
    for(int k=0;k<2;k++)
      for(int i=0;i<2;i++)
        for(int j=0;j<15;j++){
          grid[k][i][j+1] = grid[k][i][j];
        }
     
    grid[0][0][0] = random(4);
    grid[0][1][0] = random(4);
    grid[1][0][0] = random(4);
    grid[1][1][0] = random(4);
    
    if(grid[0][0][0]==1)  grid[0][0][0] = 0;
    if(grid[0][1][0]==1)  grid[0][1][0] = 0;
    if(grid[1][0][0]==1)  grid[1][0][0] = 0;
    if(grid[1][1][0]==1)  grid[1][1][0] = 0;
    
    
    atualizaLCD();
    atualizaVidas();
    
    if(vidas[1]<=0 && vidas[0]<=0)
      break;
  }
}

void carrinhosDupla(){
  start = 0;
  e     = 0;
  d     = 0;
  
  // TODO
  while(1){
    lerTeclas();
    if(start) return;
    
  }
}

// Portas utilizadas no arduino
#define VIDA01 11
#define VIDA02 10
#define VIDA03 9
#define VIDA11 8
#define VIDA12 7
#define VIDA13 6
#define START 4
#define E 5
#define D A5

void setup() {
  pinMode(VIDA01, OUTPUT);
  pinMode(VIDA01, OUTPUT);
  pinMode(VIDA02, OUTPUT);
  pinMode(VIDA03, OUTPUT);
  pinMode(VIDA11, OUTPUT);
  pinMode(VIDA12, OUTPUT);
  pinMode(VIDA13, OUTPUT);
  pinMode(START, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  
  randomSeed(analogRead(0));
  
  for(int k=0;k<2;k++)
    for(int i=0;i<2;i++)
      for(int j=0;j<16;j++)
        grid[k][i][j] = 0;

  vidas[0] = 3;
  vidas[1] = 3;
  
  desenhaMenu();
}

void loop() {
  lerTeclas();

  if(start)
    if(e)
      carrinhosIndividual();
    if(d)
      carrinhosDupla();
}
