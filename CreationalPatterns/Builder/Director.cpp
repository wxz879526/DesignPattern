#include "stdafx.h"
#include "IBuilder.h"
#include "Director.h"


Director::Director(IBuilder *pBuilder)
	: m_pBuilder(pBuilder)
{
}


Director::~Director()
{
}

Product* Director::Construct()
{
	if (m_pBuilder)
	{
		m_pBuilder->Build_Part1();
		m_pBuilder->Build_Part2();
		m_pBuilder->Build_Part3();
		return m_pBuilder->GetResult();
	}

	return nullptr;
}
