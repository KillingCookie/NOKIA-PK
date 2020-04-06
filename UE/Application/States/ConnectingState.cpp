#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"
#include "ConnectedState.hpp"

namespace ue
{

ConnectingState::ConnectingState(Context &context, common::BtsId btsId)
    : BaseState(context, "ConnectingState")
{
    using namespace std::literals;

    context.user.showConnecting();
    context.bts.sendAttachRequest(btsId);
    context.timer.startTimer(500ms);
}

void ConnectingState::handleTimeout()
{
    context.logger.logError("BTS connection timed out");
    context.setState<NotConnectedState>();
}

void ConnectingState::handleAttachAccept()
{
    context.logger.logInfo("BTS attach succeeded");
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void ConnectingState::handleAttachReject(){
    context.logger.logError("BTS attach rejected");
    context.timer.stopTimer();
    context.setState<NotConnectedState>();
}

}
