#ifndef KNOT_H
#define KNOT_H

#include "state.h"
#include "simulationState.h"
#include "progress.h"

#define MAX_DEPTH        3
#define MAX_SCORE    10000
#define MAX_SCORE   -10000

class Knot 
{
  private:

    static std::array<int, PENDING_MOVES> bestProtonMove;
    static std::array<int, BOARD_DIM> bestNeutronMove;
    unsigned int        depth;
    ScoreType<Score>    *score;
    State               *state;
    Knot                *next;

    Knot(SimulationState *state, unsigned int depth, bool firstMove);
    int handleFirstMoves(int move);
    
  public:

    Knot(State *state, bool firstMove = false);
    ~Knot();

    int run();
};

#endif