#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include <array>
#include <algorithm>
#include "state.h"

#define BOARD_DIM           2
#define PROGRESS_COUNTERS   3
#define PENDING_MOVES       3
#define LAST_DIR            7
#define LAST_PROTON         4
#define PROTON              1
#define ROW                 0
#define PENDING_ROW         1
#define COL                 1
#define PENDING_COL         2
#define TARGET              0
#define DEFAULT_MOVE        42

#define LOSE                0
#define WIN                 1
#define DEFAULT             2
#define NONE                3

class SimulationState : public State
{
  private:

    static std::array<unsigned int, PENDING_MOVES> pendingProtonMove;
    static std::array<unsigned int, BOARD_DIM>     pendingNeutronMove;

    std::array<unsigned , PROGRESS_COUNTERS> progressCounters;

    unsigned int changeTargetedProton();

  public:

    static std::array<int, PENDING_MOVES> bestProtonMove;
    static std::array<int, BOARD_DIM>     bestNeutronMove;

    SimulationState(State *state, bool activePlayer, bool firstMove =false);
    ~SimulationState();

    unsigned int moveProton();
    unsigned int moveNeutron();
    unsigned int changeProtonDirection();
    unsigned int changeNeutronDirection();

};

#endif