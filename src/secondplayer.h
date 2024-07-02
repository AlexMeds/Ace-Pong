
#ifndef SECONDPLAYER_H
#define SECONDPLAYER_H
#include <raylib.h>

class Secondplayer {       
    public:
        float pos_x, pos_y;
        int speed;
        int width, height;
        Color color;

        Secondplayer(float x, float y, int s, int w, int h, Color c);
    
    void Draw();
    void Update(int screenHeight);
};

#endif
