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
#define PION                1

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

    //MM virtual unsigned int changeTargetedProton();
    virtual unsigned int changeTargetedProton() { return 0; };

  public:

    friend class StateFriend;

    std::array<std::array<int, WIDTH>, WIDTH>& getBoard();


    State(bool activePlayer = PLAYER0);
    State(const State *previousState, bool activePlayer, bool firstMove =false);

    ~State();

    //MM virtual unsigned int moveProton();
    virtual unsigned int moveProton() { return 0; };

    //MM virtual unsigned int moveNeutron();
    virtual unsigned int moveNeutron() { return 0; };

    //MM virtual unsigned int changeProtonDirection();
    virtual unsigned int changeProtonDirection() { return 0; };

    //MM virtual unsigned int changeNeutronDirection();
    virtual unsigned int changeNeutronDirection() { return 0; };

    bool getFirstMove() const;
    int computeScore() const;
    unsigned int getNbProtonMoves(unsigned int proton, bool player) const;
};

#endif