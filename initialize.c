//
// Created by Charles on 15/01/2024.
//

#include "struct.h"

void initializeBricks(Brick bricks[]) {
    int brickWidth = 100;
    int brickHeight = 30;
    int padding = 20;
    int initialX = (SCREEN_WIDTH - (brickWidth + padding) * NUM_BRICKS) / 2;
    int initialY = 50;
    bricks->destroyed = 0;

    for (int i = 0; i < NUM_BRICKS; ++i) {
        bricks[i].rect.x = initialX + i * (brickWidth + padding);
        bricks[i].rect.y = initialY;
        bricks[i].rect.w = brickWidth;
        bricks[i].rect.h = brickHeight;
        bricks[i].lives = rand() % 3 + 1;
    }
}

void initializeSettings(GameSettings *settings) {
    settings->paddleSpeed = 10;
    settings->ballSpeed = 5;
}