#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
	context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    logger.logInfo("Disconnected from BTS");
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSms(common::PhoneNumber from, common::PhoneNumber to, std::string text)
{
    context.smsdb.addSms(from, to, text);
    context.user.showNewSms();
}

}
