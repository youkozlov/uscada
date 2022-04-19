#pragma once

namespace app
{

class ModbusClientState
{
public:
    virtual ~ModbusClientState() {}

    virtual void onConnect() {}

    virtual void onDataReceive() {}

    virtual void onError() {}

    virtual void onTimer() {}
};

} // namespace app
