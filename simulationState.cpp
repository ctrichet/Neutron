#include <array>
#include "simulationState.h"

SimulationState::SimulationState(bool activePlayer /*=PLAYER0*/, bool firstMove /*=false*/) : State(activePlayer), firstMove(firstMove)
{    
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0);

    /*Réinitialisation du coup en cours*/
    SimulationState::pendingProtonMove.fill(EMPTY);
    if(this->firstMove)
        SimulationState::pendingNeutronMove.fill(EMPTY);
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
            return NULL;
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
    return MOVE;
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
    if(row % LAST_ROW)
    {
        moveProton();
    }
    return MAT;
}

unsigned int SimulationState::changeProtonDirection()
{
    if(progressCounters[PROTON] == LAST_DIR)
    {
        progressCounters[PROTON] = 0;
        return changeTargetedProton();
    }
    ++progressCounters[PROTON];
    return moveProton();

}

unsigned int SimulationState::changeNeutronDirection()
{
    if(progressCounters[NEUTRON] == LAST_DIR)
        return NULL;
    ++progressCounters[NEUTRON];
    return moveNeutron();
}

unsigned int SimulationState::changeTargetedProton()
{
    if(progressCounters[TARGET] == LAST_PROTON)
    {
        if(this->firstMove)
            return NULL;
        progressCounters[TARGET] = 0;
        return changeNeutronDirection();
    }
    ++progressCounters[TARGET];
    return moveProton();
}