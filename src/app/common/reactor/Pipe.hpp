#pragma once

#include <cstdint>

#include "FdHandler.hpp"

namespace reactor
{

class ReactorInterface;
struct PipeEvent;

class Pipe : public FdHandler
{
public:
    explicit Pipe(ReactorInterface&);

    ~Pipe();

    void send(PipeEvent const&);

    int getFd() const final;

    void onEvent(int) final;

private:
    ReactorInterface& reactor;
    int pipefd[2] = {};
};

} // namespace reactor
