#include "raylib.h"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <conio.h>
#include <sstream>
#include "ball.h"
#include "bot.h"
#include "player.h"
#include "secondplayer.h"

using namespace std;

void DrawDashedLine(int startx, int starty, int endy, int dashLength, int spaceLength, Color color) {
    for(int y = starty; y < endy; y += dashLength + spaceLength) {
        DrawLine(startx, y, startx, y + dashLength, WHITE);
    }
}

void DrawPoints(int screenWidth, Player player1, Secondplayer player2) {
    DrawText(TextFormat("Player 1 Points: %i", player1.GetPoints()), screenWidth - 200, 10, 20, WHITE);
    DrawText(TextFormat("Player 2 Points: %i", player2.GetPoints()), 10, 10, 20, WHITE);
}

void DrawTime(int time, int screenWidth) {
    DrawText(TextFormat("%i", time), screenWidth / 2 - 20, 20, 40, WHITE);
}

void jogo() {
    const int screenWidth = 854;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "Ace Pong");
    SetTargetFPS(60);  // Definir o jogo para rodar a 60 fps

    // Criação dos objetos
    Ball ball(screenWidth / 2, screenHeight / 2, 5, 5, 5, WHITE);
    Player playerPaddle(screenWidth - 30, screenHeight / 2 - 25, 10, 10, 50, WHITE, 0);
    Secondplayer secondplayerPaddle(30, screenHeight / 2 - 25, 10, 10, 50, WHITE, 0);

    int startTime = GetTime();
    bool gameStarted = true;
    bool gameOver = false;
    char winner[20];

    // Main game loop
    while (!WindowShouldClose()) {
        // Events
        int time = 0;
        if (gameStarted) {
            time = GetTime() - startTime;
        }

        if (CheckCollisionCircleRec(Vector2{ball.pos_x, ball.pos_y}, ball.radius, Rectangle{playerPaddle.pos_x, playerPaddle.pos_y, (float)playerPaddle.width, (float)playerPaddle.height})) {
            ball.speed_x *= -1;
            float playerCenterY = playerPaddle.pos_y + playerPaddle.height / 2;
            ball.speed_y = (ball.pos_y - playerCenterY) / (playerPaddle.height / 2) * 5;
            
            // Se a colisão for exatamente no meio da raquete, fazer a bola ir reta
            if (ball.pos_y == playerCenterY) {
                ball.speed_y = 0;
            }
            ball.pos_x = playerPaddle.pos_x - ball.radius - 1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.pos_x, ball.pos_y}, ball.radius, Rectangle{secondplayerPaddle.pos_x, secondplayerPaddle.pos_y, (float)secondplayerPaddle.width, (float)secondplayerPaddle.height})) {
            ball.speed_x *= -1;
            float secondplayerCenterY = secondplayerPaddle.pos_y + secondplayerPaddle.height / 2;
            ball.speed_y = (ball.pos_y - secondplayerCenterY) / (secondplayerPaddle.height / 2) * 5;
            if (ball.pos_y == secondplayerCenterY) {
                ball.speed_y = 0;
            }
            ball.pos_x = secondplayerPaddle.pos_x + secondplayerPaddle.width + ball.radius + 1;
        }

        // Verificação de pontos
        char point = ball.Point(screenWidth, screenHeight);
        if (point == 'l') {
            secondplayerPaddle.IncreasePoints();  // Aumenta os pontos do jogador esquerdo
        } else if (point == 'r') {
            playerPaddle.IncreasePoints();  // Aumenta os pontos do jogador direito
        }

        // Verifica se algum jogador atingiu 11 pontos
        if (playerPaddle.GetPoints() == 11 || secondplayerPaddle.GetPoints() == 11) {
            gameOver = true;
            gameStarted = false;
            if (playerPaddle.GetPoints() == 11) {
                snprintf(winner, sizeof(winner), "Player 1 Ganhou!");
            } else {
                snprintf(winner, sizeof(winner), "Player 2 Ganhou!");
            }
        }
        if (gameOver) {
            // Draw Game Over screen
            BeginDrawing();
                ClearBackground(DARKGRAY);
                DrawText(winner, screenWidth / 2 - MeasureText(winner, 40) / 2, screenHeight / 2 - 20, 40, WHITE);
                DrawText("Pressione ESPAÇO para sair", screenWidth / 2 - MeasureText("Pressione ESPAÇO para sair", 20) / 2, screenHeight / 2 + 40, 20, WHITE);
            EndDrawing();

            if(IsKeyPressed(KEY_SPACE)){
                break;  // Sai do loop principal e termina o jogo
            }
        }else{
            // Update
            ball.Update(screenWidth, screenHeight);
            playerPaddle.Update(screenHeight);
            secondplayerPaddle.Update(screenHeight);

            // Draw
            BeginDrawing();
                ClearBackground(DARKGRAY);
                DrawDashedLine(screenWidth / 2, -4, screenHeight, 14, 11, WHITE);
                DrawTime(time, screenWidth);
                DrawPoints(screenWidth, playerPaddle, secondplayerPaddle);
                playerPaddle.Draw();
                ball.Draw();
                secondplayerPaddle.Draw();
            EndDrawing();
        }
    }
    CloseWindow();  // Fecha a janela e o OPEN GL
}

void instrucoes() {
    const int screenWidth = 854;
    const int screenHeight = 480;
    while (!WindowShouldClose() && !IsKeyPressed(KEY_SPACE)) {
        BeginDrawing();
            ClearBackground(GREEN);
            DrawText("INSTRUÇÕES:", screenWidth / 2 - MeasureText("INSTRUÇÕES:", 30) / 2, 50, 30, WHITE);
            DrawText("1 - NÃO DEIXE O OPONENTE PONTUAR", 50, 100, 20, WHITE);
            DrawText("2 - CONTROLE UTILIZANDO AS SETAS DE CIMA E BAIXO OU O W/S", 50, 130, 20, WHITE);
            DrawText("3 - COMPLETE 11 PONTOS PRIMEIRO DO QUE O ADVERSÁRIO", 50, 160, 20, WHITE);
            DrawText("4 - DIVIRTA-SE!", 50, 190, 20, WHITE);
            DrawText("Pressione a tecla ESPAÇO para retornar ao MENU", 50, 250, 20, WHITE);
        EndDrawing();
    }
}

int main(void) {
    const int screenWidth = 854;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "ACE PONG MENU");
    Rectangle playButton = { screenWidth / 2 - 100, 150, 200, 50 };
    Rectangle instructionsButton = { screenWidth / 2 - 100, 220, 200, 50 };
    Rectangle exitButton = { screenWidth / 2 - 100, 290, 200, 50 };
    Rectangle player1Button = { screenWidth / 2 - 100, 290, 200, 50 };
    Rectangle botButton = { screenWidth / 2 - 100, 290, 200, 50 };
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();

            if (CheckCollisionPointRec(mousePoint, playButton)) {
                jogo();
            }
            if (CheckCollisionPointRec(mousePoint, instructionsButton)) {
                instrucoes();
            }
            if (CheckCollisionPointRec(mousePoint, exitButton)) {
                break;
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(WHITE);

            DrawText("ACE PONG!", screenWidth / 2 - MeasureText("ACE PONG!", 30) / 1.25, 50, 50, GREEN);

            DrawRectangleRec(playButton, GREEN);
            DrawRectangleRec(instructionsButton, GREEN);
            DrawRectangleRec(exitButton, GREEN);
            
            DrawText("JOGAR", playButton.x + 60, playButton.y + 15, 20, WHITE);
            DrawText("INSTRUÇÕES", instructionsButton.x + 30, instructionsButton.y + 15, 20, WHITE);
            DrawText("SAIR", exitButton.x + 75, exitButton.y + 15, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}