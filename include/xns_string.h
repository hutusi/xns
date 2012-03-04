
#pragma once

#define __XNS_BEGIN_NAMESPACE namespace XNS {
#define __XNS_END_NAMESPACE }
#define __XNS_USING_NAMESPACE using namespace XNS;

#include <string>
#include <vector>

#include <regex>

__XNS_BEGIN_NAMESPACE

inline std::string operator*(const std::string& str, size_t times){
	std::string s;
	for (size_t i=0; i<times; ++i){
		s += str;
	}
	return s;
}

class String {
public:
	static std::vector<std::string>& split(const std::string& str, char splitter, std::vector<std::string>& out);
	static std::vector<std::string>& split(const char* str, size_t len, char splitter, std::vector<std::string>& out);
	static std::vector<std::string>& split(const std::string& str, const std::string& splitter, std::vector<std::string>& out);
	static std::vector<std::string>& split(const char* str, size_t len, const char* splitter, size_t sp_len, std::vector<std::string>& out);

	static std::string& trim(std::string& str);
	static std::string& trim(std::string& str, const std::string& trim_chars);
	static std::string& trim(std::string& str, const char* trim_chars, size_t n);
	static std::string& ltrim(std::string& str);
	static std::string& ltrim(std::string& str, const std::string& trim_chars);
	static std::string& ltrim(std::string& str, const char* trim_chars, size_t n);
	static std::string& rtrim(std::string& str);
	static std::string& rtrim(std::string& str, const std::string& trim_chars);
	static std::string& rtrim(std::string& str, const char* trim_chars, size_t n);

	static std::string& capitalize(std::string& str);
	static std::string& downcase(std::string& str);
	static std::string& upcase(std::string& str);
	static std::string& swapcase(std::string& str);
	static int casecmp(const std::string& x, const std::string& y);

	static std::string& reverse(std::string& str);
	static std::string& squeeze(std::string& str);
	static std::string& squeeze(std::string& str, const std::string& squeezed_str);
	static std::string& squeeze(std::string& str, const char* squeezed_str, size_t n);

	static std::vector<std::string>& lines(const std::string& str, std::vector<std::string>& out);

	static inline bool include(const std::string& str, const std::string& sub){
		return (str.find(sub) != std::string::npos);
	}
	static inline bool include(const std::string& str, const char* sub){
		return (str.find(sub) != std::string::npos);
	}
	static inline bool include(const std::string& str, const char* sub, size_t len){
		return (str.find(sub, len) != std::string::npos);
	}

	static std::string& replace(std::string& str, const std::string& replaced, const std::string& sub);
	static std::string& greplace(std::string& str, const std::string& replaced, const std::string& sub);
		
	static bool match(const std::string& str, const std::string& regexp);
	static std::vector<std::string>& search(const std::string& str, const std::string& regexp, std::vector<std::string>& out);
	static std::string& search(const std::string& str, const std::string& regexp, std::string& out);
	static std::string& sub(std::string& str, const std::string& regexp, const std::string& fmt);
	static std::string& gsub(std::string& str, const std::string& regexp, const std::string& fmt);

private:
	String(){}
};

__XNS_END_NAMESPACE
