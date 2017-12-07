// Builder.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Director.h"
#include "ConcreteBuilder.h"

int main()
{
	Director d(new ConcreteBuilder());
	auto product = d.Construct();
	if (product != nullptr)
	{
		product->ShowInfo();
	}

    return 0;
}

