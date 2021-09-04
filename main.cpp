#include "snake.h"
#include "../raylib/src/raylib.h"

#include <iostream>
#include <cstdlib>

#define WIDTH 840
#define HEIGHT 660
#define NODE_WIDTH 20
#define NODE_HEIGHT 20
#define START_TEXT "Press 'SPACE' to Start"
#define SCORE_TEXT "Score: %d"
#define END_TEXT "Press 'SPACE' to Play Again"

enum DIRECTION { NONE = 0, UP = -1, DOWN = -2, LEFT = -3, RIGHT = -4 };

// Draws the sprites in the game of Snake
//
void DrawSprites(Snake& S, Snake::Node *apple) {
    for (Snake::Node *curr = S.head; curr != S.tail; curr = curr->next) {
        DrawRectangle(curr->position.x, curr->position.y, NODE_WIDTH, NODE_HEIGHT, LIME);
    }

    DrawRectangle(apple->position.x, apple->position.y, NODE_WIDTH, NODE_HEIGHT, RED);
}

// Checks if an apple spawns on top of the Snake
//
bool AppleInBadPosition(Snake& S, Snake::Node *apple) {
    for (Snake::Node *curr = S.head; curr != S.tail; curr = curr->next) {
        if (apple->position.x == curr->position.x && apple->position.y == curr->position.y) {
            return true;
        }
    }

    return false;
}

// pops up a Start Screen before the main game
//
void StartScreen() {
    bool start = true;
    while (start) {
        if (WindowShouldClose()) CloseWindow(), exit(EXIT_SUCCESS);

        if (IsKeyPressed(KEY_SPACE)) start = false;

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangle(0, HEIGHT - 60, WIDTH, 60, DARKGRAY);
        DrawText(TextFormat(SCORE_TEXT, 0), WIDTH - 120, HEIGHT - 40, 18, RAYWHITE);
        DrawText(TextFormat(START_TEXT), WIDTH - 540, HEIGHT - 40, 20, RAYWHITE);

        EndDrawing();
    }
}

// contents and game logic of Snake
//
int runGame() {
    Snake S = Snake(WIDTH - 520, HEIGHT - 240);
    Snake::Node *apple = new Snake::Node(WIDTH - 320, HEIGHT - 240);
    
    Snake::coordinate next = { 0, 0 };
    DIRECTION direction = NONE;
    
    bool running = true;
    while (running) {
        if (WindowShouldClose()) CloseWindow(), exit(EXIT_SUCCESS);

        switch(GetKeyPressed()) {
            case KEY_RIGHT:
                if (direction != LEFT || S.length == 1)
                    next = { 20, 0 }, direction = RIGHT;
                break;

            case KEY_LEFT:
                if (direction != RIGHT || S.length == 1)
                    next = { -20, 0 }, direction = LEFT;
                break;

            case KEY_UP:
                if (direction != DOWN || S.length == 1)
                    next = { 0, -20 }, direction = UP;
                break;

            case KEY_DOWN:
                if (direction != UP || S.length == 1)
                    next = { 0, 20 }, direction = DOWN;
                break;
        }

        S.move(next.x, next.y);

        if (S.snakeEatSelf() || S.outOfBounds(WIDTH, HEIGHT - 60)) {
            running = false;
        }

        if (S.snakeEatApple(apple)) {
            S.grow();
            while (AppleInBadPosition(S, apple)) {
                apple->position.x = rand() % (WIDTH / 20) * 20;
                apple->position.y = rand() % ((HEIGHT - 60) / 20) * 20;
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangle(0, HEIGHT - 60, WIDTH, 60, DARKGRAY);
        DrawText(TextFormat(SCORE_TEXT, S.length), WIDTH - 120, HEIGHT - 40, 18, RAYWHITE);
        DrawSprites(S, apple);

        EndDrawing();
    }

    return S.length;
}

// pops up an End Screen after the main game of Snake
//
void EndScreen(int score) {
    bool end = true;
    while (end) {
        if (WindowShouldClose()) CloseWindow(), exit(EXIT_SUCCESS);

        if (IsKeyPressed(KEY_SPACE)) end = false;

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangle(0, HEIGHT - 60, WIDTH, 60, DARKGRAY);
        DrawText(TextFormat(SCORE_TEXT, score), WIDTH - 120, HEIGHT - 40, 18, RAYWHITE);
        DrawText(TextFormat(END_TEXT), WIDTH - 560, HEIGHT - 40, 20, RAYWHITE);

        EndDrawing();
    }
}

// main game loop
//
int main() {
    InitWindow(WIDTH, HEIGHT, "Snake");
    SetTargetFPS(10);

    while (true) {
        StartScreen();
        int score = runGame();
        EndScreen(score);
    }
}
