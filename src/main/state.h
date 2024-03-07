#ifndef STATE_H
#define STATE_H

#include <array>

#define NB_PLAYERS          2
#define BOARD_DIM           2
#define WIDTH               5
#define NB_PROTONS          5
#define DIRECTIONS          8
#define EMPTY              -1
#define PLAYER0             0
#define PLAYER1             1
#define NEUTRON             2
#define FIRST_ROW           0
#define LAST_ROW            4
#define MIDDLE              2

class State
{
  protected:

    static const int moves[8];

    bool    firstMove;
    bool    activePlayer;
    std::array<std::array<int, WIDTH>, WIDTH> board;
    std::array<std::array<std::array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> protons;
    std::array<unsigned int, BOARD_DIM> neutron;

    void applyPendingMoves();
    virtual unsigned int changeTargetedProton();

  public:

    friend class StateFriend;

    State(bool activePlayer = PLAYER0);
    State(const State *previousState, bool activePlayer, bool firstMove =false);

    ~State();

    virtual unsigned int moveProton();
    virtual unsigned int moveNeutron();
    virtual unsigned int changeProtonDirection();
    virtual unsigned int changeNeutronDirection();

    bool getFirstMove() const;
    int computeScore() const;
    unsigned int getNbProtonMoves(unsigned int proton, bool player) const;
};

#endif