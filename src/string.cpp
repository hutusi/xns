
#include "xns/string.h"

__XNS_BEGIN_NAMESPACE

namespace String{

static bool in_chars(char ch, const char* chars, size_t n){
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
		if (!in_chars(*(str + i - 1), trim_chars, n)) break;
	}

	return (len - i);
}

static bool has_catch(const std::string& fmt){
	size_t len = fmt.length();
	for(size_t i = 0; i < len-1; ++i){
		if(fmt[i] == '\\' && Char::is_digital(fmt[i+1])) return true;
	}
	return false;
}

static std::string& sub_catch(std::cmatch& mrs, const std::string& fmt, std::string& out){
	out.clear();
	size_t len = fmt.length();
	size_t i=0;

	for(i=0; i<len-1; ++i){
		if (fmt[i] == '\\' && Char::is_digital(fmt[i+1])){
			out += mrs[Char::char_to_int(fmt[i+1])].str();
			++i;
		} else {
			out += fmt[i];
		}
	}

	if(i<len) out += fmt[i];
	return out;
}

std::string operator*(const std::string& str, size_t times){
	std::string s;
	for (size_t i=0; i<times; ++i){
		s += str;
	}
	return s;
}

std::vector<std::string>& split(const char* str, size_t len, const char* splitter, size_t sp_len, std::vector<std::string>& out){
	out.clear();
	if (len == 0 || sp_len == 0) return out;

	const char* pos = str;
	size_t s_len = 0;

	for (size_t i = 0; i < len; ++i){
		if ((len - i >= sp_len) && (strncmp(pos+s_len, splitter, sp_len) == 0)) {
			if (s_len > 0) out.push_back(std::string(pos, s_len));
			pos = str+i+sp_len;
			i += sp_len -1;
			s_len = 0;
		} else {
			++s_len;
		}
	}

	if (s_len > 0) out.push_back(std::string(pos, s_len));
	return out;
}

std::string& ltrim(std::string& str, const char* trim_chars, size_t n){
	size_t trim_len = ltrim_len(str.c_str(), str.length(), trim_chars, n);
	if (trim_len > 0) str.erase(0, trim_len);
	return str;
}

std::string& rtrim(std::string& str, const char* trim_chars, size_t n){
	size_t len = str.length();
	size_t trim_len = rtrim_len(str.c_str(), len, trim_chars, n);
	if (trim_len > 0) str.erase(len - trim_len, trim_len);
	return str;
}

std::string& downcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(Char::is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
	}
	return str;
}

std::string& upcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(Char::is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
	}
	return str;
}

std::string& swapcase(std::string& str){
	size_t len = str.length();
	for (size_t i = 0; i < len; ++i){
		if(Char::is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
		else if(Char::is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
	}
	return str;
}

int casecmp(const char* x, size_t x_len, const char* y, size_t y_len){
	size_t len = x_len > y_len ? y_len : x_len;
	int r = 0;
	for (size_t i = 0; i < len ; ++i){
		if (Char::is_uppercase(x[i]) && Char::is_lowercase(y[i])) r = Char::cmp_char(x[i]+32, y[i]);
		else if (Char::is_lowercase(x[i]) && Char::is_uppercase(y[i])) r = Char::cmp_char(x[i], y[i]+32);
		else r = Char::cmp_char(x[i], y[i]);
		if (r != 0) return r;
	}
	return Char::cmp_char(x_len, y_len);
}

inline std::string& reverse(std::string& str){
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

std::string& squeeze(std::string& str){
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

std::string& squeeze(std::string& str, const char* squeezed_str, size_t n){
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

std::vector<std::string>& lines(const std::string& str, std::vector<std::string>& out){
	out.clear();
	size_t idx = 0;
	size_t line_len = 0;
	size_t last_idx = 0;
	while((idx = str.find('\n', idx)) != std::string::npos){
		line_len = idx < (last_idx + 1) ? 0 : (idx - last_idx);
		if (idx > last_idx && str[idx-1] == '\r' && line_len > 0) --line_len;
		if (line_len > 0) out.push_back(std::string(str.c_str()+last_idx, line_len));
		last_idx = ++idx;
	}

	if (last_idx < str.size()){
		out.push_back(std::string(str.c_str()+last_idx, str.size() - last_idx));
	}
	return out;
}

std::string& replace_all(std::string& str, const std::string& replaced, const std::string& sub){
	size_t idx = std::string::npos;
	while((idx = str.rfind(replaced, idx)) != std::string::npos){
		str.replace(idx, replaced.length(), sub);
	}
	return str;
}

std::string& replace_all(std::string& str, char replaced, char sub){
	size_t idx = std::string::npos;
	while((idx = str.rfind(replaced, idx)) != std::string::npos){
		str.replace(idx, 1, 1, sub);
	}
	return str;
}

}

__XNS_END_NAMESPACE
