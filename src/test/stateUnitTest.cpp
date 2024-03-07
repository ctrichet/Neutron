#include "catch.hpp" // https://github.com/catchorg/Catch2
#include "../main/state.h"
#include "../main/stateFriend.cpp"

TEST_CASE( "State Class" )
{
    State state1;
    State state2(true);

    CHECK(StateFriend::getActivePlayer(state1) == PLAYER0);
    CHECK(StateFriend::getActivePlayer(state1) == PLAYER1);
    CHECK(! StateFriend::getFirstMove(state1));
    CHECK(StateFriend::getSquareContent(state1, MIDDLE, MIDDLE) == NEUTRON);
    for(unsigned int row = 1; row < MIDDLE; ++row)
    {
        for(unsigned int col = FIRST_ROW; col < WIDTH; ++col)
        {
            CHECK(StateFriend::getSquareContent(state1, row, col) == EMPTY);
            CHECK(StateFriend::getSquareContent(state1, row + MIDDLE, col) == EMPTY);
        }
    }
}