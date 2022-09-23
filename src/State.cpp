#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "State.hpp"

#include <iostream>

State::State() {

}
State::State(SDL_Renderer* renderer) : isWin(false), isLose(false), winActived(false), loseActived(false) {
    image = IMG_Load("images/you_win.png");
    texutreGameWin = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("images/you_lose.png");
    textureGameOver = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    src = {0, 0, 0, 0}; dst = {200, 150, 410, 410};
    SDL_QueryTexture(textureGameOver, nullptr, nullptr, &src.w, &src.h);

    //Button when losing the game
    tryAgain = new Button(
        renderer,
        "images/try_again.png",
        {0,0,0,0},
        {275, 350, 260, 60},
        "images/try_again_hovered.png",
        {0,0,0,0},
        {270, 345, 270, 70}
    );
    quit = new Button(
        renderer,
        "images/quit.png",
        {0,0,0,0},
        {295, 429, 220, 60},
        "images/quit_hovered.png",
        {0,0,0,0},
        {290, 424, 230, 70}
    );

    //Button when winning the game
    restart = new Button(
        renderer,
        "images/restart.png",
        {0,0,0,0},
        {295, 429, 220, 60},
        "images/restart_hovered.png",
        {0,0,0,0},
        {290, 424, 230, 70}
    );
    keepGoing = new Button(
        renderer,
        "images/keep_going.png",
        {0,0,0,0},
        {275, 350, 260, 60},
        "images/keep_going_hovered.png",
        {0,0,0,0},
        {270, 345, 270, 70}
    );
}
State::~State() {
    //Delete sub-array
    for(int i = 0; i < ROW; i++) {
        delete[] map[i];
    }
    //Delete the pointer of array
    delete map;
}
void State::draw(SDL_Renderer* renderer, Loading* game, Menu* menu, Adding* add) {
    checkWin(game);
    /*
    if(isLose) {
        if(!loseActived) {
            gameOver(renderer);
            tryAgain->draw(renderer);
            quit->draw(renderer);
            if(quit->getClickedValue()) {
                std::cout << "Quit !!!!!!!!!!!!" << std::endl;
                *quitGame = SDL_FALSE;
            }
            if(tryAgain->getClickedValue()) {
                std::cout << "Try Again" << std::endl;
                menu->restartGame(game, add);
                game->getScores()->restartScores();
                setIsLose(false);
                tryAgain->setClickedValue(!tryAgain->getClickedValue());
            }
        }
    }*/
    
    if(isWin) {
        if(!winActived) {
            gameWin(renderer);
            restart->draw(renderer);
            keepGoing->draw(renderer);
            if(restart->getClickedValue()) {
                std::cout << "Restart" << std::endl;
                menu->restartGame(game, add);
                game->getScores()->restartScores();
                setIsWin(false);
                restart->setClickedValue(false);
            }
            if(keepGoing->getClickedValue()) {
                std::cout << "Keep Going" << std::endl;
                setIsWin(false);
                std::cout << isWin << std::endl;
                winActived = true;
                keepGoing->setClickedValue(false);
            }
        }
    }
}
void State::onHover(SDL_Event* event) {
    restart->onHover(event);
    quit->onHover(event);
    tryAgain->onHover(event);
    keepGoing->onHover(event);
}
void State::onClick(SDL_Event* event) {
    restart->onClick(event);
    quit->onClick(event);
    tryAgain->onClick(event);
    keepGoing->onClick(event);
}
void State::checkWin(Loading* game) {
    map = game->getMap();
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COLUMN; j++) {
            if(map[i][j] == 16) {
                setIsWin(true);
                //setStateActive(true);
            }
        }
    }
}
void State::gameOver(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, textureGameOver, &src, &dst);
}
void State::gameWin(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texutreGameWin, &src, &dst);
}
void State::setIsWin(bool win) {
    this->isWin = win;
}
bool State::getIsWin() {
    return isWin;
}
void State::setIsLose(bool lose) {
    this->isLose = lose;
}
bool State::getIsLose() {
    return isLose;
}
void State::setLoseActived(bool activeLose) {
    this->loseActived = activeLose;
}
bool State::getLoseActived() {
    return loseActived;
}
void State::setWinActived(bool activeWin) {
    this->winActived = activeWin;
}
bool State::getWinActived() {
    return winActived;
}
bool State::getStateActive() {
    return stateActive;
}
void State::setStateActive(bool active) {
    this->stateActive = active;
}