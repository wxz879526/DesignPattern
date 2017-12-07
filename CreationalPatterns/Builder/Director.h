#pragma once

class IBuilder;
class Product;

class Director
{
public:
	Director(IBuilder *pBuilder);
	~Director();

	Product* Construct();

private:
	IBuilder *m_pBuilder;
};

