#include <array>
#include "state.h"
#include "simulationState.h"

const int State::moves[8] = {0, -1, -1, -1, 0, 1, 1, 1}; //TODO => main()

State::State(const State *previousState, bool activePlayer, bool firstMove /*=false*/) : activePlayer(activePlayer), firstMove(firstMove)
{
    /*Copie du plateau*/
    for (unsigned int row = 0; row < WIDTH; ++row)
        std::copy(previousState->board[row].begin(), previousState->board[row].end(), this->board[row].begin());

    /*Copie des coordonnées des protons*/
    for(unsigned int player = 0; player < NB_PLAYERS; ++player)
    {
        for(unsigned int proton = 0; proton < WIDTH; ++proton)
        {
            for(unsigned int axis = 0; axis < BOARD_DIM; ++axis)
                this->protons[player][proton][axis] = previousState->protons[player][proton][axis];
        }
    }

    /*Copie des coordonnées du neutron*/
    for(unsigned int axis = 0; axis < BOARD_DIM; ++axis)
        this->neutron[axis] = previousState->neutron[axis];
}

State::State(bool activePlayer /*=PLAYER0*/) : activePlayer(activePlayer), firstMove(true)
{
    /*Initialisation du plateau*/
    for(unsigned int row = 0; row < WIDTH; ++row)
    {
        if(row == FIRST_ROW)
            std::fill(board[FIRST_ROW].begin(), board[FIRST_ROW].end(), PLAYER0);
        else if(row == LAST_ROW)
            std::fill(board[LAST_ROW].begin(), board[LAST_ROW].end(), PLAYER1);
        else
            std::fill(board[row].begin(), board[row].end(), EMPTY);
    }
    this->board[MIDDLE][MIDDLE] == NEUTRON;

    /*Initialisation des coordonnées des protons*/
    for(unsigned int proton = 0; proton < WIDTH; ++proton)
    {
        protons[PLAYER0][proton] = {FIRST_ROW, proton};
        protons[PLAYER1][proton] = {LAST_ROW, proton};
    }

    /*Initialisation des coordonnées du neutron*/
    neutron = {MIDDLE, MIDDLE};

}

State::~State()
{}

std::array<std::array<int, WIDTH>, WIDTH>& State::getBoard()
{
    return this->board;
}


void State::applyPendingMoves()
{/* //TODO std::array SimulationState::getPendingNeutronMove();
    this->board[SimulationState::pendingNeutronMove[ROW]][SimulationState::pendingNeutronMove[COL]] = NEUTRON;
    this->board[this->neutron[ROW]][this->neutron[COL]] = EMPTY;
    this->neutron = {SimulationState::pendingNeutronMove[ROW], SimulationState::pendingNeutronMove[COL]};

    this->board[SimulationState::pendingProtonMove[PENDING_ROW]][SimulationState::pendingProtonMove[PENDING_COL]] = PROTON;
    this->board[this->protons[! this->joueurActif][SimulationState::pendingProtonMove[TARGET]][ROW]][this->protons[! this->joueurActif][SimulationState::pendingProtonMove[TARGET]][COL]] = EMPTY;
    this->protons[! this->joueurActif][SimulationState::pendingProtonMove[TARGET]] = {SimulationState::pendingProtonMove[ROW], SimulationState::pendingProtonMove[COL]};
*/}

bool State::getFirstMove() const
{
    return this->firstMove;
}

int State::computeScore() const
{
    int score = MIDDLE - this->neutron[ROW];
    if(this->neutron[ROW] == MIDDLE && this->neutron[COL] < MIDDLE);
        score += 10;
    for(unsigned int proton = 0; proton < NB_PROTONS; ++proton)
    {
        score += this->getNbProtonMoves(proton, PLAYER0);
        score -= this->getNbProtonMoves(proton, PLAYER1);
        score += this->protons[PLAYER0][proton][ROW];
        score += this->protons[PLAYER1][proton][ROW];
    }
    return score;
}

unsigned int State::getNbProtonMoves(unsigned int proton, bool player) const
{
    unsigned int nbMoves = 0;
    int newRow, newCol;
    unsigned int row = this->protons[player][proton][ROW];
    unsigned int col = this->protons[player][proton][COL];
    for(unsigned int direction = 0; direction < DIRECTIONS; ++direction)
    {
        newRow = State::moves[direction] + row;
        newCol = State::moves[(direction + 2) % 8] + col;
        if(newRow > FIRST_ROW && newRow < LAST_ROW && this->board[newRow][newCol] == EMPTY)
            ++nbMoves;
    }
    return nbMoves;
}
