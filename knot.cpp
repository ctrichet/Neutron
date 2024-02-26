#include "knot.h"

Knot::Knot() : depth(0), score(null), state(new State()), progress(new Progress()), next(null)
{
    this.move();
}

Knot::Knot(State *state, unsigned int depth /*=0*/) : depth(depth), score(null), state(state), progress(new Progress()), next(null)
{
    this.move();
}

Knot::~Knot() 
{
    delete this->state;
    delete this->progress;
}

int Knot::getScore()
{
    return this->score;
}

unsigned int Knot::move()
{
    if(this.depth = MAX_DEPTH)
        this->score = this->state.compute();
    else
    {
        //TODO
    }
    //TODO
}