#pragma once

#include "ISmsDbPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

struct Sms
{
    Sms(common::PhoneNumber from, common::PhoneNumber to, std::string text)
    {
        from = from;
        to = to;
        text = text;
        read = false;
    }

    common::PhoneNumber from;
    common::PhoneNumber to;
    std::string text;
    bool read;
};

class SmsDbPort : public ISmsDbPort
{
public:
    SmsDbPort(common::ILogger& logger);

    void start(ISmsDbEventsHandler& handler);
    void stop();

    void addSms(common::PhoneNumber from, common::PhoneNumber to, std::string text) override;

private:
    common::PrefixedLogger logger;
    ISmsDbEventsHandler* handler = nullptr;
    std::vector<Sms> db;
};

}
