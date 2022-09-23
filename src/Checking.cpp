#include "Checking.hpp"

Checking::Checking() {

}
Checking::~Checking() {

}
void Checking::checkEmptyInMap(Loading* game, State* state, Adding* add) {
    int countEmpty = 0;
    int *emptyRow = nullptr, *emptyColumn = nullptr;
    int rowPosition[ROW*COLUMN] = {0}, columnPosition[ROW*COLUMN] = {0};
    int i = 0, j = 0, k = 0, l = 0;
    int** map = nullptr;
    map = game->getMap(); //Get map here

    for(i=0; i<ROW*COLUMN; i++)
    {
        rowPosition[i] = -1;
        columnPosition[i] = -1;
    }

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            if(map[i][j] == 0)
            {
                rowPosition[k] = i;
                columnPosition[k] = j;
                k++;
                countEmpty++;
            }
        }
    }

    if(countEmpty > 0)
    {
        l=0;
        //ligneVide = (int *)malloc(compteurPosition*sizeof(int));
        emptyRow = new int[countEmpty];
        //coloneVide = (int *)malloc(compteurPosition*sizeof(int));
        emptyColumn = new int[countEmpty];

        for(i=0; i<ROW*COLUMN; i++)
        {
            if(rowPosition[i] != -1)
            {
                emptyRow[l] = rowPosition[i];
                emptyColumn[l] = columnPosition[i];
                l++;
            }
        }
        
        add->addDigit(game, state, emptyRow, emptyColumn, countEmpty);
    }

    //free(emptyRow);
    delete[] emptyRow;
    //free(emptyColumn);
    delete[] emptyColumn;
}