#pragma once

namespace app
{

template <typename TYPE>
static TYPE& getSingleton()
{
  static TYPE instance;
  return instance;
}

} // namespace app
