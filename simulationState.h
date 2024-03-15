#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include <array>
#include "state.h"

#define PROGRESS_COUNTERS   3
#define PENDING_MOVES       3
#define LAST_DIR            7
#define LAST_PROTON         4
#define PROTON              1
#define ROW                 0
#define PENDING_ROW         1
#define COL                 1
#define PENDING_ROW         2
#define TARGET              0
#define MAT                 0
#define MOVE                1
#define NULL                2

class SimulationState : public State
{
  private:

    static std::array<int, PENDING_MOVES> pendingProtonMove;
    static std::array<int, BOARD_DIM> pendingNeutronMove;

    bool firstMove;
    std::array<unsigned , PROGRESS_COUNTERS> progressCounters;

    unsigned int moveNeutron();
    unsigned int changeNeutronDirection();
    unsigned int changeTargetedNeutron();

  public:

    SimulationState(bool activePlayer = PLAYER0, bool firstMove = false);
    //TODO Constructeur de copie...
    ~SimulationState();

    unsigned int moveProton();
    unsigned int changeProtonDirection();
    
    
};

#endif