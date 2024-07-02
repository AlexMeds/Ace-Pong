#ifndef BALL_H // Verifica se BALL_H não está definida
#define BALL_H // Define BALL_H
#include <raylib.h>
#include <iostream>
#include <string>
using namespace std;


class Ball {
    public:
        float pos_x, pos_y;
        int speed_x, speed_y;
        int radius;
        Color color;

        Ball(float x, float y, int sx, int xy, int r, Color c);

        void Draw();
        void Update(int screenWidth, int screenHeight);
        void Reset(int screenWidth, int screenHeight);
        void ResetSpeed(string side);
};

#endif // BALL_H
