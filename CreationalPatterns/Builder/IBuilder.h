#pragma once

class Product
{
public:
	void AddValue(std::string value)
	{
		m_strContent.append(value);
		m_strContent.append(" ");
	}

	void ShowInfo()
	{
		std::cout << m_strContent.c_str() << std::endl;
	}

private:
	std::string m_strContent;
};

class IBuilder
{
public:
	virtual void Build_Part1() = 0;
	virtual void Build_Part2() = 0;
	virtual void Build_Part3() = 0;
	virtual Product* GetResult() { return &m_product; }

protected:
	Product m_product;
};