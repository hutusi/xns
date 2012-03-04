
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
			pos = str+i+1;
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


static inline bool in_chars(char ch, const char* chars, size_t n){
	for(size_t i=0; i<n; ++i){
		if(ch == chars[i]) return true;
	}
	return false;
}

static size_t ltrim_len(const char* str, size_t len, const char* trim_chars, size_t n){
	size_t i = 0;
	for (i = 0; i < len; ++i){
		if (!in_chars(*(str + i), trim_chars, n)) break;
	}
	return i;
}

static size_t rtrim_len(const char* str, size_t len, const char* trim_chars, size_t n){
	size_t i = 0;
	for (i = len; i > 0; --i){
		if (!in_chars(*(str + i), trim_chars, n)) break;
	}

	return (len - i);
}

std::string& String::trim(std::string& str, const std::string& trim_chars){
	return ltrim(rtrim(str, trim_chars.c_str(), trim_chars.length()), trim_chars.c_str(), trim_chars.length());
}

std::string& String::trim(std::string& str, const char* trim_chars, size_t n){
	return ltrim(rtrim(str, trim_chars, n), trim_chars, n);
}

std::string& String::ltrim(std::string& str, const std::string& trim_chars){
	return ltrim(str, trim_chars.c_str(), trim_chars.length());
}
std::string& String::ltrim(std::string& str, const char* trim_chars, size_t n){
	size_t trim_len = ltrim_len(str.c_str(), str.length(), trim_chars, n);
	if (trim_len > 0) str.erase(0, trim_len);
	return str;
}

std::string& String::rtrim(std::string& str, const std::string& trim_chars){
	return rtrim(str, trim_chars.c_str(), trim_chars.length());
}

std::string& String::rtrim(std::string& str, const char* trim_chars, size_t n){
	size_t len = str.length();
	size_t trim_len = rtrim_len(str.c_str(), len, trim_chars, n);
	if (trim_len > 0) str.erase(len - trim_len, trim_len);
	return str;
}

std::string& String::trim(std::string& str) {
	return ltrim(rtrim(str));
}

std::string& String::ltrim(std::string& str){
	return ltrim(str, " \t\n\r", 4);
}

std::string& String::rtrim(std::string& str){
	return rtrim(str, " \t\n\r", 4);
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

std::string& String::downcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
	}
	return str;
}

std::string& String::upcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
	}
	return str;
}

std::string& String::swapcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
		else if(is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
	}
	return str;
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

std::string& String::squeeze(std::string& str){
	size_t len = str.length();
	char last = str.back();
	size_t dup_n = 0;
	for(size_t i=len-1; i>0; --i){
		if (str[i-1] == last){
			++dup_n;
		} else {
			if (dup_n>0){
				str.erase(i, dup_n);				
				dup_n = 0;
			}
			last = str[i-1];
		}
	}
	if (dup_n>0) str.erase(1, dup_n);
	return str;
}

std::string& String::squeeze(std::string& str, const std::string& squeezed_str){
	return squeeze(str, squeezed_str.c_str(), squeezed_str.length());
}

std::string& String::squeeze(std::string& str, const char* squeezed_str, size_t n){
	size_t len = str.length();
	char last = str.back();
	size_t dup_n = 0;
	for(size_t i=len-1; i>0; --i){
		if (str[i-1] == last && in_chars(str[i-1], squeezed_str, n)){
			++dup_n;
		} else {
			if (dup_n>0){
				str.erase(i, dup_n);
				dup_n = 0;
			}
			last = str[i-1];
		}
	}
	if (dup_n>0) str.erase(1, dup_n);
	return str;
}

std::vector<std::string>& String::lines(const std::string& str, std::vector<std::string>& out){
	out.clear();
	size_t idx = 0;
	size_t line_len = 0;
	size_t last_idx = 0;
	while((idx = str.find('\n', idx)) != std::string::npos){
		line_len = idx < (last_idx + 1) ? 0 : (idx - last_idx - 1);
		if (idx > last_idx && str[idx-1] == '\r' && line_len > 0) --line_len;
		if (line_len > 0) out.push_back(std::string(str.c_str()+last_idx, line_len));
		last_idx = ++idx;
	}
	return out;
}

std::string& String::replace(std::string& str, const std::string& replaced, const std::string& sub){
	size_t idx = str.find(replaced);
	if (idx == std::string::npos) return str;
	return str.replace(idx, replaced.length(), sub);
}

std::string& String::greplace(std::string& str, const std::string& replaced, const std::string& sub){
	size_t idx = std::string::npos;
	while((idx = str.rfind(replaced, idx)) != std::string::npos){
		str.replace(idx, replaced.length(), sub);
	}
	return str;
}

bool String::match(const std::string& str, const std::string& regexp){
	return std::regex_match(str.c_str(), std::regex(regexp));
}

std::vector<std::string>& String::search(const std::string& str, const std::string& regexp, std::vector<std::string>& out){
	out.clear();
	std::match_results<std::string::const_iterator> mrs;
	std::string s = str;
	while (std::regex_search(s, mrs, std::regex(regexp))){
		out.push_back(mrs.str());
		s = mrs.suffix().str();		
	}
	return out;
}

std::string& String::search(const std::string& str, const std::string& regexp, std::string& out){
	out.clear();
	std::match_results<std::string::const_iterator> mrs;
    std::regex rx(regexp); 
	if (std::regex_search(str, mrs, rx)){
		out = mrs.str();
	}
	return out;
}

std::string& String::sub(std::string& str, const std::string& regexp, const std::string& fmt){
	str = std::regex_replace(str, std::regex(regexp), fmt, std::regex_constants::format_first_only);
	return str;
}

std::string& String::gsub(std::string& str, const std::string& regexp, const std::string& fmt){
	str = std::regex_replace(str, std::regex(regexp), fmt);
	return str;
}


__XNS_END_NAMESPACE
