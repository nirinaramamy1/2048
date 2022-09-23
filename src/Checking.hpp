#ifndef DEF_CHECKING
#define DEF_CHECKING

#include "Loading.hpp"
#include "Adding.hpp"
#include "State.hpp"

class Checking {
    public:
        Checking();
        ~Checking();
        void checkEmptyInMap(Loading* game, State* state, Adding* add = nullptr);
};

#endif //DEF_CHECKING