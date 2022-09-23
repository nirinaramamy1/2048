#ifndef DEF_LOADING
#define DEF_LOADING

#include <SDL2/SDL.h>
#include <cstdlib>
#include "Constant.hpp"
#include "Scores.hpp"
#include "Adding.hpp"

class Loading {
    private:
        SDL_Renderer* renderer;
        SDL_Surface* image;
        SDL_Texture* images[16];
        SDL_Texture*** textureMap;
        SDL_Rect src;
        SDL_Rect dst[ROW][COLUMN];
        Scores gameScores = Scores(getRenderer());
        Button* restart;
        int** map;
        SDL_bool isOpen;

    public:
        Loading();
        ~Loading();
        void loadTexture(SDL_Renderer* renderer);
        void loadPosition();
        void update(SDL_Renderer* renderer);
        void setIsOpen(SDL_bool open);
        SDL_bool getIsOpen();
        //Here are some problems
        SDL_Texture* getAnImage(int digit);
        SDL_Texture** getImages();
        SDL_Texture*** getTextureMap();
        Scores* getScores();
        int** getMap();
        void setMap(int digit, int i, int j);
        void setTextureMap(SDL_Texture* image, int i, int j);
        void setRenderer(SDL_Renderer* renderer);
        SDL_Renderer* getRenderer();
        Button* getRestartButtonGameOver();
};

#endif //DEF_LOADING