#ifndef DEF_MENU
#define DEF_MENU

#include <SDL2/SDL.h>
#include <cstdlib>
#include "../modules/Button.hpp"
#include "Adding.hpp"
#include "State.hpp"
#include "loading.hpp"

class Menu {
    private:
        SDL_Event* event;
        SDL_Surface* image;
        SDL_Texture* textureMenu;
        SDL_Texture* textureOnHover;
        SDL_Texture* textureOfBackground;
        Button* restart;
        Button* continous;
        Button* help;
        Button* quit;
        SDL_Rect source;
        SDL_Rect destination;
        SDL_Rect srcOnHover;
        SDL_Rect dstOnHover;
        SDL_Rect srcBackground;
        SDL_Rect dstBackground;
        SDL_Rect target;
        SDL_Rect result;
        SDL_Point move;
        bool hover;
        bool clicked;
        bool buttonActive;
        bool clickHelp;
        bool clickQuit;
        bool menuActive;

    public:
        Menu(SDL_Renderer* renderer);
        ~Menu();
        void draw(SDL_Renderer* renderer, class Loading* game, class State* state, class Adding* add);
        void onHover(SDL_Event* event);
        void onClick(SDL_Event* event, State* state);
        void setEvent(SDL_Event* event);
        void changeButtonValue(bool* value);
        bool getClicked();
        void setClicked(bool click);
        void restartGame(Loading* game, Adding* add);
        bool getMenuActive();
        void setMenuActive(bool active);
        Button* getRestartButton();
};

#endif //DEF_MENU