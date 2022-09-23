#ifndef DEF_SCORES
#define DEF_SCORES

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <fstream>

#include "../modules/button.hpp"

class Scores {
    private:
        long scoresGame;
        long bestScoresGame;
        std::string scores;
        std::string best;
        TTF_Font* font;
        SDL_Texture* textureScores;
        SDL_Texture* textureBest;
        SDL_Surface* textScores;
        SDL_Surface* textBest;
        SDL_Rect positionScores;
        SDL_Rect positionBest;

    public:
        Scores();
        Scores(SDL_Renderer* renderer);
        ~Scores();
        /*
        int getScores();
        void setBest();
        int getBest();*/
        void update(SDL_Renderer* renderer);
        void draw(SDL_Renderer* renderer);
        void setScores(long scores);
        long somme(long value);
        long getScoresGame();
        std::string getStringScores();
        void saveScores();
        void setScoresFromSave();
        void restartScores();
};

#endif //DEF_SCORES