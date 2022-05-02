#pragma once

#include "Logger.hpp"
#include "ReactorInterface.hpp"

namespace reactor
{

template <typename T>
class ReactorBase
{
public:
    ReactorBase(ReactorBase&) = delete;
    ReactorBase& operator=(ReactorBase const&) = delete;
    ReactorBase(ReactorInterface& reactor_)
    {
        reactor = &reactor_;
    }
    virtual ~ReactorBase() {}
    static ReactorInterface& get()
    {
        return *reactor;
    }

private:
    static ReactorInterface* reactor;
};

template <typename T>
ReactorInterface* ReactorBase<T>::reactor = nullptr;

} // namespace reactor
