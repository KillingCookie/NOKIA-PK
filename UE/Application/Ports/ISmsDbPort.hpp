#pragma once

#include "Messages/PhoneNumber.hpp"

namespace ue
{

class ISmsDbEventsHandler
{
public:
    virtual ~ISmsDbEventsHandler() = default;
};

class ISmsDbPort
{
public:
    virtual ~ISmsDbPort() = default;

    virtual void addSms(common::PhoneNumber from, common::PhoneNumber to, std::string text) = 0;
};

}
