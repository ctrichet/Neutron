#ifndef STATE_H
#define STATE_H

#include <array>

#define NB_PLAYERS          2
#define BOARD_DIM           2
#define WIDTH               5
#define NB_PROTONS          5
#define EMPTY              -1
#define PLAYER0             0
#define PLAYER1             1
#define NEUTRON             2
#define PROGRESS_COUNTERS   3
#define VERBOSE             1
#define FIRST_ROW           0
#define LAST_ROW            4
#define MIDDLE              2
#define DIRECTIONS          8
#define PROTON              1
#define ROW                 0
#define COL                 1
#define TARGET              0

class State 
{
  private:

    static const int moves[8];

    bool    activePlayer;
    std::array<std::array<int, WIDTH>, WIDTH> board;
    std::array<std::array<std:array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> protons;
    std::array<unsigned int, BOARD_DIM> neutron;
    std::array<unsigned , PROGRESS_COUNTERS> progressCounters;

  public:

    State();
    State(bool activePlayer, std::array<std::array<int, WIDTH>, WIDTH> newBoard, std::array<std::array<std:array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> newProtons, std::array<unsigned int, BOARD_DIM> newNeutron);
    ~State();

    int computeScore();
    State *simulate(bool firstMove = False);
    
};

#endif