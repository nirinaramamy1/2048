#include <SDL2/SDL_image.h>
#include <iostream>

#include "Menu.hpp"

//Creating menu button with constructor
Menu::Menu(SDL_Renderer* renderer) : hover(false), clicked(false), clickHelp(false), clickQuit(false), menuActive(true) {
    image = IMG_Load("images/menu_shut.png");
    textureMenu = SDL_CreateTextureFromSurface(renderer, image);
    image = IMG_Load("images/menu_light.png");
    textureOnHover = SDL_CreateTextureFromSurface(renderer, image);
    image = IMG_Load("images/background.png");
    textureOfBackground = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image); //Free surface first occasion
    source = {0, 0, 0, 0}; destination = {530, 50, 80, 60};
    srcOnHover = {0, 0, 0, 0}; dstOnHover = {525, 45, 90, 70};
    srcBackground = {0, 0, 0, 0}; dstBackground = {200, 150, 410, 410};
    SDL_QueryTexture(textureMenu, nullptr, nullptr, &source.w, &source.h);
    SDL_QueryTexture(textureOnHover, nullptr, nullptr, &srcOnHover.w, &srcOnHover.h);
    SDL_QueryTexture(textureOfBackground, nullptr, nullptr, &srcBackground.w, &srcBackground.h);
    target = {0, 0, 2, 2}; //We click a point

    //Creation of button
        //The restarting button
        restart = new Button(
            renderer,
            "images/restart.png",
            {0,0,0,0},
            {295, 225, 220, 60},
            "images/restart_hovered.png",
            {0,0,0,0},
            {289, 220, 230, 70}
        );
        //The continuing button
        continous = new Button(
            renderer,
            "images/continue.png",
            {0,0,0,0},
            {295, 295, 220, 60},
            "images/continue_hovered.png",
            {0,0,0,0},
            {289, 290, 230, 70}
        );
        //The helping button
        help = new Button(
            renderer,
            "images/help.png",
            {0,0,0,0},
            {295, 365, 220, 60},
            "images/help_hovered.png",
            {0,0,0,0},
            {289, 360, 230, 70},
            "images/helping.png",
            {0,0,0,0},
            {200, 150, 410, 410}
        );
        //The quiting button
        quit = new Button(
            renderer,
            "images/quit.png",
            {0,0,0,0},
            {295, 435, 220, 60},
            "images/quit_hovered.png",
            {0,0,0,0},
            {289, 430, 230, 70}
        );
}
Menu::~Menu() {
    SDL_DestroyTexture(textureMenu);
    SDL_DestroyTexture(textureOnHover);
    SDL_DestroyTexture(textureOfBackground);

    restart->~Button();
    continous->~Button();
    help->~Button();
    quit->~Button();

    delete event;
}
void Menu::draw(SDL_Renderer* renderer, Loading* game, State* state, Adding* add) {
    // When the cursor is hover
    if(hover) {
        SDL_RenderCopy(renderer, textureOnHover, &srcOnHover, &dstOnHover);
    } else {
        SDL_RenderCopy(renderer, textureMenu, &source, &destination);
    }

    // When cliked
    if(clicked) {
        state->setWinActived(!clicked);
        //Case restart button is clicked
        state->setWinActived(!state->getWinActived());
        if(restart->getClickedValue()) {
            //This is same like continous
            buttonActive = false;
            clicked = !clicked;
            //Here you have to work
            restartGame(game, add);
            game->getScores()->restartScores();
            //state->setIsLose(false);
            state->setIsWin(false);
            state->setWinActived(false);
            
        }
        //Case continue button is clicked
        if(continous->getClickedValue()) {
            buttonActive = false;
            clicked = !clicked;
            //state->setWinActived(false);
        }
        //Case help button is clicked
        if(help->getClickedValue()) {
            buttonActive = false;
            SDL_RenderCopy(
                renderer,
                help->getBackgroundTexture(),
                help->getSrcBackground(),
                help->getDstBackground()
            );
        }
        //Case quit button is clicked
        if(quit->getClickedValue()) {
            buttonActive = false;
            clicked = !clicked;
            game->setIsOpen(SDL_FALSE);
        }

        //Case no button is clicked
        if(!(restart->getClickedValue() ||
            continous->getClickedValue() ||
            help->getClickedValue() ||
            quit->getClickedValue()
        )) {
            SDL_RenderCopy(renderer, textureOfBackground, &srcBackground, &dstBackground);
            restart->draw(renderer);
            continous->draw(renderer);
            help->draw(renderer);
            quit->draw(renderer);
        }
    }

    if(!clicked) {
        state->setLoseActived(clicked);
        state->setWinActived(state->getWinActived());
    }
}
void Menu::onHover(SDL_Event* event) {
    move.x = event->motion.x;
    move.y = event->motion.y;
    if(SDL_PointInRect(&move, &destination)) {
        hover = true;
    } else {
        hover = false;
    }
    restart->onHover(event);
    continous->onHover(event);
    help->onHover(event);
    quit->onHover(event);
}
void Menu::onClick(SDL_Event* event, State* state) {
    target.x = event->button.x;
    target.y = event->button.y;
    if(SDL_IntersectRect(&target, &dstOnHover, &result)) {
        clicked = !clicked;
        if(clicked) {
            restart->setClickedValue(false);
            continous->setClickedValue(false);
            help->setClickedValue(false);  
            quit->setClickedValue(false);
        }
        buttonActive = true;
        state->setStateActive(false);
        std::cout << "State active : " << state->getStateActive() << std::endl;
    }
    if(buttonActive && clicked) {
        restart->onClick(event);
        continous->onClick(event);
        help->onClick(event);
        quit->onClick(event);
    }
}
bool Menu::getClicked() {
    return clicked;
}
void Menu::restartGame(Loading* game, Adding* add) {
    SDL_Texture*** textureMap = nullptr;
    int** map = nullptr;

    textureMap = game->getTextureMap();
    map = game->getMap();

    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COLUMN; j++) {
            textureMap[i][j] = nullptr;
            map[i][j] = 0;
        }
    }

    add->addFirstDigits(game);
}
Button* Menu::getRestartButton() {
    return restart;
}
void Menu::setClicked(bool click) {
    clicked = click;
}
void Menu::setMenuActive(bool active) {
    this->menuActive = active;
}
bool Menu::getMenuActive() {
    return menuActive;
}