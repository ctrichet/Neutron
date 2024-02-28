#include <array>
#include "state.h"

State::moves = {0, -1, -1, -1, 0, 1, 1, 1}; //TODO => main()

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

unsigned int State::getNbProtonMoves(unsigned int proton, bool player)
{
    unsigned int nbMoves = 0;
    int newRow, newCol;
    row = this->protons[player][proton][ROW];
    col = this->protons[player][proton][COL];    
    for(unsigned int direction = 0; direction < DIRECTIONS)
    {
        newRow = State::moves[direction] + row;
        newCol = State::moves[(direction + 2) % 8] + col;
        if(newRow > FIRST_ROW && newRow < LAST_ROW && this->board[newRow][newCol] == EMPTY)
            ++nbMoves;
    }
    return nbMoves;
}
