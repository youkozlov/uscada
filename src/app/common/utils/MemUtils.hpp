#pragma once

namespace app::utils
{

template <typename TYPE>
TYPE memAlign(TYPE val)
{
    return (val + 15) & ~(TYPE)0x0F;
}

} // namespace app
