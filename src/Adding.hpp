#ifndef DEF_ADDING
#define DEF_ADDING

#include <SDL2/SDL.h>
#include "loading.hpp"
#include "State.hpp"
#include "Constant.hpp"

class Adding {
    public:
        Adding();
        ~Adding();
        void addFirstDigits(class Loading* game);
        void addDigit(class Loading* game, class State* state, int emptyRow[], int emptyColumn[], int positionCounted);
};

#endif //DEF_ADDING