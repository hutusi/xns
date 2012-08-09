
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

#define REGISTER_PRODUCT_CATEGORY(PRODUCT_TYPE, PRODUCT_CLASS, CATEGORY_TYPE) \
	static bool register_for_##PRODUCT_CLASS = Factory<PRODUCT_TYPE>::Register(CATEGORY_TYPE, (_MAKER)(PRODUCT_CLASS::new_instance));
#define DEFINE_PRODUCT_MAKER(PRODUCT_TYPE, PRODUCT_CLASS) \
	static PRODUCT_TYPE* new_instance(){  return new PRODUCT_CLASS();  }

/// usage: 
///		class SampleProductType{
///		  ...
///		};
///		typedef typedef Factory<SampleProductType> SampleFactory;
///		
///		#define REGISTER_SAMPLE_PRODUCT_CATEGORY(PRODUCT_CLASS, CATEGORY_TYPE)  \
///			REGISTER_PRODUCT_CATEGORY(SampleProductType, PRODUCT_CLASS, CATEGORY_TYPE)
///		#define DEFINE_SAMPLE_PRODUCT_MAKER(PRODUCT_CLASS)  \
///			DEFINE_PRODUCT_MAKER(SampleProductType, PRODUCT_CLASS)
/// 
/// more in:
///		command_factory.h
/// 