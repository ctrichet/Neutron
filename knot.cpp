#include "knot.h"

Knot::Knot() : depth(0), score(null), state(new State()), next(null)
{
    this.move();
}

Knot::Knot(State *state, unsigned int depth /*=0*/) : depth(depth), score(null), state(state), next(null)
{
    this.move();
}

Knot::~Knot() 
{
    delete this->state;
}

int Knot::getScore()
{
    return this->score;
}

unsigned int Knot::move()
{
    if(this.depth = MAX_DEPTH)
        this->score = this->state.computeScore();
    else
    {
        //TODO
    }
    //TODO
}