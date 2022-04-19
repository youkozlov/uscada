#pragma once

#include <memory>
#include <vector>

#include "ReactorInterface.hpp"
#include "ComponentInterface.hpp"

namespace reactor { class ReactorManager; }

namespace app
{

enum class DeploymentType
{
      def
    , cpu3
};

class Deployer
{
public:
    void apply(reactor::ReactorManager&, DeploymentType);

};

} // namespace app