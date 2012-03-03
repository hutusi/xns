
#include "../include/xns_string.h"

__XNS_BEGIN_NAMESPACE

std::vector<std::string>& String::split(const std::string& str, char splitter, std::vector<std::string>& out){
	return split(str.c_str(), str.length(), splitter, out);
}


std::vector<std::string>& String::split(const char* str, size_t len, char splitter, std::vector<std::string>& out){
	out.clear();
	if (len == 0) return out;

	const char* pos = str;
	size_t s_len = 0;
	for (size_t i = 0; i < len; ++i){
		if (*(pos + s_len) == splitter) {
			if (s_len > 0) out.push_back(std::string(pos, s_len));
			++pos;
			s_len = 0;
		} else {
			++s_len;
		}
	}

	if (s_len > 0) out.push_back(std::string(pos, s_len));
	return out;
}

std::vector<std::string>& String::split(const std::string& str, const std::string& splitter, std::vector<std::string>& out){
	return split(str.c_str(), str.length(), splitter.c_str(), splitter.length(), out);
}

std::vector<std::string>& String::split(const char* str, size_t len, const char* splitter, size_t sp_len, std::vector<std::string>& out){
	out.clear();
	if (len == 0 || sp_len == 0) return out;

	const char* pos = str;
	size_t s_len = 0;
	for (size_t i = 0; i < len; ++i){
		if (strncmp(pos, splitter, s_len) == 0) {
			if (s_len > 0) out.push_back(std::string(pos, s_len));
			++pos;
			s_len = 0;
		} else {
			++s_len;
		}
	}

	if (s_len > 0) out.push_back(std::string(pos, s_len));
	return out;
}

static inline bool Blank(char ch){
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

static size_t ltrim_len(const char* str, size_t len){
	size_t i = 0;
	for (i = 0; i < len; ++i){
		if (!Blank(*(str + i))) break;
	}
	return i;
}

static size_t rtrim_len(const char* str, size_t len){
	size_t i = 0;
	for (i = len; i > 0; --i){
		if (!Blank(*(str + i))) break;
	}

	return (len - i);
}

std::string& String::trim(std::string& str) {
	return ltrim(rtrim(str));
}

std::string& String::trim(const std::string& str, std::string& out){
	out = str;
	return ltrim(rtrim(out)); 
}

std::string& String::ltrim(std::string& str){
	size_t trim_len = ltrim_len(str.c_str(), str.length());
	if (trim_len > 0) str.erase(0, trim_len);
	return str;
}
std::string& String::ltrim(const std::string& str, std::string& out){
	out = str;
	return ltrim(out);
}

std::string& String::rtrim(std::string& str){
	size_t len = str.length();
	size_t trim_len = rtrim_len(str.c_str(), len);
	if (trim_len > 0) str.erase(len - trim_len, trim_len);
	return str;
}

std::string& String::rtrim(const std::string& str, std::string& out){
	out = str;
	return rtrim(out);
}

static inline bool is_uppercase(char ch){
	return (ch >= 'A' && ch <= 'Z');
}

static inline bool is_lowercase(char ch){
	return (ch >= 'a' && ch <= 'z');
}

std::string& String::capitalize(std::string& str){
	if (str.length() > 0 && is_lowercase(str[0])) {
		str.replace(0, 1, 1, (str[0] - 32));
	}
	return str;
}
std::string& String::capitalize(const std::string& str, std::string& out){
	out = str;
	return capitalize(out);
}

std::string& String::downcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
	}
	return str;
}

std::string& String::downcase(const std::string& str, std::string& out){
	out = str;
	return downcase(out);
}

std::string& String::upcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
	}
	return str;
}

std::string& String::upcase(const std::string& str, std::string& out){
	out = str;
	return upcase(out);
}

std::string& String::swapcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
		else if(is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
	}
	return str;
}

std::string& String::swapcase(const std::string& str, std::string& out){
	out = str;
	return swapcase(out);
}

static inline int cmp_char(char x, char y){
	if (x > y) return 1;
	else if (x < y) return -1;
	else return 0;
}

int String::casecmp(const std::string& x, const std::string& y){
	size_t x_len = x.length();
	size_t y_len = y.length();
	size_t len = x_len > y_len ? y_len : x_len;
	int r = 0;
	for (size_t i = 0; i < len ; ++i){
		if (is_uppercase(x[i]) && is_lowercase(y[i])) r = cmp_char(x[i]+32, y[i]);
		else if (is_lowercase(x[i]) && is_uppercase(y[i])) r = cmp_char(x[i], y[i]+32);
		else r = cmp_char(x[i], y[i]);
		if (r != 0) return r;
	}
	return cmp_char(x_len, y_len);
}

std::string& String::reverse(std::string& str){
	size_t len = str.length();
	size_t half_len = len / 2;
	for (size_t i = 0; i < half_len; ++i){
		if (str[i] != str[len-i-1]) {
			char ch = str[len-i-1];
			str.replace(len-i-1, 1, 1, str[i]);
			str.replace(i, 1, 1, ch);
		}
	}
	return str;
}
std::string& String::reverse(const std::string& str, std::string& out){
	out = str;
	return reverse(out);
}

static std::string& sub(std::string& str, const std::string& replaced, const std::string& sub);
static std::string& sub(const std::string& str, const std::string& replaced, const std::string& sub, std::string& out);
static std::string& gsub(std::string& str, const std::string& replaced, const std::string& sub);
static std::string& gsub(const std::string& str, const std::string& replaced, const std::string& sub, std::string& out);


__XNS_END_NAMESPACE
