#pragma once

#include "FsmBase.hpp"
#include "OpcUaServerSecureChannelState.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelInit;
class OpcUaServerSecureChannelReceiveOpenReq;
class OpcUaServerSecureChannelEstablished;

class OpcUaServerSecureChannel : public app::FsmBase<OpcUaServerSecureChannel, OpcUaServerSecureChannelState>
                               , public OpcUaSecureChannel
{
public:
    using SecureChannelHandler = std::function<void()>;

    OpcUaServerSecureChannel();

    ~OpcUaServerSecureChannel();

    char const* name() const { return "OpcUaServerSecureChannel"; }

    void onConnected(OpcUaConnection&) final;

    void onDataReceived(OpcUaConnection&) final;

    void onError() final;

    void onClosed() final;

private:
    friend OpcUaServerSecureChannelInit;
    friend OpcUaServerSecureChannelReceiveOpenReq;
    friend OpcUaServerSecureChannelEstablished;

    Result receiveOpenSecureChannelReq(OpcUaConnection&);
    Result sendOpenSecureChannelRsp(OpcUaConnection&);

    OpcUaSecureChannelHandler handler;
};

} // namespace app::ua
