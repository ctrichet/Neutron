#include "catch.hpp" // https://github.com/catchorg/Catch2
#include "../main/state.h"

class StateFriend;

TEST_CASE( "SimulationState Class" )
{
    State state1();
    State state2(true);

    CHECK(true);
}