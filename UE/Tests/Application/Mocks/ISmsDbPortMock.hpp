#pragma once

#include <gmock/gmock.h>
#include "Ports/ISmsDbPort.hpp"

namespace ue
{

class ISmsDbEventsHandlerMock : public ISmsDbEventsHandler
{
public:
    ISmsDbEventsHandlerMock();
    ~ISmsDbEventsHandlerMock();

};

class ISmsDbPortMock : public ISmsDbPort
{
public:
    ISmsDbPortMock();
    ~ISmsDbPortMock() override;

    MOCK_METHOD(void, addSms, (common::PhoneNumber from, common::PhoneNumber to, std::string text), (final));
};

}