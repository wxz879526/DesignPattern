#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Message.hpp"

struct Factory
{
	template<typename T>
	struct register_t
	{
		register_t(const std::string &key)
		{
			Factory::get().map_.emplace(key, [] {return new T(); });
		}

		template<typename ...Args>
		register_t(const std::string &key, Args... args)
		{
			Factory::get().map_.emplace(key, [&] {return T(args...); });
		}
	};

	Message* produce(const std::string &key)
	{
		if (map_.find(key) == map_.end())
		{
			throw std::invalid_argument("the message key is not exist");
		}

		return map_[key]();
	}

	std::unique_ptr<Message> produce_unique(const std::string &key)
	{
		return std::unique_ptr<Message>(produce(key));
	}

	std::shared_ptr<Message> produce_shared(const std::string &key)
	{
		return std::shared_ptr<Message>(produce(key));
	}

	static Factory& get()
	{
		static Factory instance;

		return instance;
	}
	
private:
	Factory(){}
	Factory(const Factory &f) = delete;
	Factory(Factory && f) = delete;

	std::map<std::string, std::function<Message*()>> map_;
};

#define REGISTER_MESSAGE_VNAME(T) reg_msg_##T##_
#define REGISTER_MESSAGE(T, key, ...) static Factory::register_t<T> REGISTER_MESSAGE_VNAME(T)(key, __VA_ARGS__);

// usage
// auto p = Factory::get().produce("message1");
// p->Foo();
//
//
