#pragma once

#include "FsmBase.hpp"
#include "OpcUaClientSecureChannelState.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelInit;
class OpcUaClientSecureChannelReceiveOpenRsp;
class OpcUaClientSecureChannelEstablished;

class OpcUaClientSecureChannel : public app::FsmBase<OpcUaClientSecureChannel, OpcUaClientSecureChannelState>
                               , public OpcUaSecureChannel
{
public:
    using SecureChannelHandler = std::function<void()>;

    OpcUaClientSecureChannel();

    ~OpcUaClientSecureChannel();

    char const* name() const { return "OpcUaClientSecureChannel"; }

    void onConnected(OpcUaConnection&) final;

    void onDataReceived(OpcUaConnection&) final;

    void onError() final;

    void onClosed() final;

private:
    friend OpcUaClientSecureChannelInit;
    friend OpcUaClientSecureChannelReceiveOpenRsp;
    friend OpcUaClientSecureChannelEstablished;

    Result sendOpenSecureChannelReq(OpcUaConnection&);
    Result receiveOpenSecureChannelRsp(OpcUaConnection&);

    OpcUaSecureChannelHandler handler;
};

} // namespace app::ua
