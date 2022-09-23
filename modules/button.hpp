#ifndef DEF_BUTTON
#define DEF_BUTTON

#include <SDL2/SDL.h>

class Button {
    private:
        SDL_Surface* surface;
        SDL_Texture* texture;
        SDL_Texture* textureOnHover;
        SDL_Texture* textureOfBackground;
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

    public:
        //constructor with three optionals arguments
        Button(
            SDL_Renderer* renderer,
            char const* path,
            SDL_Rect source,
            SDL_Rect destination,
            char const* pathOnHover = "",
            SDL_Rect srcOnHover = {0,0,0,0},
            SDL_Rect dstOnHover = {0,0,0,0},
            char const* pathBackground = "",
            SDL_Rect srcBackground = {0,0,0,0},
            SDL_Rect dstBackgournd = {0,0,0,0}
        );
        Button();
        ~Button();
        void draw(SDL_Renderer* renderer);
        void onHover(SDL_Event* event);
        void onClick(SDL_Event* event);
        bool getClickedValue();
        void setClickedValue(bool value);
        SDL_Rect* getSrcBackground();
        SDL_Rect* getDstBackground();
        SDL_Texture* getBackgroundTexture();
        SDL_Texture* getTexture();
};

#endif //DEF_BUTTON