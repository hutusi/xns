
#pragma once

#include <string>
#include <map>

#define DEFINE_SINGLETON(class_name)		\
	   class_name* get_instance(){			\
	   static class_name instance_;			\
	   return &instance_;					\
	}


class Singleton{
	friend class SingletonBox;
public:
	DEFINE_SINGLETON(Singleton)

private:
	~Singleton(){}
};

class SingletonBox{
public:
	DEFINE_SINGLETON(SingletonBox)

	Singleton* get(const char* name){
		return maps_[name];
	}

	Singleton* get(const std::string& name){
		return maps_[name];
	}

	bool register(const std::string& name, Singleton* instance);

private:
	std::map<std::string, Singleton*> maps_;
};
