//
// Created by Charles on 04/12/2023.
//

#ifndef PROJECT_CASSE_BRIQUE_STRUCT_H
#define PROJECT_CASSE_BRIQUE_STRUCT_H

#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 700
#define NUM_BRICKS 10

typedef struct {
    SDL_Rect rect;
    int lives;
    int destroyed;
} Brick;

typedef struct {
    int paddleSpeed;
    int ballSpeed;
} GameSettings;

void initializeBricks(Brick bricks[]);
void initializeSettings(GameSettings *settings);

#endif //PROJECT_CASSE_BRIQUE_STRUCT_H
