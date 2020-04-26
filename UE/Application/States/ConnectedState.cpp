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

void ConnectedState::handleSms(common::PhoneNumber from, std::string text)
{
    logger.logInfo("Received SMS from ", from, ": «", text, "»");
}

}
