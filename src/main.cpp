#include <raylib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <cmath>
#include "ball.h"
#include "player.h"
#include "bot.h"
#include "secondplayer.h"
using namespace std;

enum{
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};
enum{
    _BLACK = 0, _BLUE = 16, _GREEN = 32, _CYAN = 48, _RED = 64,
    _MAGENTA = 80, _BROWN = 96, _LIGHTGRAY = 112, _DARKGRAY = 128,
    _LIGHTBLUE = 144, _LIGHTGREEN = 160, _LIGHTCYAN = 176,
    _LIGHTRED = 192, _LIGHTMAGENTA = 208, _YELLOW = 224, _WHITE = 240
};

void limpartela(){ // AuxÃ­lio da IA para fazer.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Limpar a tela atual.
    CONSOLE_SCREEN_BUFFER_INFO csbi; // FunÃ§Ã£o que identifica o tamanho da tela e onde tÃ¡ o cursor.
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD coord = {0,0}; // Onde comeÃ§a a limpar.
    DWORD charsWritten;
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coord, &charsWritten); // Coloca espaÃ§os na tela.
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, coord, &charsWritten);
    SetConsoleCursorPosition(hConsole, coord); // PosiÃ§Ã£o do texto na coordenada 0,0.
}
void cor(int letra, int fundo){ // Muda a cor das letras e do fundo da tela. 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}
void posicao(int linha, int coluna){ // MovimentaÃ§Ã£o do cursor pelo teclado, usando as teclas para cima e para baixo.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){coluna - 1, linha - 1}); // PosiÃ§Ã£o do cursor na tela.
  // Deixando o cursor invisivel:
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void selecao(int linha1, int coluna1, int linha2, int coluna2){ // FunÃ§Ã£o que cria a caixa de seleÃ§ao do menu.
    int i, j, tamanholinha, tamanhocoluna;
    // Calculando o tamanho da caixa de menu:
    tamanholinha = linha2 - linha1;
    tamanhocoluna = coluna2 - coluna1;
    // Montagem da caixa de menu:
    for(i = coluna1; i <= coluna2; i++){ // Desenhando das linhas. *196 = valor retirado da tabela ASCII*.
        posicao(linha1, i);
        printf("%c", 196);
        posicao(linha2, i);
        printf("%c", 196);
    }
    
    for(i = linha1; i <= linha2; i++){ // Desenhando as colunas. *179 = Valor retirado da tabela ASCII*.
        posicao(i, coluna1);
        printf("%c", 179);
        posicao(i, coluna2);
        printf("%c", 179);
    }
    
    for(i = linha1 + 1; i < linha2; i++){ // Desenhando o fundo da tela.
        for(j = coluna1 + 1; j < coluna2; j++){
            posicao(i, j); // Coordenada do menu para percorrer toda a estrutura.
            printf(" ");
        }
    }
    
    // Desenho dos cantos do menu.
    posicao(linha1, coluna1);
    printf("%c", 218); // Superior esquerdo.
    posicao(linha1, coluna2);
    printf("%c", 191); // Superior direito.
    posicao(linha2, coluna1);
    printf("%c", 192); // Inferior esquerdo.
    posicao(linha2, coluna2);
    printf("%c", 217); // Inferior direito.
}

void DrawDashedLine(int startx, int starty, int endy, int dashLength, int spaceLength, Color color){
    for(int y = starty; y < endy; y += dashLength + spaceLength){
        DrawLine(startx, y, startx, y + dashLength, WHITE);
    }
}
int menu(int linha1, int coluna1, int quantidade, char lista[3][20]) {
    int opc = 1, linha, coluna2, linha2, i, tamMax, tecla;
    // CÃ¡lculo das coordenadas:
    tamMax = strlen(lista[0]);
    for(i = 1; i < quantidade; i++){ // Percorre toda a lista para achar o item do menu com maior tamanho.
        if(strlen(lista[i]) > tamMax){
            tamMax = strlen(lista[i]);
        }
    }
    // CÃ¡lculo para saber o tamanho da linha e da coluna do menu.
    linha2 = linha1 + (quantidade * 2 + 2); // Essas adiÃ§Ãµes servem para a palavra nÃ£o ficar muito imprenssada nas bordas.
    coluna2 = coluna1 + tamMax + 2;
    // Montagem da tela:
    cor(BLACK, _GREEN); // Cor da tela e das bordas.
    setlocale(LC_ALL, "C"); // Usamos o parÃ¢metro C da tabela ASCII para evitar a inserÃ§Ã£o de outros caracteres no menu. 
    selecao(linha1, coluna1, linha2, coluna2);
    setlocale(LC_ALL, "");
    
    // LaÃ§o das opÃ§Ãµes
    while (1){
        linha = linha1 + 2;
        for(i = 0; i < quantidade; i++){
            if(i + 1 == opc){
				cor(BLACK,_LIGHTMAGENTA); // Cor do texto selecionado.
			}else{ 
			cor(WHITE, _GREEN);// Cor do texto nÃ£o selecionado.
			}
            posicao(linha, coluna1 + 2); // PosiÃ§Ã£o do cursor. Ã‰ realizada a adiÃ§Ã£o para os itens nÃ£o ultrapassarem a borda do menu.
            printf("%s", lista[i]);
            linha = linha + 2; // Cada item em uma linha.
        }
        // LÃ³gica para guardar a tecla pressionada.
        posicao(1, 1);
        tecla = getch();
        posicao(22, 1);
        
        // OpÃ§Ã£o
        if(tecla == 27){ // ESC.
            opc = 0;
            break;
        }else if(tecla == 13){ // Enter.
            break;
        }else if(tecla == 72){ // Seta para cima.
            if(opc > 1){
				opc --; // Cursor vai para cima.
			}
        }else if(tecla == 80){ // Seta para baixo.
            if(opc < quantidade){
				opc++; // Cursor vai para baixo.
 	  	  }
        }
    }
    return opc; // Retorna um valor inteiro.
}


//------------------------------------------------------------------------------------
// Ponto de entrada da main do programa
//------------------------------------------------------------------------------------
int main(void){
    // InicializaÃ§Ã£o
    //--------------------------------------------------------------------------------------
  int opc;
    char lista[3][20] = {"JOGAR", "INSTRUÃ‡Ã•ES", "SAIR"}; // Itens que podem ser selecionados no menu.
    
    setlocale(LC_ALL, "");
    while(1){
    	posicao(10,14);
    	cor(LIGHTGREEN,_BLACK);
    	printf("ACE PONG!\n");
        opc = menu(12, 12, 3, lista);
        if(opc == 1){
			const int screenWidth = 854;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Ace Pong");

    SetTargetFPS(60);               // Definir o jogo para rodar a 60 fps
    //--------------------------------------------------------------------------------------

    // Criação dos objetos
    Ball ball(screenWidth/2, screenHeight/2, 5, 5, 5, WHITE);
    Player playerPaddle(screenWidth - 30, screenHeight/2 - 25, 10, 10, 50, WHITE);
    Secondplayer secondplayerPaddle(30, screenHeight/2 - 25, 10, 10, 50, WHITE);
    //Bot botPaddle(30, screenHeight/2 - 25, 10, 10, 50, WHITE);

    // Main game loop
    while (!WindowShouldClose())    // Detecta o botão de fechar janela ou a tecla ESC
    {
        // Events
        //----------------------------------------------------------------------------------
        if(CheckCollisionCircleRec(Vector2{ball.pos_x, ball.pos_y}, ball.radius, Rectangle{playerPaddle.pos_x, playerPaddle.pos_y, (float)playerPaddle.width, (float)playerPaddle.height})) {
            ball.speed_x *= -1;
            float playerCenterY = playerPaddle.pos_y + playerPaddle.height / 2;
            ball.speed_y = (ball.pos_y - playerCenterY) / (playerPaddle.height / 2) * -5;
            
            // Se a colisÃ£o for exatamente no meio da raquete, fazer a bola ir reta
            if (ball.pos_y == playerCenterY) {
                ball.speed_y = 1;
            }
            ball.pos_x = playerPaddle.pos_x - ball.radius - 1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.pos_x, ball.pos_y}, ball.radius, Rectangle{secondplayerPaddle.pos_x, secondplayerPaddle.pos_y, (float)secondplayerPaddle.width, (float)secondplayerPaddle.height})) {
            ball.speed_x *= -1;
            float secondplayerCenterY = secondplayerPaddle.pos_y + secondplayerPaddle.height / 2;
            ball.speed_y = (ball.pos_y - secondplayerCenterY) / (secondplayerPaddle.height / 2) * -5;
            
            // Se a colisÃ£o for exatamente no meio da raquete, fazer a bola ir reta
            if (ball.pos_y == secondplayerCenterY) {
                ball.speed_y = 1;
            }
            ball.pos_x = secondplayerPaddle.pos_x + ball.radius + 1;
        }

        /*if (CheckCollisionCircleRec(Vector2{ball.pos_x, ball.pos_y}, ball.radius, Rectangle{botPaddle.pos_x, botPaddle.pos_y, (float)botPaddle.width, (float)botPaddle.height})) {
            ball.speed_x *= -1;
            float botCenterY = botPaddle.pos_y + botPaddle.height / 2;
            ball.speed_y = (ball.pos_y - botCenterY) / (botPaddle.height / 2) * -5;
            
            // Se a colisÃ£o for aproximadamente no meio da raquete, fazer a bola ir reta
            if (fabs(ball.pos_y - botCenterY) < 1.0f) {
                ball.speed_y = 0;
            }
            
            // Ajusta a posiÃ§Ã£o da bola para fora da raquete para evitar mÃºltiplas detecÃ§Ãµes
            ball.pos_x = botPaddle.pos_x + botPaddle.width / 2 + ball.radius + 1;
        }
        */
       
        cout << playerPaddle.pos_y << endl;
        //----------------------------------------------------------------------------------

        // Update
        //----------------------------------------------------------------------------------
        ball.Update(screenWidth, screenHeight);
        playerPaddle.Update(screenHeight);
        //botPaddle.Update(ball.pos_y);
        secondplayerPaddle.Update(screenHeight);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
            DrawDashedLine(screenWidth / 2, -4, screenHeight, 14, 11, WHITE);
            //botPaddle.Draw();
            playerPaddle.Draw();
            ball.Draw();
            secondplayerPaddle.Draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Fecha a janela e o OPEN GL
    //--------------------------------------------------------------------------------------
		}
        if(opc == 2){ // Mostrar as instruções.
			cor(WHITE,_BLACK);
			limpartela();
			printf("1 - Use as setas para cima e para baixo do teclado\n");
			printf("2 - NÃ£o deixe que a bola ultrapasse a sua raquete\n");
			printf("3 - Complete 11 pontos primeiro do que o adversÃ¡rio\n");
			printf("4 - BOM JOGO!\n");
			printf("\n");
			printf("Pressione qualquer tecla para voltar ao MENU INICIAL\n");
			getch();
			limpartela();
		}
        if(opc == 3){ // Opção de sair do jogo, encerra o programa.
            break;
        }
    }
    cor(WHITE, _BLACK);
    posicao(24, 1);
    printf("");
  
  return 0;
}