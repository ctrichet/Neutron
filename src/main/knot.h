#ifndef KNOT_H
#define KNOT_H

#include "state.h"
#include "simulationState.h"

#define MAX_DEPTH        3
#define MAX_SCORE      10000
#define MIN_SCORE     -10000
#define DEFAULT_SCORE -100000

using Score = int;

class Knot
{
  private:

    static std::array<int, PENDING_MOVES> bestProtonMove;
    static std::array<int, BOARD_DIM> bestNeutronMove;
    unsigned int        depth;
    Score               score;
    State               *state;
    Knot                *next;

    Knot(SimulationState *state, unsigned int depth, bool firstMove);
    int handleFirstMoves(int move);
    int handleMoves(int move);

  public:

    Knot(State *state, bool firstMove = false);
    ~Knot();

    int run();
};

#endif