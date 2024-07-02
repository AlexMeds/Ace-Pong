/*#ifndef BOT_H
#define BOT_H
#include <raylib.h>
#include "ball.h"

class Bot {
    protected:
    void LimitMovement(){
        if (pos_y <= 0){
            pos_y = 0;
        }if (pos_y + height >= GetScreenHeight()){
            pos_y = GetScreenHeight () - height;
        }
        
    } 
    public:
        float pos_x, pos_y;
        int speed;  
        int width, height;
        Color color;

        Bot(float x, float y, int s, int w, int h, Color c);
    
    void Draw();
    void Update(int ball_pos_y);
};

#endif
*/