
#include "xns/pattern/factory_template.h"
#include "xns/pattern/singleton.h"

#include "gtest/gtest.h"
using namespace testing;
using namespace std;

class Product{
public:
	virtual void Show(){cout<<"I'm base!";}
	DEFINE_SINGLETON(Product)
};

class AP : public Product{
public:
	DEFINE_PRODUCT_MAKER(Product, AP)

	virtual void Show(){cout<<"I'm AP!";}
};

REGISTER_PRODUCT_CATEGORY(Product, AP, 1)

TEST(test_factory, test){
	Factory<Product> fa;
	Product* p = fa.make(1);
	p->Show();
}
