#pragma once

#include "Logger.hpp"
#include "Singleton.hpp"

namespace app
{

template <typename Entity, typename State>
class FsmBase
{
public:
    explicit FsmBase(State* s, const char* n)
        : state(s)
        , name(n)
    {}

    State& getState() { return *state; }

    Entity& getEntity() { return *static_cast<Entity*>(this); }

    template <typename NewState>
    void transit()
    {
        auto* newState = &getSingleton<NewState>();
        if (newState == state)
        {
            LM(GEN, LE, "FSM %s: invalid transition", name);
            return;
        }
        LM(GEN, LI, "FSM %s: transit %s -> %s", name, state->name(), newState->name());
        state->onExit(getEntity());
        state = newState;
        state->onEnter(getEntity());
    }
private:
    State* state;
    const char* name;
};

} // namespace app
