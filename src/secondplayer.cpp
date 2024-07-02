#include "secondplayer.h"

Secondplayer::Secondplayer(float x, float y,  int s, int w, int h, Color c){
    pos_x = x;
    pos_y = y;
    speed = s;
    width = w;
    height = h;
    color = c;
}

void Secondplayer::Draw(){
    DrawRectangle(pos_x, pos_y, width, height, color);
    // x position screenWidth - largura + padding | y position screenHeigth/2 - altura/2 | largura | altura | cor
}

void Secondplayer::Update(int screenHeight){
    if (IsKeyDown(KEY_W) && pos_y > 0){
        pos_y -= speed;
    }

    if (IsKeyDown(KEY_S) && pos_y < screenHeight - height){
        pos_y += speed;
    }
}
