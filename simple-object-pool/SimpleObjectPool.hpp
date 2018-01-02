#pragma once
#include <memory>
#include <vector>
#include <functional>

template <typename T>
class SimpleObjectPool
{
public:
	using DeleteType = std::function<void(T*)>;

	void add(std::unique_ptr<T> t)
	{
		pool_.push_back(std::move(t));
	}

	std::unique_ptr<T, DeleteType> get()
	{
		if (pool_.empty())
		{
			throw std::logic_error("no more object");
		}

		std::unique_ptr<T, DeleteType> ptr(pool_.back().release(), [this](T *t) {
			pool_.push_back(std::unique_ptr<T>(t));
		});
		pool_.pop_back();

		return std::move(ptr);
	}

	bool empty() const
	{
		return pool_.empty();
	}

	size_t size() const
	{
		return pool_.size();
	}

private:
	std::vector<std::unique_ptr<T>> pool_;
};

/*
	SimpleObjectPool<Message1> p;
	p.add(std::unique_ptr<Message1>(new Message1()));
	p.add(std::unique_ptr<Message1>(new Message1()));
	{
		auto t = p.get();
		p.get();
	}

	{
		p.get();
		p.get();
	}

	std::cout << p.size() << std::endl;
*/