/*#include "bot.h"
#include "ball.h"
#include <cstdlib> // Para std::rand() e std::srand()
#include <ctime>   // Para std::time()

Bot::Bot(float x, float y,  int s, int w, int h, Color c){
    pos_x = x;
    pos_y = y;
    speed = s;
    width = w;
    height = h;
    color = c;
}

void Bot::Draw(){
    DrawRectangle(pos_x, pos_y, width, height, color);
    // x position screenWidth - largura + padding | y position screenHeigth/2 - altura/2 | largura | altura | cor
}

void Bot::Update(int ball_y){
    std::srand(std::time(0));
    // Fator de variação aleatória
    int random_factor = std::rand() % 10 - 5; // Gera um número entre -5 e 4

    // Adiciona o fator aleatório à posição da bola
    ball_y += random_factor;

    // Adiciona um atraso na reação do bot
    static int reaction_delay = 0;
    if (reaction_delay <= 0) {
        reaction_delay = std::rand() % 5; // Gera um atraso aleatório entre 0 e 4 frames

        if (pos_y + height / 2 > ball_y) {
            pos_y = pos_y - speed;
        }
        if (pos_y + height / 2 <= ball_y) {
            pos_y = pos_y + speed;
        }
    } else {
        reaction_delay--;
    }

    LimitMovement();
};
*/