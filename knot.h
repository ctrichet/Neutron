#ifndef KNOT_H
#define KNOT_H

#include "state.h"
#include "progress.h"

#define MAX_DEPTH        3
#define ERROR_UNDEFINED -1

class Knot 
{
  private:

    static std::array<std::array<unsigned int, 2>, 3> bestMove; //TODO replace 2 3
    unsigned int        depth;
    ScoreType<Score>    *score;
    State               *state;
    Knot                *next;
    
  public:

    Knot();
    Knot(State *state, unsigned int depth = 0);
    ~Knot();

    int getScore();
    unsigned int move();
};

#endif