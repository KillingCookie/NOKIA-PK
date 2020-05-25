#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleDisconnected();
    void handleSms(common::PhoneNumber from, common::PhoneNumber to, std::string text);
    void handleCallRequest(common::PhoneNumber from);
    void handleDial(common::PhoneNumber to);
};

}
