#include <array>
#include "state.h"

const int State::moves[8] = {0, 1, 1, 1, 0, -1, -1, -1};

State::State() : activePlayer(PLAYER0)
{
    /*Initialisation du plateau*/
    for(unsigned int row = 0; row < WIDTH; row++)
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
    for(unsigned int proton = 0; proton < WIDTH; proton++)
    {
        protons[PLAYER0][proton] = {FIRST_ROW, proton};
        protons[PLAYER1][proton] = {LAST_ROW, proton};
    }

    /*Initialisation des coordonnées du neutron*/
    neutron = {MIDDLE, MIDDLE};
    
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0)
}

State::State(bool activePlayer, std::array<std::array<int, WIDTH>, WIDTH> newBoard, std::array<std::array<std:array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> newProtons, std::array<unsigned int, BOARD_DIM> newNeutron) : activePlayer(! activePlayer), board(newBoard), protons(newProtons), neutron(newNeutron)
{
    /*Initialisation des compteurs de progression*/
    std::fill(progressCounters.begin(), progressCounters.end(), 0)
}

State::~State()
{}

int State::computeScore()
{
    //TODO
}

State *State::simulate(bool firstMove /*=False*/) //TODO Faudra songer à factoriser...
{
    std::array<std::array<int, WIDTH>, WIDTH> newBoard = this->board;
    std::array<std::array<std:array<unsigned int, BOARD_DIM>, NB_PROTONS>, NB_PLAYERS> newProtons = this->protons;
    std::array<unsigned int, BOARD_DIM> newNeutron = this->neutron;
    while(true)
    {
        if(progressCounters[PROTON] == DIRECTIONS)
        {
            progressCounters[PROTON] = 0;
            ++progressCounters[TARGET];
            if(progressCounters[TARGET] == NB_PROTONS)
            {
                if(firstMove)
                    return null;
                progressCounters[TARGET] = 0;
                while(true)
                {
                    ++progressCounters[NEUTRON]
                    if(progressCounters[NEUTRON] == DIRECTIONS)
                        return null;
                    int rowMove = State::moves[progressCounters[NEUTRON]];
                    int colMove = State::moves[(progressCounters[NEUTRON] + 2) % DIRECTIONS];
                    int row = this->neutron[ROW] + rowMove;
                    int col = this->neutron[COL] + colMove;
                    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
                        continue;
                    do
                    {
                        newNeutron = {row, col};
                        row += rowMove;
                        col += colMove;
                    } while(row > FIRST_ROW & row < LAST_ROW & col > FIRST_ROW & col < LAST_ROW & this->board[row][col] == EMPTY);
                    newBoard[this->neutron[ROW]][this->neutron[COL]] = EMPTY;
                    newBoard[newNeutron[ROW]][newNeutron[COL]] = NEUTRON;
                    break;
                }
                while(true)
                {
                    int rowMove = State::moves[this->progressCounters[PROTON]];
                    int colMove = State::moves[(this->progressCounters[PROTON] + 2) % DIRECTIONS];
                    int row = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW] + rowMove;
                    int col = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL] + colMove;
                    if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
                    {
                        ++progressCounters[PROTON];
                        if(progressCounters[PROTON] == DIRECTIONS)
                        {
                            progressCounters[PROTON] = 0;
                            ++progressCounters[TARGET];
                            if(progressCounters[TARGET] == NB_PROTONS)
                                return null;
                            continue;
                        }
                    }
                    do
                    {
                        newProtons[this->activePlayer][this->progressCounters[TARGET]] = {row, col};
                        row += rowMove;
                        col += colMove;
                    } while(row > FIRST_ROW & row < LAST_ROW & col > FIRST_ROW & col < LAST_ROW & this->board[row][col] == EMPTY);
                    newBoard[this->protons[activePlayer][this->progressCounters[TARGET]][ROW]][this->protons[activePlayer][this->progressCounters[TARGET]][COL]] = EMPTY;
                    newBoard[newProtons[this->activePlayer][this->progressCounters[TARGET]][ROW]][newProtons[this->activePlayer][this->progressCounters[TARGET]][COL]] = this->activePlayer;
                    return(new State(newBoard, newProtons, newNeutron)); //TODO Ceci n'est pas un constructeur de copie ATTENTION constructeur à faire!
                }
            }
            while(true)
            {
                int rowMove = State::moves[this->progressCounters[PROTON]];
                int colMove = State::moves[(this->progressCounters[PROTON] + 2) % DIRECTIONS];
                int row = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW] + rowMove;
                int col = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL] + colMove;
                if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
                {
                    ++progressCounters[PROTON];
                    if(progressCounters[PROTON] == DIRECTIONS)
                    {
                        progressCounters[PROTON] = 0;
                        ++progressCounters[TARGET];
                        if(progressCounters[TARGET] == NB_PROTONS)
                        {
                            return null;
                        }
                        continue;
                    }
                }
                do
                {
                    newProtons[this->activePlayer][this->progressCounters[TARGET]] = {row, col};
                    row += rowMove;
                    col += colMove;
                } while(row > FIRST_ROW & row < LAST_ROW & col > FIRST_ROW & col < LAST_ROW & this->board[row][col] == EMPTY);
                newBoard[this->protons[activePlayer][this->progressCounters[TARGET]][ROW]][this->protons[activePlayer][this->progressCounters[TARGET]][COL]] = EMPTY;
                newBoard[newProtons[this->activePlayer][this->progressCounters[TARGET]][ROW]][newProtons[this->activePlayer][this->progressCounters[TARGET]][COL]] = this->activePlayer;
                return(new State(newBoard, newProtons, newNeutron));
            }

        }
        int rowMove = State::moves[this->progressCounters[PROTON]];
        int colMove = State::moves[(this->progressCounters[PROTON] + 2) % DIRECTIONS];
        int row = this->protons[this->activePlayer][this->progressCounters[TARGET]][ROW] + rowMove;
        int col = this->protons[this->activePlayer][this->progressCounters[TARGET]][COL] + colMove;
        if(row < FIRST_ROW or row > LAST_ROW or col < FIRST_ROW or col > LAST_ROW or this->board[row][col] != EMPTY)
        {
            ++progressCounters[PROTON];
            continue;
        }
        do
        {
            newProtons[this->activePlayer][this->progressCounters[TARGET]] = {row, col};
            row += rowMove;
            col += colMove;
        } while(row > FIRST_ROW & row < LAST_ROW & col > FIRST_ROW & col < LAST_ROW & this->board[row][col] == EMPTY);
        newBoard[this->protons[activePlayer][this->progressCounters[TARGET]][ROW]][this->protons[activePlayer][this->progressCounters[TARGET]][COL]] = EMPTY;
        newBoard[newProtons[this->activePlayer][this->progressCounters[TARGET]][ROW]][newProtons[this->activePlayer][this->progressCounters[TARGET]][COL]] = this->activePlayer;
        return(new State(newBoard, newProtons, newNeutron));
    }
}