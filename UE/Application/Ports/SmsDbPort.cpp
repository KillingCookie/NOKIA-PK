#include "SmsDbPort.hpp"

namespace ue
{

SmsDbPort::SmsDbPort(common::ILogger &logger)
    : logger(logger, "[SMS-DB-PORT]")
{}

void SmsDbPort::start(ISmsDbEventsHandler &handler)
{
    this->handler = &handler;
}

void SmsDbPort::stop()
{
    handler = nullptr;
}

void SmsDbPort::addSms(common::PhoneNumber from, common::PhoneNumber to, std::string text)
{
	logger.logDebug("Save sms from ", from, " to ", to, ": ", text);
    db.push_back(Sms(from, to, text));
}

}
