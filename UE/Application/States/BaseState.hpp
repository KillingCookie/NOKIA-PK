#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleSms(common::PhoneNumber from, common::PhoneNumber to, std::string text) override;
    void handleCallRequest(common::PhoneNumber from) override;
    void handleDial(common::PhoneNumber to) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
