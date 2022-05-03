#pragma once

#include "Logger.hpp"
#include "Singleton.hpp"

namespace app
{

template <typename Entity, typename State>
class FsmBase
{
public:
    explicit FsmBase(State* s)
        : state(s)
    {}

    State& getState() { return *state; }

    Entity& getEntity() { return *static_cast<Entity*>(this); }

    template <typename NewState>
    void transit()
    {
        auto* newState = &getSingleton<NewState>();
        if (newState == state)
        {
            LM(GEN, LE, "FSM %s: invalid transition", getEntity().name());
            return;
        }
        LM(GEN, LD, "FSM %s: transit %s -> %s", getEntity().name(), state->name(), newState->name());
        state->onExit(getEntity());
        state = newState;
        state->onEnter(getEntity());
    }
private:
    State* state;
};

} // namespace app
