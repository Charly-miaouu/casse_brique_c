#include "struct.h"

bool gameWon = false;
bool gameOver = false;
int lives = 3;

void displayTitle(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect dest = {((SCREEN_WIDTH / 2) - 250), 50, 500, 100};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void displayQuit(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect dest = {50, 600, 100, 30};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void displayPlay(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect dest = {50, 380, 150, 45};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void displaySettings(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect dest = {50, 500, 150, 30};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void displayLogo(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void displaySettingsScreen(SDL_Renderer *renderer, GameSettings *settings) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect backButton = {50, 600, 100, 30};
    SDL_Rect paddleSpeed = {60, (SCREEN_HEIGHT / 2) + 5, 310, 30};
    SDL_Rect ballSpeed = {810, (SCREEN_HEIGHT / 2) + 5, 310, 30};

    SDL_RenderFillRect(renderer, &backButton);
    SDL_RenderFillRect(renderer, &paddleSpeed);
    SDL_RenderFillRect(renderer, &ballSpeed);

    TTF_Font *font = TTF_OpenFont("..\\assets\\m20_sp_ranker\\m20.ttf", 30);
    SDL_Color color = {0, 0, 0};

    SDL_Surface *backSurface = TTF_RenderText_Blended(font, "Back", color);
    SDL_Texture *backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
    SDL_FreeSurface(backSurface);
    SDL_Rect backDest = {60, 605, 80, 20};
    SDL_RenderCopy(renderer, backTexture, NULL, &backDest);

    char textSettingsPaddle[30];
    sprintf(textSettingsPaddle, "Vitesse joueur : %d", settings->paddleSpeed);

    SDL_Surface *paddleSurface = TTF_RenderText_Blended(font, textSettingsPaddle, color);
    SDL_Texture *paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    SDL_FreeSurface(paddleSurface);
    SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleSpeed);

    SDL_Surface *minusButtonSurfacePaddle = IMG_Load("..\\assets\\signe-moins.png");
    SDL_Texture *minusButtonTexturePaddle = SDL_CreateTextureFromSurface(renderer, minusButtonSurfacePaddle);
    SDL_FreeSurface(minusButtonSurfacePaddle);

    SDL_Surface *plusButtonSurfacePaddle = IMG_Load("..\\assets\\signe-plus.png");
    SDL_Texture *plusButtonTexturePaddle = SDL_CreateTextureFromSurface(renderer, plusButtonSurfacePaddle);
    SDL_FreeSurface(plusButtonSurfacePaddle);

    SDL_Rect minusButtonDestPaddle = {370, (SCREEN_HEIGHT / 2) + 5, 30, 30};
    SDL_Rect plusButtonDestPaddle = {410, (SCREEN_HEIGHT / 2) + 5, 30, 30};

    SDL_RenderCopy(renderer, minusButtonTexturePaddle, NULL, &minusButtonDestPaddle);
    SDL_RenderCopy(renderer, plusButtonTexturePaddle, NULL, &plusButtonDestPaddle);

    char textSettingsBall[30];
    sprintf(textSettingsBall, "Vitesse Balle : %d", settings->ballSpeed);

    SDL_Surface *ballSurface = TTF_RenderText_Blended(font, textSettingsBall, color);
    SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    SDL_FreeSurface(ballSurface);
    SDL_Rect ballDest = {810, (SCREEN_HEIGHT / 2) + 5, 310, 30};
    SDL_RenderCopy(renderer, ballTexture, NULL, &ballDest);

    SDL_Surface *minusButtonSurfaceBall = IMG_Load("..\\assets\\signe-moins.png");
    SDL_Texture *minusButtonTextureBall = SDL_CreateTextureFromSurface(renderer, minusButtonSurfaceBall);
    SDL_FreeSurface(minusButtonSurfaceBall);

    SDL_Surface *plusButtonSurfaceBall = IMG_Load("..\\assets\\signe-plus.png");
    SDL_Texture *plusButtonTextureBall = SDL_CreateTextureFromSurface(renderer, plusButtonSurfaceBall);
    SDL_FreeSurface(plusButtonSurfaceBall);

    SDL_Rect minusButtonDestBall = {1140, (SCREEN_HEIGHT / 2) + 5, 30, 30};
    SDL_Rect plusButtonDestBall = {1180, (SCREEN_HEIGHT / 2) + 5, 30, 30};

    SDL_RenderCopy(renderer, minusButtonTextureBall, NULL, &minusButtonDestBall);
    SDL_RenderCopy(renderer, plusButtonTextureBall, NULL, &plusButtonDestBall);

    SDL_DestroyTexture(minusButtonTexturePaddle);
    SDL_DestroyTexture(plusButtonTexturePaddle);
    SDL_DestroyTexture(minusButtonTextureBall);
    SDL_DestroyTexture(plusButtonTextureBall);
    SDL_DestroyTexture(backTexture);
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);
}

void displayBricks(SDL_Renderer *renderer, Brick bricks[]) {
    for (int i = 0; i < NUM_BRICKS; ++i) {
        if (bricks[i].lives > 0) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            if (bricks[i].lives == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            } else if (bricks[i].lives == 2) {
                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
            }
            SDL_RenderFillRect(renderer, &bricks[i].rect);
        }
    }
}

void displayLives(SDL_Renderer *renderer, int ballLeft) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < ballLeft; ++i) {
        SDL_Rect lifeRect = {10 + i * 25, 10, 20, 20};
        SDL_RenderFillRect(renderer, &lifeRect);
    }
}

void checkCollisionWithBricks(Brick bricks[], int numBricks, int ballX, int ballY, int ballRadius, int *ball_depl_x, int *ball_depl_y) {
    for (int i = 0; i < numBricks; ++i) {
        if (bricks[i].lives > 0) {
            if (ballX + ballRadius >= bricks[i].rect.x &&
                ballX - ballRadius <= bricks[i].rect.x + bricks[i].rect.w &&
                ballY >= bricks[i].rect.y &&
                ballY <= bricks[i].rect.y + bricks[i].rect.h) {

                bricks[i].lives--;
                *ball_depl_x = -(*ball_depl_x);
            }
            if (ballY + ballRadius >= bricks[i].rect.y &&
                ballY - ballRadius <= bricks[i].rect.y + bricks[i].rect.h &&
                ballX >= bricks[i].rect.x &&
                ballX <= bricks[i].rect.x + bricks[i].rect.w) {

                bricks[i].lives--;
                *ball_depl_y = -(*ball_depl_y);
            }
            if (bricks[i].lives == 0) {
                bricks->destroyed++;
            }
        }
    }

    if (bricks->destroyed == numBricks) {
        gameWon = true;
    }
}

void my_game(SDL_Renderer *renderer, int rect_x, int rect_y, GameSettings *settings) {
    SDL_Event event;
    SDL_bool quit = false;

    int ball_rect_x = 15;
    int ball_rect_y = 15;

    int ball_depl_x = settings->ballSpeed;
    int ball_depl_y = settings->ballSpeed;

    bool q_pressed = false;
    bool d_pressed = false;

    int lastTimer = SDL_GetTicks();

    Brick bricks[NUM_BRICKS];

    initializeBricks(bricks);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
                d_pressed = true;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
                q_pressed = true;
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_d) {
                d_pressed = false;
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q) {
                q_pressed = false;
            }
        }

        if (SDL_GetTicks() - lastTimer > 16) {
            if (q_pressed == true && rect_x > 0) {
                rect_x -= settings->paddleSpeed;
            }
            if (d_pressed == true && rect_x < SCREEN_WIDTH - 100) {
                rect_x += settings->paddleSpeed;
            }
            if (ball_rect_y >= SCREEN_HEIGHT) {
                lives--;

                if (lives <= 0) {
                    gameOver = true;
                } else {
                    ball_rect_x = 15;
                    ball_rect_y = 15;
                }
            }

            if (gameOver) {
                quit = true;
            }
            if (gameWon) {
                quit = true;
            }

            ball_rect_x += ball_depl_x;
            ball_rect_y += ball_depl_y;

            if (ball_rect_x >= SCREEN_WIDTH - 10 || ball_rect_x <= 0) {
                ball_depl_x = -ball_depl_x;
            }

            if (ball_rect_y <= 0) {
                ball_depl_y = -ball_depl_y;
            }

            if (ball_rect_y >= rect_y - 10 && ball_rect_y <= rect_y + 10 &&
                ball_rect_x >= rect_x - 10 && ball_rect_x <= rect_x + 100) {
                ball_depl_y = -ball_depl_y;
            }

            checkCollisionWithBricks(bricks, NUM_BRICKS, ball_rect_x, ball_rect_y, 5, &ball_depl_x, &ball_depl_y);

            lastTimer = SDL_GetTicks();
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        displayLives(renderer, lives);

        SDL_Rect playerRect = {rect_x, rect_y, 100, 10};
        SDL_Rect ballRect = {ball_rect_x, ball_rect_y, 10, 10};

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &ballRect);

        displayBricks(renderer, bricks);

        SDL_RenderPresent(renderer);
    }
}

void gameloop(SDL_Renderer *renderer) {
    SDL_bool quit = false;
    SDL_Event event;

    bool game = false;
    bool settings = false;

    int rect_x = SCREEN_WIDTH / 2;
    int rect_y = SCREEN_HEIGHT - 80;

    char *path_title = "..\\assets\\m20_sp_ranker\\m20.ttf";
    char *path_etoile = "..\\assets\\fond_etoile.jpg";

    SDL_Color color = {255, 255, 255};

    TTF_Font *font_title = TTF_OpenFont(path_title, 80);
    SDL_Surface *surface_title = TTF_RenderText_Blended(font_title, "Casse - briques", color);
    SDL_Texture *texture_title = SDL_CreateTextureFromSurface(renderer, surface_title);
    SDL_FreeSurface(surface_title);

    TTF_Font *font_leave_button = TTF_OpenFont(path_title, 50);
    SDL_Surface *surface_leave_button = TTF_RenderText_Blended(font_leave_button, "Quitter", color);
    SDL_Texture *texture_leave_button = SDL_CreateTextureFromSurface(renderer, surface_leave_button);
    SDL_FreeSurface(surface_leave_button);

    TTF_Font *font_play_button = TTF_OpenFont(path_title, 80);
    SDL_Surface *surface_play_button = TTF_RenderText_Blended(font_play_button, "Jouer", color);
    SDL_Texture *texture_play_button = SDL_CreateTextureFromSurface(renderer, surface_play_button);
    SDL_FreeSurface(surface_play_button);

    TTF_Font *font_settings_button = TTF_OpenFont(path_title, 50);
    SDL_Surface *surface_settings_button = TTF_RenderText_Blended(font_settings_button, "Parametres", color);
    SDL_Texture *texture_settings_button = SDL_CreateTextureFromSurface(renderer, surface_settings_button);
    SDL_FreeSurface(surface_settings_button);

    SDL_Surface *surface_screen = IMG_Load(path_etoile);
    SDL_Texture *texture_screen = SDL_CreateTextureFromSurface(renderer, surface_screen);
    SDL_FreeSurface(surface_screen);

    GameSettings settings_data;
    initializeSettings(&settings_data);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) {
                quit = true;
                break;
            } else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP) {
                if (event.motion.x > 50 && event.motion.x < 200 && event.motion.y > 380 && event.motion.y < 425 && settings == false) {
                    game = true;
                    quit = true;
                } else if (event.motion.x > 50 && event.motion.x < 200 && event.motion.y > 500 && event.motion.y < 530) {
                    settings = true;
                } else if (event.motion.x > 370 && event.motion.x < 400 && event.motion.y > (SCREEN_HEIGHT / 2) + 5 && event.motion.y < (SCREEN_HEIGHT / 2) + 35 && settings == true){
                    settings_data.paddleSpeed -= 5;
                } else if (event.motion.x > 410 && event.motion.x < 440 && event.motion.y > (SCREEN_HEIGHT / 2) + 5 && event.motion.y < (SCREEN_HEIGHT / 2) + 35 && settings == true){
                    settings_data.paddleSpeed += 5;
                } else if (event.motion.x > 1140 && event.motion.x < 1170 && event.motion.y > (SCREEN_HEIGHT / 2) + 5 && event.motion.y < (SCREEN_HEIGHT / 2) + 35 && settings == true){
                    settings_data.ballSpeed -= 5;
                } else if (event.motion.x > 1180 && event.motion.x < 1210 && event.motion.y > (SCREEN_HEIGHT / 2) + 5 && event.motion.y < (SCREEN_HEIGHT / 2) + 35 && settings == true){
                    settings_data.ballSpeed += 5;
                } else if (settings && event.motion.x > 50 && event.motion.x < 150 && event.motion.y > 600 && event.motion.y < 630) {
                    settings = false;
                } else if (event.motion.x > 50 && event.motion.x < 150 && event.motion.y > 600 && event.motion.y < 630) {
                    quit = true;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        if (game) {
            my_game(renderer, rect_x, rect_y, &settings_data);
        } else if (settings) {
            displaySettingsScreen(renderer, &settings_data);
        } else {
            displayLogo(renderer, texture_screen);
            displayTitle(renderer, texture_title);
            displayPlay(renderer, texture_play_button);
            displaySettings(renderer, texture_settings_button);
            displayQuit(renderer, texture_leave_button);
        }

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture_title);
    SDL_DestroyTexture(texture_leave_button);
    SDL_DestroyTexture(texture_play_button);
    SDL_DestroyTexture(texture_settings_button);
    SDL_DestroyTexture(texture_screen);
}

int main(int ac, char **av) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Error SDL_Init: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (NULL == window) {
        fprintf(stderr, "Error SDL_CreateWindow: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == renderer) {
        fprintf(stderr, "Error SDL_CreateRenderer: %s", SDL_GetError());
    }

    gameloop(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}