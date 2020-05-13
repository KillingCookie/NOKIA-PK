#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Mocks/ISmsDbPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include <memory>

namespace ue
{
using namespace ::testing;

class ApplicationTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::BtsId BTS_ID{203};
    const std::string TEXT{"Test"};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;
    StrictMock<ISmsDbPortMock> smsDbPortMock;

    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock,
                                smsDbPortMock};
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{};

TEST_F(ApplicationNotConnectedTestSuite, shallShowNotConnected)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleSib(BTS_ID);
}

struct ApplicationConnectingTestSuite : ApplicationTestSuite
{};

TEST_F(ApplicationConnectingTestSuite, shallShowConnecting)
{
    EXPECT_CALL(userPortMock, showConnecting());
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationConnectingTestSuite, shallSendAttachRequest)
{
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationConnectingTestSuite, shallStartTimer)
{
    using namespace std::literals;

    EXPECT_CALL(timerPortMock, startTimer(500ms));
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationConnectingTestSuite, shallStopTimerOnTimeout)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleTimeout();
}

TEST_F(ApplicationConnectingTestSuite, shallStopTimerOnAttachAccept)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationConnectingTestSuite, shallStopTimerOnAttachReject)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnDisconect){
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();
}

struct ApplicationConnectedTestSuite : ApplicationTestSuite
{};

TEST_F(ApplicationConnectingTestSuite, shallShowConnected)
{
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationConnectedTestSuite, shallShowNotConnectedOnDisconect){
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallShowNewSmsOnSmsReceived){
    EXPECT_CALL(userPortMock, showNewSms());
    objectUnderTest.handleSms(PHONE_NUMBER, PHONE_NUMBER, TEXT);
}

TEST_F(ApplicationConnectedTestSuite, shallSaveNewSmsToDbOnSmsReceived){
    EXPECT_CALL(smsDbPortMock, addSms(PHONE_NUMBER, PHONE_NUMBER, TEXT));
    objectUnderTest.handleSms(PHONE_NUMBER, PHONE_NUMBER, TEXT);
}
}
