#ifndef STATE_H
#define STATE_H

#include <array>

#define NB_PLAYERS          2
#define BOARD_DIM           2
#define WIDTH               5
#define EMPTY              -1
#define PLAYER0             0
#define PLAYER1             1
#define NEUTRON             2
#define FIRST_ROW           0
#define LAST_ROW            4
#define MIDDLE              2

class State 
{
  private:

    bool    activePlayer;
    std::array<std::array<int, WIDTH>, WIDTH> board;
    std::array<std::array<std:array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> protons;
    std::array<unsigned int, BOARD_DIM> neutron;

  public:

    State();
    ~State();

    int computeScore() const;
    
};

#endif