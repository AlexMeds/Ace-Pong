#include "ball.h"

Ball::Ball(float x, float y, int sx, int sy, int r, Color c){
    pos_x = x;
    pos_y = y;
    speed_x = sx;
    speed_y = sy;
    radius = r;
    color = c;
}

void Ball::Draw() {
    DrawCircle(pos_x, pos_y, radius, color);
}

void Ball::Update(int screenWidth, int screenHeight){
    pos_x += speed_x;
    pos_y += speed_y;

    if(pos_y <= radius){
        speed_y *= -1;
        pos_y = radius;
    }
    if(pos_y >= screenHeight - radius){
        speed_y *= -1;
        pos_y = screenHeight - radius;
    }

    if(pos_x >= screenWidth - radius){
        Reset(screenWidth, screenHeight);
        ResetSpeed("right");
    }
    if(pos_x <= radius){
        Reset(screenWidth, screenHeight);
        ResetSpeed("left");
    }
}

void Ball::ResetSpeed(string side){
    if (side == "left"){
        speed_y = -5;
        }
    if (side == "right"){
        speed_y = 5;
    }
}

void Ball::Reset(int screenWidth, int screenHeight){
    pos_x = screenWidth/2;
    pos_y = screenHeight/2;
    
}
