

#include "../src/xns_string.cpp"

#include "gtest/gtest.h"

using namespace testing;
using namespace std;
__XNS_USING_NAMESPACE

static bool vector_equal_to_string_array(const vector<string>& vec, const string str_array[]){
	for(size_t i = 0; i < vec.size(); ++i){
			if(!(vec[i] == str_array[i])) return false;
		}
		return true;
}

class test_split_string : public Test{
protected:
	virtual void SetUp() {
	}
	virtual void TearDown() {
		out.clear();
	}

	vector<string> out;
};

TEST_F(test_split_string, use_normal_string){
	string s("");
	ASSERT_EQ(String::split(string("@@@qqq###@@@@ qqq @aaa "), '@', out).size(), 3);
	const string sa[] = {"qqq###", " qqq ", "aaa "};
	ASSERT_TRUE(vector_equal_to_string_array(out, sa));
}

TEST_F(test_split_string, use_null_string){
	string s("");
	ASSERT_EQ(String::split(string(""), '@', out).size(), 0);
}

TEST_F(test_split_string, use_string_excluded_splitter){
	string s("");
	ASSERT_EQ(String::split(string("@qqq###@ qqq @aaa "), "@@", out).size(), 1);
	const string sa[] = {"@qqq###@ qqq @aaa "};
	ASSERT_TRUE(vector_equal_to_string_array(out, sa));
}

TEST_F(test_split_string, use_normal_string_split_by_string){
	string s("");
	ASSERT_EQ(String::split(string("@@@qqq###@@@@ qqq @@aaa@ "), "@@", out).size(), 3);
	const string sa[] = {"@qqq###", " qqq ", "aaa@ "};
	ASSERT_TRUE(vector_equal_to_string_array(out, sa));
}

TEST_F(test_split_string, use_string_included_null_charactor){
	string s("");
	ASSERT_EQ(String::split(string("@@@\0@@\0@aaa@\0@bbb@\0@\0ccc\0@", 26), string("@\0@", 3), out).size(), 4);
	const string sa[] = {string("@@"), string("aaa"), string("bbb"), string("\0ccc\0@", 6)};
	ASSERT_TRUE(vector_equal_to_string_array(out, sa));
}

TEST(test_trim, trim_both_ends_blank)
{
	string s(" \t\t aaa \t bb\t\r\n  ");
	ASSERT_EQ(String::trim(s), "aaa \t bb");
}

TEST(test_trim, trim_blank_string)
{
	string s(" \t\n\t\t  ");
	ASSERT_EQ(String::trim(s), "");
}

TEST(test_trim, trim_string_spec_chars)
{
	string s(" xxxyzabcxxxdefg xyz");
	ASSERT_EQ(String::trim(s, string(" x\0yz", 5)), "abcxxxdefg");
}

TEST(test_trim, ltrim_string_spec_chars)
{
	string s(" xxxyzabcxxxdefg xyz");
	ASSERT_EQ(String::ltrim(s, string(" x\0yz", 5)), "abcxxxdefg xyz");
}

TEST(test_trim, rtrim_string_spec_chars)
{
	string s(" xxxyzabcxxxdefg xyz");
	ASSERT_EQ(String::rtrim(s, string(" x\0yz", 5)), " xxxyzabcxxxdefg");
}

TEST(test_string_case, capitalize){
	string s = "abc@";
	ASSERT_EQ(String::capitalize(s), "Abc@");
	s = "Abc@";
	ASSERT_EQ(String::capitalize(s), "Abc@");
	s = "@abc@";
	ASSERT_EQ(String::capitalize(s), "@abc@");
}

TEST(test_string_case, uppcase){
	string s = "abc@";
	ASSERT_EQ(String::upcase(s), "ABC@");
	s = "Abc@";
	ASSERT_EQ(String::upcase(s), "ABC@");
	s = "@ABC@";
	ASSERT_EQ(String::upcase(s), "@ABC@");
}

TEST(test_string_case, downcase){
	string s = "abc@";
	ASSERT_EQ(String::downcase(s), "abc@");
	s = "Abc@";
	ASSERT_EQ(String::downcase(s), "abc@");
	s = "@ABC@";
	ASSERT_EQ(String::downcase(s), "@abc@");
}

TEST(test_string_case, swapcase){
	string s = "abc@";
	ASSERT_EQ(String::swapcase(s), "ABC@");
	s = "Abc@";
	ASSERT_EQ(String::swapcase(s), "aBC@");
	s = "@ABC@";
	ASSERT_EQ(String::swapcase(s), "@abc@");
}

TEST(test_string_case, casecmp){
	ASSERT_EQ(String::casecmp("aBc@", "abC@"), 0);
	ASSERT_EQ(String::casecmp(" ABc@", " abC@"), 0);
	ASSERT_EQ(String::casecmp("ABC @", "ABC @"), 0);
}

TEST(test_reverse_string, reverse){
	string s = "abcdefghijk";
	ASSERT_EQ(String::reverse(s), "kjihgfedcba");
	s = "abcdefghijkl";
	ASSERT_EQ(String::reverse(s), "lkjihgfedcba");
}

TEST(test_squeeze_string, squeeze){
	string s = "aaabbc    cdefffg   ijjjj";
	ASSERT_EQ(String::squeeze(s), "abc cdefg ij");
	s = "aaabbc    cdefffg   ij\t\t\t\n\n\n";
	ASSERT_EQ(String::squeeze(s), "abc cdefg ij\t\n");
	s = "aaabbc    cdefffg   ij\t\t\t\n\n\n";
	ASSERT_EQ(String::squeeze(s, " ", 1), "aaabbc cdefffg ij\t\t\t\n\n\n");
}


TEST(test_lines, lines){
	string s = "\n\nabcd\r\naa\rb\n\raabb\n\n\r\n";
	vector<string> v;
	ASSERT_EQ(String::lines(s, v).size(), 3);
	// ASSERT_TRUE(vector_equal_to_string_array(v, {"abcd", "aa\rb", "\raabb"}));
}

TEST(test_replace, replace){
	string s = "abcdefabcdefdefffabcdef";
	ASSERT_EQ(String::replace(s, "def", "uvwxyz"), "abcuvwxyzabcdefdefffabcdef");
	s = "abcdefabcdefdefffabcdef";
	ASSERT_EQ(String::replace(s, "xyz", "uvwxyz"), "abcdefabcdefdefffabcdef");	
}

TEST(test_replace, greplace){
	string s = "abcdefabcdefdefffabcdef";
	ASSERT_EQ(String::greplace(s, "def", "uvwxyz"), "abcuvwxyzabcuvwxyzuvwxyzffabcuvwxyz");
	s = "abcdefabcdefdefffabcdef";
	ASSERT_EQ(String::greplace(s, "xyz", "uvwxyz"), "abcdefabcdefdefffabcdef");
}

TEST(test_match, match){
	ASSERT_TRUE(String::match("xabc123", "\\w*"));
}

TEST(test_search, search){
	string s;
	ASSERT_EQ(String::search("xa1234bc1234sss456", "\\d{3}", s), "123");
}

TEST(test_search, search_all){
	vector<string> v;
	String::search(string("xa123=4abc123ss123s333=45bc\0kkkkkk3ss123456feuyu", 35), "(\\d{3}=).{4}(\\d{3})", v);
}

TEST(test_substitute, sub){
	string s("ababc123=+abc");
	ASSERT_EQ(String::sub(s, "abc", "xx"), "abxx123=+abc");
}
