#include "knot.h"

Knot::Knot(State *state, bool firstMove =/*false*/) : depth(0), score(null), next(null)
{
    SimulationState::bestProtonMove.fill(EMPTY);
    SimulationState::bestNeutronMove.fill(EMPTY);
    Knot::bestProtonMove.fill(EMPTY);
    Knot::bestNeutronMove.fill(EMPTY);
    this->state = new SimulationState(state, PLAYER0, firstMove);
}

Knot::Knot(SimulationState *state, unsigned int depth, bool firstMove) : depth(depth), score(null), next(null)
{
    if(depth == MAX_DEPTH)
        this->state = new State(state, (this.depth % NB_PLAYERS), false);
    else
        this->state = new SimulationState(state, (this.depth % NB_PLAYERS), firstMove);
}
//TODO DeepCopies!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Knot::~Knot() 
{
    delete this->state;
}

int Knot::run()
{
    if(this.depth = MAX_DEPTH)
    {
        this->score = this->state.computeScore();
        return this->score;
    }
    if(this->state.firstMove)
        return handleFirstMoves(this->state->moveNeutron());
    else
        return handleMoves(this->state->moveProton());
    
}

int Knot::handleFirstMoves(int move)
{
    try
    {
        switch(move)
        {
            case WIN:
                if(! this.depth % NB_PLAYERS)
                {
                    this->score = MAX_SCORE + MAX_DEPTH - this.depth;
                    if(! this.depth)
                    {
                        bestProtonMove = //TODO
                        bestNeutronMove = //TODO
                    }
                    return this->score;
                }
                else if(this.score == null)
                {
                    this->score = MAX_SCORE + MAX_DEPTH - this.depth;;
                }
                return this->handleFirstMoves(this->changeNeutronDirection());
                break;

            case LOSE:
                if(this.depth % NB_PLAYERS)
                {
                    this->score = MIN_SCORE - MAX_DEPTH + this.depth;
                    return this->score;
                }
                else if(this.score == null)
                {
                    this->score = MIN_SCORE - MAX_DEPTH + this.depth;
                }
                return this->handleFirstMoves(this->changeNeutronDirection());
                break;

            case NULL:
                if(this.score)
                    return this->score;
                throw std::logic_error("Situation de Pat");
                break;

            default:
                if(this.next)
                    delete this.next;
                if(this.depth == MAX_DEPTH - 1)
                    this.next = new(Knot(this.state, MAX_DEPTH));//TODO
                else
                    this.next = new(Knot(this.state, this.depth + 1));//TODO
                int newScore = this->next->run(); //TODO dans le constructeur?
                if(! this.score || newScore > this->score)
                {
                    Knot::bestNeutronMove = //TODO
                    if(newScore > MAX_SCORE)
                        return newScore;
                    this->score = newScore;
                }
                return (this->handleFirstMoves(this->state->changeNeutronDirection()));
                break;
        }
            
    }
    catch (const std::logic_error& error)
    {
        return this->handleFirstMoves(this->state->changeProtonDirection());
    }
}

int Knot::handleMoves(int move)
{
    try
    {
        switch(this->state->moveProton())
        {
            case WIN:
                if(! this.depth % NB_PLAYERS)
                {
                    this->score = MAX_SCORE + MAX_DEPTH - this.depth;
                    if(! this.depth)
                    {
                        bestProtonMove = //TODO
                        bestNeutronMove = //TODO
                    }
                    return this->score;
                }
                else if(this.score == null)
                {
                    this->score = MAX_SCORE + MAX_DEPTH - this.depth;
                }
                return this->handleMoves(this->changeProtonDirection());
                break;

            case LOSE:
                if(this.depth % NB_PLAYERS)
                {
                    this->score = MIN_SCORE - MAX_DEPTH + this.depth;
                    return this->score;
                }
                else if(this.score == null)
                {
                    this->score = MIN_SCORE - MAX_DEPTH + this.depth;;
                }
                return this->handleMoves(this->changeProtonDirection());
                break;

            case NULL:
                if(this.score)
                    return this->score;
                throw std::logic_error("Situation de Pat");
                break;

            default:
                if(this.next)
                    delete this.next;
                if(this.depth == MAX_DEPTH - 1)
                    this.next = new(Knot(this.state, MAX_DEPTH));//TODO
                else
                    this.next = new(Knot(this.state, this.depth));//TODO
                int newScore = this->next->run(); //TODO dans le constructeur?
                if(! this.score || (! this.depth % NB_PLAYERS && newScore > this->score) || (this.depth % NB_PLAYERS && newScore < this->score))
                {
                    if(! this.depth)
                    {
                        this->bestNeutronMove = //TODO
                        this->bestProtonMove = //TODO
                    }
                    if(newScore > MAX_SCORE || newScore < MIN_SCORE)
                        return newScore;
                    this->score = newScore;
                }
                return (this->handleMoves(this->state->changeProtonDirection()));
                break;    
        }
    }
    catch (const std::logic_error& error)
    {
        return this->handleMoves(this->state->changeProtonDirection());
    }
}