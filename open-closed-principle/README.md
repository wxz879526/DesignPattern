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
ProductFilter::Items ProductFilter::by_color_and_size(Items items, Color color, Size size)
{
	Items result;
	for (auto &i : items)
		if (i->color == color && i->size == size)
			result.push_back(i);
	return result;
}
```

是不是以上的代码很像啊，by_color 和 by_size 仅仅是使用的属性不同。我们可以写一个携带predicate参数通用函数呀

回顾以上代码我们可以看到其实它已经违反了开闭原则：对修改关闭，对扩展开放。理想情况下新增的过滤功能不应该修改原有的功能
怎么重构呢？我们首先看看之前的ProductFilter其实违背了单一职责准则(SRP)，我们接下来的任务是剥离功能，
把它一分为二:一个过滤器(一个仅仅保存所有待过滤数据和返回符合条件的类)，一个过滤准则类，即把原先判断条件的任务交由过滤准则类处理
```
template<typename T>
struct Specification
{
	virtual bool is_satisfied(T *item) = 0;
};
```

```
template<typename T>
struct Filter
{
	virtual vector<T*> filter(vector<T*> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product>
{
	vector<Product*> filter(vector<Product*> items, Specification<Product> &spec) override
	{
		vector<Product*> result;
		for (auto &p : items)
			if (spec.is_satisfied()
				result.push_back(p);
		result result;
	}
};

struct ColorSpecification : Specification<Product>
{
	Color color;
	
	explicit ColorSpecification(const Color &color) :
	color{color} {}
	
	bool is_satisfied(Product* item) override
	{
		return item->color == color;
	}
};

template<typename T>
struct AndSpecification : Specification<T>
{
	Specification<T> &first;
	Specification<T> &second;
	
	AndSpecification(Specification<T> &first, Specification<T> &second)
	: first{first}
	, second{second} {}
	{
		
	}
	
	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};
```

```
// 测试代码
Product apple("Apple", Color::Green, Size::Small);
Product tree("Tree", Color::Green, Size::Large);
Product house("House", Color::Blue, Size::Large);

vector<Product*> all{&apple, &tree, &house};
BetterFilter bf;
ColorSpecification green(Color::Green);
auto green_things = bf.filter(all, green);
...
```
