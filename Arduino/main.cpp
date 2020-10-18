/*

  Aqui temos um exemplo de representação dos valores do grid
  
  | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 
  | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 
  | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
  | 0 | 0 | 2 | 0 | 0 | 0 | 0 | 0 | 
  | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
  | 0 | 0 | 2 | 1 | 0 | 0 | 0 | 0 | 
  | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 
  | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 

  Consideramos o jogo da cobrinha nesse exemplo, nesse caso temos:
    1 - Representa o corpo
    2 - Representa a cabeça e as comidinhas que a cobrinha pega para crescer

  No grid todos os valores >0 são acesos os LEDs

*/

int grid[8][8];


void escreveLED(){
  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      if(grid[i][j])
        // liga led
      else
        // desliga led
}

void preencheGrid(int gridAux[8][8]){
  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      grid[i][j] = gridAux[i][j];
}

void desenhaMenu(){
  int gridAux[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}    
  };
  preencheGrid(gridAux);

  escreveLED();
}

void lerTeclas(){
  // TODO
}

void cobrinha(){
  // TODO
}


void setup() {
  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
      grid[i][j] = 0;

  desenhaMenu();
}

void loop() {
  lerTeclas();

  if(start)
    cobrinha();
}
