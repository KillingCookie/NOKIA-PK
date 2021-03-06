#pragma once
#include "BaseMode.hpp"
#include "IUeGui.hpp"

namespace ue
{

class IUeGui::ICallMode : public IUeGui::BaseMode
{
public:
    virtual ~ICallMode() = default;

    virtual void appendIncomingText(const std::string &text) = 0;
    virtual void clearOutgoingText() = 0;
    virtual std::string getOutgoingText() const = 0;
};

}
