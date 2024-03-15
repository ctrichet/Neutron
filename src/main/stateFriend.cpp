
#ifndef STATETEST_H
#define STATETEST_H

#include "state.h"

class StateFriend
{
  public:

    virtual void abstractClass() = 0;

    static bool getFirstMove(const State& state)
    {
        return state.firstMove;
    }

    static bool getActivePlayer(const State& state)
    {
        return state.activePlayer;
    }

    static int getSquareContent(const State& state, unsigned int row, unsigned int col)
    {
        return state.board[row][col];
    }
};

#endif
