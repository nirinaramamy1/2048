#include <SDL2/SDL.h>
#include "Moving.hpp"
#include "Constant.hpp"

#include <iostream>

Moving::Moving() {
    
}
Moving::~Moving() {

}
void Moving::up(Loading* game, State* state, Checking* check) {
    //int** map, SDL_Texture*** textureMap, SDL_Texture* images[]
    int i = 0, j = 0, k = 0, egality = 0, copyMap[ROW][COLUMN] = {{0}};
    int** map = nullptr;
    SDL_Texture*** textureMap = nullptr;
    SDL_Texture** images = nullptr;
    Scores* gameScores = nullptr;
    gameScores = game->getScores();

    map = game->getMap();
    textureMap = game->getTextureMap();
    images = game->getImages();

    for(i = 0; i < ROW; i++) {
        for(j = 0; j < COLUMN ; j++) {
            copyMap[i][j] = map[i][j];
        }
    }

    for(j=0; j<COLUMN; j++)
    {
        for(i=0; i<ROW; i++)
        {
            if(map[i][j] == 0)
            {
                for(k=i+1; k<COLUMN; k++)
                {
                    if(map[k][j] != 0)
                    {
                        map[i][j] = map[k][j];
                        map[k][j] = 0;    
                        textureMap[i][j] = textureMap[k][j];
                        textureMap[k][j] = nullptr;
                        i++;
                    }
                }
            }
        }
    }
    for(j=0; j<COLUMN; j++)
    {
        for(i=0; i<ROW-1; i++)
        {
            if(map[i][j] == map[i+1][j])
            {
                map[i][j] = map[i][j]+map[i+1][j];
                //somme(carte[i][j]);
                gameScores->setScores(gameScores->somme(map[i][j]));
                map[i+1][j] = 0;
                
                if(map[i][j] == 4)
                    textureMap[i][j] = images[1];
                else if(map[i][j] == 8)
                    textureMap[i][j] = images[2];
                else if(map[i][j] == 16)
                    textureMap[i][j] = images[3];
                else if(map[i][j] == 32)
                    textureMap[i][j] = images[4];
                else if(map[i][j] == 64)
                    textureMap[i][j] = images[5];
                else if(map[i][j] == 128)
                    textureMap[i][j] = images[6];
                else if(map[i][j] == 256)
                    textureMap[i][j] = images[7];
                else if(map[i][j] == 512)
                    textureMap[i][j] = images[8];
                else if(map[i][j] == 1024)
                    textureMap[i][j] = images[9];
                else if(map[i][j] == 2048)
                    textureMap[i][j] = images[10];
                else if(map[i][j] == 4096)
                    textureMap[i][j] = images[11];
                else if(map[i][j] == 8192)
                    textureMap[i][j] = images[12];
                else if(map[i][j] == 16384)
                    textureMap[i][j] = images[13];
                else if(map[i][j] == 32768)
                    textureMap[i][j] = images[14];
                textureMap[i+1][j] = nullptr;
                i++;
            }
        }
    }
    for(j=0; j<COLUMN; j++)
    {
        for(i=0; i<ROW; i++)
        {
            if(map[i][j] == 0)
            {
                for(k=i+1; k<COLUMN; k++)
                {
                    if(map[k][j] != 0)
                    {
                        map[i][j] = map[k][j];
                        map[k][j] = 0;    
                        textureMap[i][j] = textureMap[k][j];
                        textureMap[k][j] = nullptr;
                        i++;
                    }
                }
            }
        }
    }

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            if(map[i][j] == copyMap[i][j]) {
                egality++;
            }
        }
    }


    if(egality < ROW*COLUMN)
    {
        //verifierTableau(carte, carteImages, images, ecran);
        check->checkEmptyInMap(game, state);
    }

    //Free memory

}
void Moving::down(Loading* game, State* state, Checking* check) {
    int i = 0, j = 0, k = 0, egality = 0, copyMap[ROW][COLUMN] = {{0}};
    int** map = nullptr;
    SDL_Texture*** textureMap = nullptr;
    SDL_Texture** images = nullptr;
    Scores* gameScores = nullptr;
    gameScores = game->getScores();

    map = game->getMap();
    textureMap = game->getTextureMap();
    images = game->getImages();

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            copyMap[i][j] = map[i][j];
        }
    }

    for(j=0; j<COLUMN; j++)
    {
        for(i=ROW-1; i>0; i--)
        {
            if(map[i][j] == 0)
            {
                for(k=i-1; k>=0; k--)
                {
                    if(map[k][j] != 0)
                    {
                        map[i][j] = map[k][j];
                        map[k][j] = 0;
                        textureMap[i][j] = textureMap[k][j];
                        textureMap[k][j] = nullptr;
                        i--;
                    }
                }
            }
        }
    }
    for(j=0; j<COLUMN; j++)
    {
        for(i=ROW-1; i>0; i--)
        {
            if(map[i][j] == map[i-1][j])
            {
                map[i][j] = map[i][j]+map[i-1][j];
                //somme(carte[i][j]);
                gameScores->setScores(gameScores->somme(map[i][j]));
                map[i-1][j] = 0;
                
                if(map[i][j] == 4)
                    textureMap[i][j] = images[1];
                else if(map[i][j] == 8)
                    textureMap[i][j] = images[2];
                else if(map[i][j] == 16)
                    textureMap[i][j] = images[3];
                else if(map[i][j] == 32)
                    textureMap[i][j] = images[4];
                else if(map[i][j] == 64)
                    textureMap[i][j] = images[5];
                else if(map[i][j] == 128)
                    textureMap[i][j] = images[6];
                else if(map[i][j] == 256)
                    textureMap[i][j] = images[7];
                else if(map[i][j] == 512)
                    textureMap[i][j] = images[8];
                else if(map[i][j] == 1024)
                    textureMap[i][j] = images[9];
                else if(map[i][j] == 2048)
                    textureMap[i][j] = images[10];
                else if(map[i][j] == 4096)
                    textureMap[i][j] = images[11];
                else if(map[i][j] == 8192)
                    textureMap[i][j] = images[12];
                else if(map[i][j] == 16384)
                    textureMap[i][j] = images[13];
                else if(map[i][j] == 32768)
                    textureMap[i][j] = images[14];
                textureMap[i-1][j] = nullptr;
                i--;
            }
        }
    }
    for(j=0; j<COLUMN; j++)
    {
        for(i=ROW-1; i>0; i--)
        {
            if(map[i][j] == 0)
            {
                for(k=i-1; k>=0; k--)
                {
                    if(map[k][j] != 0)
                    {
                        map[i][j] = map[k][j];
                        map[k][j] = 0;
                        textureMap[i][j] = textureMap[k][j];
                        textureMap[k][j] = nullptr;
                        i--;
                    }
                }
            }
        }
    }

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            if(map[i][j] == copyMap[i][j]) {
                egality++;
            }
        }
    }

    if(egality < ROW*COLUMN)
    {
        //verifierTableau(carte, carteImages, images, ecran);
        check->checkEmptyInMap(game, state);
    }
}
void Moving::left(Loading* game, State* state, Checking* check) {
    int i = 0, j = 0, k = 0, egality = 0, copyMap[ROW][COLUMN] = {{0}};
    int** map = nullptr;
    SDL_Texture*** textureMap = nullptr;
    SDL_Texture** images = nullptr;
    Scores* gameScores = nullptr;
    gameScores = game->getScores();

    map = game->getMap();
    textureMap = game->getTextureMap();
    images = game->getImages();

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            copyMap[i][j] = map[i][j];
        }
    }

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            if(map[i][j] == 0)
            {
                for(k=j+1; k<COLUMN; k++)
                {
                    if(map[i][k] != 0)
                    {
                        map[i][j] = map[i][k];
                        map[i][k] = 0;
                        textureMap[i][j] = textureMap[i][k];
                        textureMap[i][k] = nullptr;
                        j++;
                    }
                }
            }
        }
    }
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN-1; j++)
        {
            if(map[i][j] == map[i][j+1])
            {
                map[i][j] = map[i][j]+map[i][j+1];
                //somme(carte[i][j]);
                gameScores->setScores(gameScores->somme(map[i][j]));
                map[i][j+1] = 0;
                
                if(map[i][j] == 4)
                    textureMap[i][j] = images[1];
                else if(map[i][j] == 8)
                    textureMap[i][j] = images[2];
                else if(map[i][j] == 16)
                    textureMap[i][j] = images[3];
                else if(map[i][j] == 32)
                    textureMap[i][j] = images[4];
                else if(map[i][j] == 64)
                    textureMap[i][j] = images[5];
                else if(map[i][j] == 128)
                    textureMap[i][j] = images[6];
                else if(map[i][j] == 256)
                    textureMap[i][j] = images[7];
                else if(map[i][j] == 512)
                    textureMap[i][j] = images[8];
                else if(map[i][j] == 1024)
                    textureMap[i][j] = images[9];
                else if(map[i][j] == 2048)
                    textureMap[i][j] = images[10];
                else if(map[i][j] == 4096)
                    textureMap[i][j] = images[11];
                else if(map[i][j] == 8192)
                    textureMap[i][j] = images[12];
                else if(map[i][j] == 16384)
                    textureMap[i][j] = images[13];
                else if(map[i][j] == 32768)
                    textureMap[i][j] = images[14];
                textureMap[i][j+1] = nullptr;
                j++;
            }
        }
    }
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            if(map[i][j] == 0)
            {
                for(k=j+1; k<COLUMN; k++)
                {
                    if(map[i][k] != 0)
                    {
                        map[i][j] = map[i][k];
                        map[i][k] = 0;
                        textureMap[i][j] = textureMap[i][k];
                        textureMap[i][k] = nullptr;
                        j++;
                    }
                }
            }
        }
    }

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            if(map[i][j] == copyMap[i][j]) {
                egality++;
            }
        }
    }

    if(egality < ROW*COLUMN)
    {
        //verifierTableau(carte, carteImages, images, ecran);
        check->checkEmptyInMap(game, state);
    }
}
void Moving::right(Loading* game, State* state, Checking* check) {
    int i = 0, j = 0, k = 0, egality = 0, copyMap[ROW][COLUMN] = {0};
    int** map = nullptr;
    SDL_Texture*** textureMap = nullptr;
    SDL_Texture** images = nullptr;
    Scores* gameScores = nullptr;
    gameScores = game->getScores();

    map = game->getMap();
    textureMap = game->getTextureMap();
    images = game->getImages();

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            copyMap[i][j] = map[i][j];
        }
    }

    for(i=0; i<ROW; i++)
    {
        for(j=COLUMN-1; j>0; j--)
        {
            if(map[i][j] == 0)
            {
                for(k=j-1; k>=0; k--)
                {
                    if(map[i][k] != 0)
                    {
                        map[i][j] = map[i][k];
                        map[i][k] = 0;    
                        textureMap[i][j] = textureMap[i][k];
                        textureMap[i][k] = nullptr;
                        j--;
                    }
                }
            }
        }
    }
    for(i=0; i<ROW; i++)
    {
        for(j=COLUMN-1; j>0; j--)
        {
            if(map[i][j] ==  map[i][j-1])
            {
                map[i][j] = map[i][j]+map[i][j-1];
                //somme(carte[i][j]);
                gameScores->setScores(gameScores->somme(map[i][j]));
                map[i][j-1] = 0;
                
                if(map[i][j] == 4)
                    textureMap[i][j] = images[1];
                else if(map[i][j] == 8)
                    textureMap[i][j] = images[2];
                else if(map[i][j] == 16)
                    textureMap[i][j] = images[3];
                else if(map[i][j] == 32)
                    textureMap[i][j] = images[4];
                else if(map[i][j] == 64)
                    textureMap[i][j] = images[5];
                else if(map[i][j] == 128)
                    textureMap[i][j] = images[6];
                else if(map[i][j] == 256)
                    textureMap[i][j] = images[7];
                else if(map[i][j] == 512)
                    textureMap[i][j] = images[8];
                else if(map[i][j] == 1024)
                    textureMap[i][j] = images[9];
                else if(map[i][j] == 2048)
                    textureMap[i][j] = images[10];
                else if(map[i][j] == 4096)
                    textureMap[i][j] = images[11];
                else if(map[i][j] == 8192)
                    textureMap[i][j] = images[12];
                else if(map[i][j] == 16384)
                    textureMap[i][j] = images[13];
                else if(map[i][j] == 32768)
                    textureMap[i][j] = images[14];
                textureMap[i][j-1] = nullptr;
                j--;
            }
        }
    }
    for(i=0; i<ROW; i++)
    {
        for(j=COLUMN-1; j>0; j--)
        {
            if(map[i][j] == 0)
            {
                for(k=j-1; k>=0; k--)
                {
                    if(map[i][k] != 0)
                    {
                        map[i][j] = map[i][k];
                        map[i][k] = 0;
                        textureMap[i][j] = textureMap[i][k];
                        textureMap[i][k] = nullptr;
                        j--;
                    }
                }
            }
        }
    }

    for(i=0; i<ROW; i++) {
        for(j=0; j<COLUMN; j++) {
            if(map[i][j] == copyMap[i][j]) {
                egality++;
            }
        }
    }
    
    if(egality < ROW*COLUMN)
    {
        //verifierTableau(carte, carteImages, images, ecran);
        check->checkEmptyInMap(game, state);
    }
}
