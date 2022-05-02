#pragma once

#include "ReactorBase.hpp"

namespace app::controller
{

class Reactor : public reactor::ReactorBase<Reactor>
{
public:
    using ReactorBase::ReactorBase;
};

} // namespace app::controller
