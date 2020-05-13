#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/SmsDbPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/ISmsDbPortMock.hpp"

namespace ue
{
using namespace ::testing;

class SmsDbPortTestSuite : public Test
{
protected:
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<ISmsDbEventsHandlerMock> handlerMock;

    SmsDbPort objectUnderTest{loggerMock};

    SmsDbPortTestSuite()
    {
        objectUnderTest.start(handlerMock);
    }
    ~SmsDbPortTestSuite()
    {
        objectUnderTest.stop();
    }
};

}
