#include <array>
#include "state.h"

State::State(bool activePlayer /*=PLAYER0*/) : activePlayer(activePlayer)
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
    
}

State::~State()
{}

int State::computeScore()
{
    //TODO
}