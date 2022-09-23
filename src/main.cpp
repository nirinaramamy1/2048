//Sometimes I got this problem when quitting the application, that needs to search in google
//Assertion failed: hb_object_is_valid (obj), file ../external/harfbuzz-2.8.0/src/hb-object.hh, line 272
// g++ src/*.cpp modules/button.cpp -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "../modules/Button.hpp"
#include "Menu.hpp"
#include "Loading.hpp"
#include "Moving.hpp"
#include "Adding.hpp"
#include "Checking.hpp"
#include "Scores.hpp"

int main(int argc, char* argv[]) {
    // Initialisation of the video mode
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initiatisation of SDL_TTF
    if(TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Creating window and renderer
    SDL_Window* pWindow{nullptr};
    SDL_Renderer* pRenderer{nullptr};
    if(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Setting title and icon of the application
    SDL_Surface* icon = IMG_Load("images/icone.png");
    SDL_SetWindowTitle(pWindow, "2048");
    SDL_SetWindowIcon(pWindow, icon);
    SDL_FreeSurface(icon); // We Free the surface icon

    // Setting main background of the application
    SDL_Surface* grille = IMG_Load("images/grille.png");
    SDL_Texture* pTextureGrille = SDL_CreateTextureFromSurface(pRenderer, grille);
    SDL_FreeSurface(grille);
    SDL_Rect srcGrille{0, 0, 0, 0}, dstGrille{200, 150, 410, 410};
    SDL_QueryTexture(pTextureGrille, nullptr, nullptr, &srcGrille.w, &srcGrille.h);

    // Setting scores and besties
    SDL_Surface* scores = IMG_Load("images/scores.png");
    SDL_Surface* best = IMG_Load("images/best.png");
    SDL_Texture* pTextureScores = SDL_CreateTextureFromSurface(pRenderer, scores);
    SDL_Texture* pTextureBest = SDL_CreateTextureFromSurface(pRenderer, best);
    SDL_FreeSurface(scores);
    SDL_FreeSurface(best);
    SDL_Rect srcScores{0, 0, 0, 0}, dstScores{200, 50, 160, 60};
    SDL_Rect srcBest{0, 0, 0, 0}, dstBest{365, 50, 160, 60};
    SDL_QueryTexture(pTextureScores, nullptr, nullptr, &srcScores.w, &srcScores.h);
    SDL_QueryTexture(pTextureBest, nullptr, nullptr, &srcBest.w, &srcBest.h);

    // Setting the random function
    srand(time(nullptr));

    // Creating menu that manages some buttons
    Menu *menu = new Menu(pRenderer);
    
        std::cout << "Where we are ?" << std::endl;

    // Creating loading that manages all images
    Loading *game = new Loading();
        game->setRenderer(pRenderer);
    Scores *gameScores = nullptr;

        //std::cout << "Where we are ?" << std::endl;
        // Loading images and positions
        game->loadTexture(pRenderer);
        game->loadPosition();
        gameScores = game->getScores();
        

        //std::cout << "Where we are ?" << std::endl;

    // Creating command that moves the containt of game
    Moving *move = new Moving();

    //Game Loop
    SDL_Event event;
    SDL_bool isOpen{SDL_TRUE};

    //Testing game here
    Adding *add = new Adding();
    add->addFirstDigits(game);

    //Checking game
    Checking *check = new Checking();

    //State of game
    State *state = new State(pRenderer);

    //When restarting
    menu->restartGame(game, add);

    bool menuIsClicked = false;
    
    //Setting the last best scores from file
    gameScores->setScoresFromSave();
    gameScores->setScores(0);

    while(game->getIsOpen()) {

        while(SDL_PollEvent(&event)) {

            switch(event.type) {

                case SDL_KEYDOWN:
                    if(!menu->getClicked() || (state->getWinActived() && !state->getIsWin())) {
                        if(event.key.keysym.sym == SDLK_UP) {
                            move->up(game, state, check);
                        } 
                        else if(event.key.keysym.sym == SDLK_DOWN) {
                            move->down(game, state, check);
                        }
                        else if(event.key.keysym.sym == SDLK_LEFT) {
                            move->left(game, state, check);
                        }
                        else if(event.key.keysym.sym == SDLK_RIGHT) {
                            move->right(game, state, check);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(state->getStateActive()) {
                        state->onClick(&event);
                    }
                    if(menu->getMenuActive()) {
                        menu->onClick(&event, state);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if(state->getStateActive()) {
                        state->onHover(&event);
                    }
                    if(menu->getMenuActive()) {
                        menu->onHover(&event);
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        game->setIsOpen(SDL_FALSE);
                    }
                    break;
                default:
                    break;
            }
        }
        
        //Managing graphics interfaces
            //Set the primary color of the application
            SDL_SetRenderDrawColor(pRenderer, 1, 11, 111, 255);
            SDL_RenderClear(pRenderer);

            //Setting the scores and best
            SDL_RenderCopy(pRenderer, pTextureScores, &srcScores, &dstScores);
            SDL_RenderCopy(pRenderer, pTextureBest, &srcBest, &dstBest);

            //Setting the main background
            SDL_RenderCopy(pRenderer, pTextureGrille, &srcGrille, &dstGrille);

            //update images here
            game->update(pRenderer);

            //Here to manage state of game
            //game->gameOver(pRenderer);
            state->draw(pRenderer, game, menu, add);


            //Setting Scores
            gameScores->update(pRenderer);
            gameScores->draw(pRenderer);
            
            
            //Setting the menu button
            menu->draw(pRenderer, game, state, add);
        
        //Update the renderer
        SDL_RenderPresent(pRenderer);

        //For letting the cpu to take a sleep
        SDL_Delay(64);
    }

    //Vefication : Get scores
    std::cout << "In game, scores(string) : " << game->getScores()->getStringScores() << std::endl;
    std::cout << "In game, scores(long) : " << game->getScores()->getScoresGame() << std::endl;
    std::cout << "In gameScores, scores(string) : " << gameScores->getStringScores() << std::endl;
    std::cout << "Adress null : " << pTextureBest << std::endl;

    //Save scores
    gameScores->saveScores();

    //Free all memories
    SDL_DestroyTexture(pTextureScores);
    SDL_DestroyTexture(pTextureBest);
    SDL_DestroyTexture(pTextureGrille);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    menu->~Menu();
    game->~Loading();
    move->~Moving();
    check->~Checking();
    gameScores->~Scores();
    add->~Adding();
    state->~State();
    
    delete menu;
    delete game;
    delete move;
    delete check;
    delete gameScores;
    delete add;

    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}