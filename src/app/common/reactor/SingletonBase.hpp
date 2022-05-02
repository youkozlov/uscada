#pragma once

#include <stdexcept>

namespace app::reactor
{

template <typename ENTITY>
class SingletonBase
{
public:
    explicit SingletonBase()
    {
        entity = static_cast<ENTITY*>(this);
    }
    virtual ~SingletonBase() {}

    static ENTITY& getInst()
    {
        if (nullptr == entity)
        {
            throw std::runtime_error("nullptr");
        }
        return *entity;
    }
private:
    static ENTITY* entity;
};

template <typename ENTITY>
ENTITY* SingletonBase<ENTITY>::entity = nullptr;

} // namespace app::reactor
