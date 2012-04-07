
#pragma once

#include "../defs.h"

#include <vector>
#include <map>

typedef int _PRODUCT_CATEGORY;
typedef void* (*_MAKER)();

template<typename T>
class Factory{
public:
	virtual ~Factory(){
		for (std::vector<T*>::iterator iter = products_.begin(); iter != products_.end(); ++iter){
			delete *iter;
		}
	}

	T* make(_PRODUCT_CATEGORY cat, bool auto_recycle = true){
		if (get_categories().count(cat) == 0) { return 0; }
		T* p = (T*)(get_categories()[cat]());
		if (auto_recycle) { products_.push_back(p); }
		return p;
	}
	
	static bool Register(_PRODUCT_CATEGORY cat, _MAKER maker){
		get_categories()[cat] = maker;
		return true;
	}

	static std::map<_PRODUCT_CATEGORY, _MAKER>& get_categories(){
		static std::map<_PRODUCT_CATEGORY, _MAKER> categories_;
		return categories_;
	}

private:	
	std::vector<T*> products_;
};

class Product;
#define REGISTER_PRODUCT_CATEGORY(CATEGORY_TYPE, PRODUCT_CLASS) \
	static bool register_for_##PRODUCT_CLASS = Factory<Product>::Register(CATEGORY_TYPE, (_MAKER)(PRODUCT_CLASS::new_instance));
#define DEFINE_PRODUCT_MAKER(PRODUCT_CLASS) \
	static Product* new_instance(){  return new PRODUCT_CLASS();  }
