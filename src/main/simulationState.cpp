#include "simulationState.h"
#include "state.h"

//TODO DeepCopy statiques ou non! TT vérifier +bestMoves => KNOT!!!!!
SimulationState::SimulationState(State *state, bool activePlayer, bool firstMove /*=false*/) : State(state, activePlayer, firstMove)
{
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0);

    this->applyPendingMoves();

    /*Réinitialisation du coup en cours*/
    SimulationState::pendingProtonMove.fill(DEFAULT_MOVE);
    SimulationState::pendingNeutronMove.fill(DEFAULT_MOVE);
}

SimulationState::~SimulationState()
{}

unsigned int SimulationState::moveProton()
{
    unsigned int newRow, newCol;
    int rowMove = State::moves[this->progressCounters[PROTON]]; //TODO Regrouper ligne colonne ....
    int colMove = State::moves[(this->progressCounters[PROTON] + 2) % DIRECTIONS];
    int row = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW] + rowMove;
    int col = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL] + colMove;
    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
    {
        if(this->firstMove)
            return NONE;
        return changeNeutronDirection();
    }
    do
    {
        newRow = row;
        newCol = col;
        row += rowMove;
        col += colMove;
    } while(row > FIRST_ROW && row < LAST_ROW && col > FIRST_ROW && col < LAST_ROW && this->board[row][col] == EMPTY);
    SimulationState::pendingProtonMove = {this->progressCounters[TARGET], newRow, newCol};
    std::copy(SimulationState::pendingProtonMove.begin(), SimulationState::pendingProtonMove.end(), SimulationState::bestProtonMove.begin()); //TODO trop con, à faire if(! depth)!!!!
    return DEFAULT;
}

unsigned int SimulationState::moveNeutron()
{
    unsigned int newRow, newCol;
    int rowMove = State::moves[this->progressCounters[NEUTRON]];
    int colMove = State::moves[(this->progressCounters[NEUTRON] + 2) % DIRECTIONS];
    int row = this->neutron[ROW] + rowMove;
    int col = this->neutron[COL] + colMove;
    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
        return changeNeutronDirection();
    do
    {
        newRow = row;
        newCol = col;
        row += rowMove;
        col += colMove;
    } while(row > FIRST_ROW && row < LAST_ROW && col > FIRST_ROW && col < LAST_ROW && this->board[row][col] == EMPTY);
    SimulationState::pendingNeutronMove = {newRow, newCol};
    std::copy(SimulationState::pendingNeutronMove.begin(), SimulationState::pendingNeutronMove.end(), SimulationState::bestNeutronMove.begin());//TODO trop con, à faire if(! depth)!!!!
    if(newRow % LAST_ROW)
    {
        moveProton();
    }
    else if(newRow)
        return LOSE;
    return WIN;
}

unsigned int SimulationState::changeProtonDirection()
{
    if(this->progressCounters[PROTON] == LAST_DIR)
    {
        this->progressCounters[PROTON] = 0;
        return this->changeTargetedProton();
    }
    ++progressCounters[PROTON];
    return this->moveProton();

}

unsigned int SimulationState::changeNeutronDirection()
{
    if(this->progressCounters[NEUTRON] == LAST_DIR)
        return NONE;
    ++progressCounters[NEUTRON];
    return this->moveNeutron();
}

unsigned int SimulationState::changeTargetedProton()
{
    if(this->progressCounters[TARGET] == LAST_PROTON)
    {
        if(this->firstMove)
            return NONE;
        this->progressCounters[TARGET] = 0;
        return this->changeNeutronDirection();
    }
    ++progressCounters[TARGET];
    return this->moveProton();
}