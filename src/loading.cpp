#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Loading.hpp"

#include <iostream>

Loading::Loading() : isOpen(SDL_TRUE) {
    renderer = nullptr;
    src = {0,0,85,85};
    //We create a pointer to 2D array and initialize to null
    textureMap = new SDL_Texture**[ROW];
    for(int i = 0; i < ROW; i++) {
        textureMap[i] = new SDL_Texture*[COLUMN];
        for(int j = 0; j < COLUMN; j++) {
            textureMap[i][j] = nullptr;
        }
    }

    //We create a 2D array and initialize it
    map = new int*[ROW];
    for(int i = 0; i < 4; i++) {
        map[i] = new int[COLUMN];
        for(int j = 0; j < 4; j++) {
            map[i][j] = 0;
        }
    }
}
Loading::~Loading() {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COLUMN; j++) {
            SDL_DestroyTexture(textureMap[i][j]);
        }
    }
    for(auto const image : images) {
        SDL_DestroyTexture(image);
    }
}
void Loading::loadTexture(SDL_Renderer* renderer) {
    this->renderer = renderer;
    image = IMG_Load("images/2.png");
    images[0] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/4.png");
    images[1] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/8.png");
    images[2] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/16.png");
    images[3] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/32.png");
    images[4] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/64.png");
    images[5] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/128.png");
    images[6] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/256.png");
    images[7] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/512.png");
    images[8] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/1024.png");
    images[9] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/2048.png");
    images[10] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/4096.png");
    images[11] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/8192.png");
    images[12] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/16384.png");
    images[13] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/32768.png");
    images[14] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/65536.png");
    images[15] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
}

void Loading::loadPosition() {
    dst[0][0]={217,167,85,85}; dst[0][1]={314,167,85,85}; dst[0][2]={411,167,85,85}; dst[0][3]={508,167,85,85};
    dst[1][0]={217,264,85,85}; dst[1][1]={314,264,85,85}; dst[1][2]={411,264,85,85}; dst[1][3]={508,264,85,85};
    dst[2][0]={217,361,85,85}; dst[2][1]={314,361,85,85}; dst[2][2]={411,361,85,85}; dst[2][3]={508,361,85,85};
    dst[3][0]={217,458,85,85}; dst[3][1]={314,458,85,85}; dst[3][2]={411,458,85,85}; dst[3][3]={508,458,85,85};
}

void Loading::update(SDL_Renderer* renderer) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COLUMN; j++) {
            if(textureMap != nullptr) {
                SDL_RenderCopy(renderer, textureMap[i][j], &src, &dst[i][j]);
            }
        }
    }   
}

Button* Loading::getRestartButtonGameOver() {
    return this->restart;
}

SDL_Texture** Loading::getImages() {
    return images;
}
SDL_Texture*** Loading::getTextureMap() {
    return textureMap;
}
int** Loading::getMap() {
    return map;
}
void Loading::setTextureMap(SDL_Texture* image, int i, int j) {
    textureMap[i][j] = image;
}
SDL_Texture* Loading::getAnImage(int digit) {
    return images[digit];
}
void Loading::setMap(int digit, int i, int j) {
    map[i][j] = digit;
}
Scores* Loading::getScores() {
    return &gameScores;
}
void Loading::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}
SDL_Renderer* Loading::getRenderer() {
    return renderer;
}
void Loading::setIsOpen(SDL_bool open) {
    isOpen = open;
}
SDL_bool Loading::getIsOpen() {
    return isOpen;
}