#include "OpcUaController.hpp"
#include "ControllerReactor.hpp"

namespace app::controller
{

OpcUaController::OpcUaController()
    //: client(Reactor::get())
{
}

OpcUaController::~OpcUaController()
{
}

void OpcUaController::start()
{
    /*
    reactor::LinkAddr addr;
    addr.data[0] = 0x7f;
    addr.data[1] = 0x0;
    addr.data[2] = 0x0;
    addr.data[3] = 0x1;
    addr.data[4] = 0x2f;
    addr.data[5] = 0x70;
    listner.listen(addr);
*/
}

void OpcUaController::connect()
{
    /*
    reactor::LinkAddr addr;
    addr.data[0] = 0x7f;
    addr.data[1] = 0x0;
    addr.data[2] = 0x0;
    addr.data[3] = 0x1;
    addr.data[4] = 0x2f;
    addr.data[5] = 0x70;

    client.connect(addr);
    */
}


} // namespace app::controller
