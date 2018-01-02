#pragma once

#include "MessageFactory.hpp"
#include "Message.hpp"

#include <iostream>

class Message1 : public Message
{
public:
	virtual void Foo() override
	{
		std::cout << "derive foo" << std::endl;
	}
};

REGISTER_MESSAGE(Message1, "message1");
