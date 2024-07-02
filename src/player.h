#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

class Player {       
    public:
        float pos_x, pos_y;
        int speed;
        int width, height;
        Color color;

        Player(float x, float y, int s, int w, int h, Color c);
    
    void Draw();
    void Update(int screenHeight);
};

#endif