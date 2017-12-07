// Builder.cpp : 定义控制台应用程序的入口点。
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

