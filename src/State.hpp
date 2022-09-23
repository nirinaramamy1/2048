#ifndef DEF_STATE
#define DEF_STATE

#include <SDL2/SDL.h>
#include "../modules/button.hpp"
#include "loading.hpp"
#include "menu.hpp"
#include "Adding.hpp"

class State {
    private:
        SDL_Surface* image;
        SDL_Texture* textureGameOver;
        SDL_Texture* texutreGameWin;
        Button* restart;
        Button* quit;
        Button* tryAgain;
        Button* keepGoing;
        int** map;
        SDL_Rect src;
        SDL_Rect dst;
        bool isWin;
        bool isLose;
        bool winActived;
        bool loseActived;
        bool stateActive;
        long scoresWin;

    public:
        State(SDL_Renderer* renderer);
        State();
        ~State();
        void draw(SDL_Renderer* renderer, Loading* game, class Menu* menu, class Adding* add);
        void onHover(SDL_Event* event);
        void onClick(SDL_Event* event);
        void gameOver(SDL_Renderer* renderer);
        void gameWin(SDL_Renderer* renderer);
        void setIsWin(bool win);
        bool getIsWin();
        void setIsLose(bool lose);
        bool getIsLose();
        void setLoseActived(bool activeLose);
        bool getLoseActived();
        void setWinActived(bool activeWin);
        bool getWinActived();
        void checkWin(Loading* game);
        void setStateActive(bool active);
        bool getStateActive();
};


#endif //DEF_STATE