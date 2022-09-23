#include <SDL2/SDL.h>
#include "Adding.hpp"
#include "Constant.hpp"

#include <iostream>

Adding::Adding() {

}
Adding::~Adding() {

}
void Adding::addFirstDigits(Loading* game) {
    int i = 0, j = 0, k = 0, l = 0, digit[2] = {2,4};
    int** map = nullptr;
    SDL_Texture*** textureMap = nullptr;
    SDL_Texture** images = nullptr;
    map = game->getMap();//We get the map here
    textureMap = game->getTextureMap();//We get the texture map
    images = game->getImages();//We get images here

    i = rand()%ROW;
    k = rand()%ROW;
    j = rand()%COLUMN;
    l = rand()%COLUMN;

    if(i != k) {
        //carte[i][j] = chiffre[0];
        map[i][j] = digit[0];
        //carte[k][l] = chiffre[rand()%2];
        map[k][l] = digit[rand()%2];
        //carteImages[i][j] = images[0];
        textureMap[i][j] = images[0];
        if(map[k][l] == 2) {   
            textureMap[k][l] = images[0];
        }
        else {
            textureMap[k][l] = images[1];
        }
    } else {
        if(j != l) {
            map[i][j] = digit[rand()%2];
            map[k][l] = digit[0];
            textureMap[k][l] = images[0];
        
            if(map[i][j] == 2) {   
                textureMap[i][j] = images[0];
            }
            else {
                textureMap[i][j] = images[1];
            }
        }
        else {
            if(i > 0) {
                map[i-1][j] = digit[0];
                map[k][l] = digit[rand()%2];
                textureMap[i-1][j] = images[0];
            
                if(map[k][l] == 2) {   
                    textureMap[k][l] = images[0];
                }
                else {   
                    textureMap[k][l] = images[1];
                }
            }
            else {
                if(j > 0) {
                    map[i][j-1] = digit[0];
                    map[k][l] = digit[rand()%2];
                    textureMap[i][j-1] = images[0];
            
                    if(map[k][l] == 2) {   
                        textureMap[k][l] = images[0];
                    }
                    else {
                        textureMap[k][l] = images[1];
                    }   
                }
                else {
                    map[i+1][j] = digit[0];
                    map[k][l] = digit[rand()%2];
                    textureMap[i+1][j] = images[0];
                    
                    if(map[k][l] == 2) {   
                        textureMap[k][l] = images[0];
                    }
                    else {
                        textureMap[k][l] = images[1];
                    }
                }
            }
        }
    }
}
void Adding::addDigit(Loading* game, State* state, int emptyRow[], int emptyColumn[], int positionCounted) {
    int i = 0, j = 0;
    int countingRow = 0, countingColumn = 0, randomPosition = 0, digit[2] = {2,4};
    const int MAX = 1, MIN = 0;
    int** map = nullptr;
    SDL_Texture** images;
    SDL_Texture*** textureMap;
    images = game->getImages();
    map = game->getMap();
    textureMap = game->getTextureMap();

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            if(map[i][j] == 0)
            {
                randomPosition = rand()%positionCounted;
                if(digit[(rand() % (MAX - MIN + 1)) + MIN] == 2)
                {
                    textureMap[emptyRow[randomPosition]][emptyColumn[randomPosition]] = images[0];
                    map[emptyRow[randomPosition]][emptyColumn[randomPosition]] = 2;
                }
                else
                {
                    textureMap[emptyRow[randomPosition]][emptyColumn[randomPosition]] = images[1];
                    map[emptyRow[randomPosition]][emptyColumn[randomPosition]] = 4;
                }
                j = COLUMN;
                i = ROW;
            }
        }
    }
    for(i=0; i<ROW; i++)
    {
        for(j=1; j<COLUMN; j++)
        {
            if(map[i][j-1] != map[i][j])
            {
                if(map[i][j-1] == 0 || map[i][j] == 0)
                {
                    countingRow--;
                    j++;
                }
                countingRow++;
            }
        }
    }
    for(j=0; j<COLUMN; j++)
    {
        for(i=1; i<ROW; i++)
        {
            if(map[i-1][j] != map[i][j])
            {
                if(map[i-1][j] == 0 || map[i][j] == 0)
                {
                    countingColumn--;
                    i++;
                }
                countingColumn++;
            }
        }
    }


    if(countingRow == ROW*COLUMN-ROW && countingColumn == ROW*COLUMN-COLUMN)
    {
        //printf("Vous avez perdu !\n");
        //exit(EXIT_SUCCESS);
        //It works!
        state->setIsLose(true);
        std::cout << "You Lose!" << std::endl;
    }
}