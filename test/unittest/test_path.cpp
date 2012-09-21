#include "path.cpp"

#include "gtest/gtest.h"

using namespace testing;
using namespace std;
__XNS_USING_NAMESPACE

class test_current_path : public Test{
protected:
	virtual void SetUp() {
		pre_dir = Path::get_current();
	}
	virtual void TearDown() {
		Path::chdir(pre_dir.c_str());
	}
	
	string pre_dir;
};

TEST_F(test_current_path, get_and_set){
	cout<<"Current path: "<<pre_dir<<endl;
	ASSERT_TRUE(Path::chdir("D:\\tools"));
	ASSERT_EQ(0, strcmp("D:\\tools", Path::get_current()));
}

TEST_F(test_current_path, set_unformat_dir){
	ASSERT_TRUE(Path::chdir("D:/tools"));
	ASSERT_EQ(0, strcmp("D:\\tools", Path::get_current()));
}

TEST_F(test_current_path, set_incorrect_dir){
	ASSERT_FALSE(Path::chdir("D:/sefref"));
}
