#include "stdafx.h"
#include "ConcreteBuilder.h"


ConcreteBuilder::ConcreteBuilder()
{
}


ConcreteBuilder::~ConcreteBuilder()
{
}

void ConcreteBuilder::Build_Part1()
{
	std::cout << "ConcreteBuilder::Build_Part1" << std::endl;
	m_product.AddValue("Build_Part1");
}

void ConcreteBuilder::Build_Part2()
{
	std::cout << "ConcreteBuilder::Build_Part2" << std::endl;
	m_product.AddValue("Build_Part2");
}

void ConcreteBuilder::Build_Part3()
{
	std::cout << "ConcreteBuilder::Build_Part3" << std::endl;
	m_product.AddValue("Build_Part3");
}