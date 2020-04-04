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

嗯 非常棒 运行也如你所期待的。不幸运的是，几天后老板又过来让你提供个根据大小过滤产品的功能，显而易见的，你又会打开ProductFilter.cpp 添加以下代码：
```
// 根据大小过滤出指定属性的产品
ProductFilter::Items ProductFilter::by_size(Items items, Size size)
{
	Items result;
	for (auto &i : items)
		if (i->size == size)
			result.push_back(i);
	return result;
}
```

又过了一段时间 老板又来骚扰了 提出要根据颜色和大小过滤产品
// 根据颜色和大小过滤出指定属性的产品
```
ProductFilter::Items ProductFilter::by_size(Items items, Color color, Size size)
{
	Items result;
	for (auto &i : items)
		if (i->color == color && i->size == size)
			result.push_back(i);
	return result;
}
```

是不是以上的代码很像啊，by_color 和 by_size 仅仅是使用的属性不同。我们可以写一个携带predicate参数通用函数呀
