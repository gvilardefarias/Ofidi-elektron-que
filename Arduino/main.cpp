/*

  Aqui temos um exemplo de representação dos valores do grid
  
  | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 |
  | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2 | 0 | 0 | 1 |

  Consideramos o jogo da cobrinha nesse exemplo, nesse caso temos:
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


void escreveLCD(int gridNum){
  for(int i=0;i<2;i++)
    for(int j=0;j<16;j++){
      grid[gridNum][i][j]
    }
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

  escreveLED();
}

void lerTeclas(){
  // Nao limpa a telca de start
  // TODO
}

void carrinhosIndividual(){
  start = 0;
  e     = 0;
  d     = 0;
  
  
  while(1){
    lerTeclas();
    if(start) return;
    
    if(e){
      if(grid[0][0][15]){ // se o carrinho se encontra na primeira linha passa para a segunda
        grid[0][0][15] = 0;
        grid[0][1][15] = 1;
      }
      else{
        grid[0][0][15] = 1;
        grid[0][1][15] = 0;
      }
    }
    
    if(d){
      if(grid[1][0][15]){ // se o carrinho se encontra na primeira linha passa para a segunda
        grid[1][0][15] = 0;
        grid[1][1][15] = 1;
      }
      else{
        grid[1][0][15] = 1;
        grid[1][1][15] = 0;
      }
    }
    
    //TODO pontuacao
    
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


void setup() {
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
