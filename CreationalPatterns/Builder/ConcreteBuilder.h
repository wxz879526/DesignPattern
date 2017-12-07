#pragma once
#include "IBuilder.h"


class ConcreteBuilder :
	public IBuilder
{
public:
	ConcreteBuilder();
	~ConcreteBuilder();

	// implements of IBuilder
	virtual void Build_Part1() override;
	virtual void Build_Part2() override;
	virtual void Build_Part3() override;
};

