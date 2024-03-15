#include "simulationState.h"
#include "state.h"

State   *SimulationState::afterProtonMovementState;
State   *SimulationState::bestState = nullptr;
State   *SimulationState::pendingState = nullptr;

SimulationState::SimulationState(State *state, bool activePlayer, bool firstMove /*=false*/) : State(state, activePlayer, firstMove), afterNeutronMovementState(nullptr)
{
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0);
}

SimulationState::~SimulationState()
{}

State *SimulationState::getAfterNeutronMovementState()
{
    return this->afterNeutronMovementState;
}
void SimulationState::setAfterNeutronMovementState(State *state)
{
    this->afterNeutronMovementState = state;
}

State *SimulationState::getPendingState()
{
    return SimulationState::getPendingState();
}
void SimulationState::setPendingState(State *state)
{
    SimulationState::pendingState = nullptr;
}

unsigned int SimulationState::moveProton()
{
    int rowMove = State::moves[this->progressCounters[PROTON]];
    int colMove = State::moves[(this->progressCounters[PROTON] + 2) % DIRECTIONS];
    unsigned int row = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW];
    unsigned int col = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL];
    int newRow = row + rowMove;
    int newCol = col + colMove;

    State   *pendingState;
    if(this->firstMove)
        pendingState = this;
    else
        pendingState = this->afterNeutronMovementState;

    if(outOfBoard(newRow, newCol) || pendingState->getBoard()[newRow][newCol] != EMPTY)
    {
        return this->changeProtonDirection();
    }
    if(SimulationState::afterProtonMovementState)
        delete SimulationState::afterProtonMovementState;
    SimulationState::afterProtonMovementState = new State(pendingState);//TODO à partir de this ou de afterNeut..
    do
    {
        SimulationState::afterProtonMovementState->getBoard()[row][col] = EMPTY;
        SimulationState::afterProtonMovementState->getBoard()[newRow][newCol] = PION;
        row, col = newRow, newCol;
        newRow += rowMove;
        newCol += colMove;

    } while(not outOfBoard(newRow, newCol) && SimulationState::afterProtonMovementState->getBoard()[newRow][newCol] == EMPTY);
    return DEFAULT;
}

unsigned int SimulationState::moveNeutron()
{
    int rowMove = State::moves[this->progressCounters[NEUTRON]];
    int colMove = State::moves[(this->progressCounters[NEUTRON] + 2) % DIRECTIONS];
    unsigned int row = this->neutron[ROW];
    unsigned int col = this->neutron[COL];
    int newRow = row + rowMove;
    int newCol = col + colMove;
    if(outOfBoard(newRow, newCol) || this->board[row][col] != EMPTY)
        return changeNeutronDirection();
    if(this->afterNeutronMovementState)
        delete this->afterNeutronMovementState;
    this->afterNeutronMovementState = new State(this);//TODO vérifier
    do
    {
        this->afterNeutronMovementState->getBoard()[row][col] = EMPTY;
        this->afterNeutronMovementState->getBoard()[newRow][newCol] = PION;
        row, col = newRow, newCol;
        newRow += rowMove;
        newCol += colMove;
    } while(! outOfBoard(newRow, newCol) && this->board[newRow][newCol] == EMPTY);
    if(newRow % LAST_ROW)
    {
        return this->moveProton();
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

bool outOfBoard(int row, int col) //TODO ->Main
{
    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW)
        return true;
    return false;
}