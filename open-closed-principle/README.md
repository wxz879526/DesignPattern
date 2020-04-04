# 开闭原则
假设我们现在拥有很多产品的记录存在于数据库。每种产品都有颜色和大小属性:
``` c++
enum class Color {Red, Green, Blue};
enum class Size {Small, Medium, Larger};

struct Product
{
	string name;
	Color color;
	Size size;
};
```

现在接到老板要求提供个函数能够过滤出指定属性的产品。咔咔很容易的写出了以下代码：
```
struct ProductFilter
{
	typedef vector<Product*> Items;
};

// 根据颜色过滤出指定属性的产品
ProductFilter::Items ProductFilter::by_color(Items items, Color color)
{
	Items result;
	for (auto &i : items)
		if (i->color == color)
			result.push_back(i);
	return result;
}
```