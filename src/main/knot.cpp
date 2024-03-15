#include "knot.h"
#include <stdexcept>
#include <iostream>
#define DEBUG 0 //TODO ->Main

Knot::Knot(State *state, bool firstMove /*=false*/) : depth(0), score(DEFAULT_SCORE), next(nullptr)
{
    SimulationState::bestState = nullptr;
    SimulationState::pendingState = nullptr;
    this->state = new SimulationState(state, PLAYER0, firstMove);
}

Knot::Knot(SimulationState *state, unsigned int depth, bool firstMove) : depth(depth), score(DEFAULT_SCORE), next(nullptr)
{
    this->state = new SimulationState(state, (depth % NB_PLAYERS), firstMove);
}

Knot::~Knot()
{
    delete this->state;
}

int Knot::run()
{
    if(this->state->getFirstMove())
        return handleMoves(this->state->moveNeutron());
    else
        return handleMoves(this->state->moveProton());
}

int Knot::handleMoves(int move)
{
    try
    {
        switch(move)
        {
            case WIN:
                if(! this->depth % NB_PLAYERS)
                {
                    this->score = MAX_SCORE + MAX_DEPTH - this->depth;
                    if(! this->depth)
                    {
                        SimulationState::bestState = this->state->getAfterNeutronMovementState();
                        this->state->setAfterNeutronMovementState(nullptr);
                    }
                    return this->score;
                }
                else if(this->score == DEFAULT_SCORE)
                {
                    this->score = MAX_SCORE + MAX_DEPTH - this->depth;
                }
                return this->handleMoves(this->state->changeProtonDirection());
                break;

            case LOSE:
                if(this->depth % NB_PLAYERS)
                {
                    this->score = MIN_SCORE - MAX_DEPTH + this->depth;
                    return this->score;
                }
                else if(this->score == DEFAULT_SCORE)
                {
                    this->score = MIN_SCORE - MAX_DEPTH + this->depth;;
                }
                return this->handleMoves(this->state->changeNeutronDirection());
                break;

            case NONE:
                if(this->score)
                    return this->score;
                throw std::logic_error("Situation de Pat");
                break;

            default:
                if(! this->depth)
                {
                    if(SimulationState::pendingState)
                        delete SimulationState::pendingState;
                    SimulationState::pendingState = new State(SimulationState::afterProtonMovementState);//TODO check
                }
                int newScore;
                if(this->depth == MAX_DEPTH - 1)
                    newScore = SimulationState::afterProtonMovementState->computeScore();
                else
                {
                    if(this->next)
                        delete this->next;
                    this->next = new Knot(SimulationState::afterProtonMovementState, this->depth +1);//TODO check
                    newScore = this->next->run();
                }
                if(! this->score || (! this->depth % NB_PLAYERS && newScore > this->score) || (this->depth % NB_PLAYERS && newScore < this->score))
                {
                    if(! this->depth)
                    {
                        if(SimulationState::bestState)
                            delete SimulationState::bestState;
                        SimulationState::bestState = SimulationState::getPendingState();
                        SimulationState::setPendingState(nullptr);
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
        if(DEBUG)
            std::cout << "[Knot::handleMoves] ERROR: Situation de PAT" << std::endl;
        return NONE;
    }
}