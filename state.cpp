#include <array>
#include "state.h"

const int State::moves[8] = {0, 1, 1, 1, 0, -1, -1, -1};

State::State() : activePlayer(PLAYER0)
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
    board[MIDDLE][MIDDLE] == NEUTRON;

    /*Initialisation des coordonnées des protons*/
    for(unsigned int proton = 0; proton < WIDTH; ++proton)
    {
        protons[PLAYER0][proton] = {FIRST_ROW, proton};
        protons[PLAYER1][proton] = {LAST_ROW, proton};
    }

    /*Initialisation des coordonnées du neutron*/
    neutron = {MIDDLE, MIDDLE};
    
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0);
}

State::State(bool activePlayer, std::array<std::array<int, WIDTH>, WIDTH> newBoard, std::array<std::array<std:array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> newProtons, std::array<unsigned int, BOARD_DIM> newNeutron) : activePlayer(! activePlayer), board(newBoard), protons(newProtons), neutron(newNeutron)
{
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0);
}

State::~State()
{}

int State::computeScore()
{
    //TODO
}

unsigned int State::moveProton(bool save /*=false*/, bool firstMove /*=false*/) // TODO Variables globales save mais surtout firstMove!!!
{
    int rowMove = State::moves[this->progressCounters[PROTON]];
    int colMove = State::moves[(this->progressCounters[PROTON] + 2) % DIRECTIONS];
    int row = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW] + rowMove;
    int col = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL] + colMove;
    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
    {
        if(firstMove)
            return NULL;
        return changeNeutronDirection(save, firstMove);
    }
    //State::proton[OLD][ROW] = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW];//TODO En une ligne? 
    //State::proton[OLD][COL] = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL];//TODO
    do
    {
        State::proton/*[NEW]*/[ROW] = row;//TODO
        State::proton/*[NEW]*/[COL] = col;//TODO
        row += rowMove;
        col += colMove; 
    } while(row > FIRST_ROW & row < LAST_ROW & col > FIRST_ROW & col < LAST_ROW & this->board[row][col] == EMPTY);
    if(save)
        saveProtonMove(); //TODO
    return MOVE;
}

unsigned int State::moveNeutron(bool save /*=false*/, bool firstMove /*=false*/)
{
    int rowMove = State::moves[this->progressCounters[NEUTRON]];
    int colMove = State::moves[(this->progressCounters[NEUTRON] + 2) % DIRECTIONS];
    int row = this->neutron[ROW] + rowMove;
    int col = this->neutron[COL] + colMove;
    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
        return changeNeutronDirection(save, firstMove);
    //State::neutron[OLD][ROW] = this->neutron[this->progressCounters[NEUTRON]][ROW];//TODO En une ligne? 
    //State::neutron[OLD][COL] = this->neutron[this->progressCounters[NEUTRON]][COL];//TODO
    do
    {
        State::neutron/*[NEW]*/[ROW] = row;//TODO
        State::neutron/*[NEW]*/[COL] = col;//TODO
        row += rowMove;
        col += colMove;
    } while(row > FIRST_ROW & row < LAST_ROW & col > FIRST_ROW & col < LAST_ROW & this->board[row][col] == EMPTY);
    if(save)
        saveNeutronMove();//TODO
    if(row % LAST_ROW)
    {
        moveProton(save, FirstMove);
    }
    return MAT;
}

unsigned int State::changeProtonDirection(bool save /*=false*/, bool firstMove /*=false*/)
{
    if(progressCounters[PROTON] == LAST_DIR)
    {
        progressCounters[PROTON] = 0;
        return changeTargetedProton(save, firstMove);
    }
    ++progressCounters[PROTON];
    return moveProton(save, bool firstMove);

}

unsigned int State::changeNeutronDirection(bool save /*=false*/, bool firstMove /*=false*/)
{
    if(progressCounters[NEUTRON] == LAST_DIR)
        return NULL;
    ++progressCounters[NEUTRON];
    return moveNeutron(save, firstMove);
}

unsigned int State::changeTargetedProton(bool save /*=false*/, bool firstMove /*=false*/)
{
    if(progressCounters[TARGET] == LAST_PROTON)
    {
        if(firstMove)
            return NULL;
        progressCounters[TARGET] = 0;
        return changeNeutronDirection(save, firstMove);
    }
    ++progressCounters[TARGET];
    return moveProton(save, firstMove);
}