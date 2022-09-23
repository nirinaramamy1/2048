#ifndef DEF_MOVING
#define DEF_MOVING

#include <SDL2/SDL.h>
#include <cstdlib>
#include "Loading.hpp"
#include "Checking.hpp"
#include "Scores.hpp"

class Moving {
    public:
        Moving();
        ~Moving();
        void up(Loading* game, State* state, Checking* check);
        void down(Loading* game, State* state, Checking* check);
        void left(Loading* game, State* state, Checking* check);
        void right(Loading* game, State* state, Checking* check);
};

#endif //DEF_MOVING
