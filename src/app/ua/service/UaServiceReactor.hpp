#pragma once

#include "ReactorBase.hpp"

namespace app::ua::service
{

class Reactor : public reactor::ReactorBase<Reactor>
{
public:
    using ReactorBase::ReactorBase;
};

} // namespace app::ua::service
