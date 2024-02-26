#ifndef KNOT_H
#define KNOT_H

#include "state.h"
#include "progress.h"

#define MAX_DEPTH        3
#define ERROR_UNDEFINED -1

class Knot 
{
  private:

    unsigned int        depth;
    ScoreType<Score>    *score;
    State               *state;
    Progress            *progress;
    Knot                *next;
    
  public:
    Knot();
    Knot(State *state, unsigned int depth = 0);
    ~Knot();

    int getScore();
    unsigned int move();
};

#endif