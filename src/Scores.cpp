#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "Scores.hpp"

Scores::Scores() {
    
}
Scores::Scores(SDL_Renderer* renderer) {
    scoresGame = 0;
    bestScoresGame = 0;
    font = TTF_OpenFont("fonts/nonserif.ttf", 16);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    scores = "0";
    best = "0";
    positionScores = {0,0,0,0};
    positionBest = {0,0,0,0};
}
Scores::~Scores() {
    TTF_CloseFont(font);
    SDL_FreeSurface(textScores);
    SDL_FreeSurface(textBest);
    SDL_DestroyTexture(textureScores);
    SDL_DestroyTexture(textureBest);
}
void Scores::update(SDL_Renderer* renderer) {
    textScores = TTF_RenderText_Blended(font, scores.c_str(), SDL_Color{255, 255, 255, 255});
    textBest = TTF_RenderText_Blended(font, best.c_str(), SDL_Color{255, 255, 255, 255});
    textureScores = SDL_CreateTextureFromSurface(renderer, textScores);
    textureBest = SDL_CreateTextureFromSurface(renderer, textBest);
    
    SDL_QueryTexture(textureScores, nullptr, nullptr, &positionScores.w, &positionScores.h);
    SDL_QueryTexture(textureBest, nullptr, nullptr, &positionBest.w, &positionBest.h);

    positionScores.x = 198 + 160/2 - positionScores.w/2;
    positionScores.y = 70 + 40/2 - positionScores.h/2;
    positionBest.x = 362 + 160/2 - positionBest.w/2;
    positionBest.y = 70 + 40/2 - positionBest.h/2;
}
void Scores::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, textureScores, nullptr, &positionScores);
    SDL_RenderCopy(renderer, textureBest, nullptr, &positionBest);
    SDL_FreeSurface(textScores);
    SDL_FreeSurface(textBest);
    SDL_DestroyTexture(textureScores);
    SDL_DestroyTexture(textureBest);
}
void Scores::setScores(long value) {
    scoresGame = value;
    scores = std::to_string(scoresGame);
    /*
    //std::cout << "Score : " << getScore() << std::endl;
    if(getMeilleurScore() <= getScore()){
        //std::cout << "Meilleur Score : " << getScore() << std::endl << std::endl;
        setMeilleurScore(getScore());
    }
    else {
        //std::cout << "Meilleur Score : " << getMeilleurScore() << std::endl << std::endl;
    }*/
    if(bestScoresGame <= scoresGame) {
        bestScoresGame = scoresGame;
        best = std::to_string(scoresGame);
    } 
    else {
        best = std::to_string(bestScoresGame);
    }
}
long Scores::somme(long value) {
    scoresGame = scoresGame + value;
    return scoresGame;
}
long Scores::getScoresGame() {
    return scoresGame;
}
std::string Scores::getStringScores() {
    return scores;
}
void Scores::restartScores() {
    scoresGame = 0;
    scores = "0";
}
void Scores::saveScores() {
    std::ofstream outFile;
    outFile.open("saveScores.txt");
        if(outFile.is_open()){
        outFile << "BestScores: " << std::endl;
        if(scoresGame <= bestScoresGame){
            outFile << bestScoresGame << std::endl;
        }
        else {
            outFile << scoresGame << std::endl;
        }
        outFile << "Scores:" << std::endl;
        outFile << scoresGame << std::endl;
    }
    outFile.close();
}
void Scores::setScoresFromSave() {
    std::string data = "";
    std::ifstream inFile;
    inFile.open("saveScores.txt");
    if(inFile.is_open()){
        inFile >> data;
        inFile >> data;
        //setMeilleurScore(stoi(donnee));
        //scores = data;
        //std::cout << scores << std::endl;
        bestScoresGame = stoi(data);

        /* Active it if you want save last game
        inFile >> data;
        inFile >> data;
        //setScore(stoi(donnee));
        //best = data;
        //std::cout << best << std::endl;
        scoresGame = stoi(data);
        */
    }
    inFile.close();
}