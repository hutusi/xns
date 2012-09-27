
// Copyright (c) 2012, John Hu 

#pragma once

#include "defs.h"
#include "char.h"

#include <string>
#include <vector>

#include <regex>

__XNS_BEGIN_NAMESPACE

namespace String{
	// usage: string s("s");
	//        cout<<s*5;
	std::string operator*(const std::string& str, size_t times);
	
	// split a string by a splitter character
	// 
	std::vector<std::string>& split(const char* str, size_t len, const char* splitter, size_t sp_len, __OUT std::vector<std::string>& out);
	
	inline std::vector<std::string>& split(const char* str, size_t len, char splitter, std::vector<std::string>& out){
		char sp[] = {splitter,'\0'};
		return split(str, len, sp, 1, out);
	}

	inline std::vector<std::string>& split(const std::string& str, char splitter, std::vector<std::string>& out){
		return split(str.c_str(), str.length(), splitter, out);
	}

	inline std::vector<std::string>& split(const std::string& str, const std::string& splitter, std::vector<std::string>& out){
		return split(str.c_str(), str.length(), splitter.c_str(), splitter.length(), out);
	}
	
	//trim
	std::string& ltrim(std::string& str, const char* trim_chars, size_t n);

	inline std::string& ltrim(std::string& str, const std::string& trim_chars){
		return ltrim(str, trim_chars.c_str(), trim_chars.length());
	}

	inline std::string& ltrim(std::string& str){
		return ltrim(str, " \t\n\r", 4);
	}
		
	std::string& rtrim(std::string& str, const char* trim_chars, size_t n);

	inline std::string& rtrim(std::string& str, const std::string& trim_chars){
		return rtrim(str, trim_chars.c_str(), trim_chars.length());
	}

	inline std::string& rtrim(std::string& str){
		return rtrim(str, " \t\n\r", 4);
	}	

	inline std::string& trim(std::string& str){
		return ltrim(rtrim(str));
	}
	inline std::string& trim(std::string& str, const std::string& trim_chars){
		return ltrim(rtrim(str, trim_chars.c_str(), trim_chars.length()), trim_chars.c_str(), trim_chars.length());
	}
	inline std::string& trim(std::string& str, const char* trim_chars, size_t n){
		return ltrim(rtrim(str, trim_chars, n), trim_chars, n);
	}

	inline std::string& capitalize(std::string& str){
		if (str.length() > 0 && Char::is_lowercase(str[0])) {
			str.replace(0, 1, 1, (str[0] - 32));
		}
		return str;
	}

	std::string& downcase(std::string& str);

	std::string& upcase(std::string& str);

	std::string& swapcase(std::string& str);
	
	// case compare
	int casecmp(const char* x, size_t x_len, const char* y, size_t y_len);

	inline int casecmp(const std::string& x, const std::string& y){
		return casecmp(x.c_str(), x.length(), y.c_str(), y.length());
	}

	std::string& reverse(std::string& str);

	std::string& squeeze(std::string& str);

	std::string& squeeze(std::string& str, const char* squeezed_str, size_t n);

	inline std::string& squeeze(std::string& str, const std::string& squeezed_str){
		return squeeze(str, squeezed_str.c_str(), squeezed_str.length());
	}
	
	std::vector<std::string>& lines(const std::string& str, std::vector<std::string>& out);

	inline bool include(const std::string& str, const std::string& sub){
		return (str.find(sub) != std::string::npos);
	}
	inline bool include(const std::string& str, const char* sub){
		return (str.find(sub) != std::string::npos);
	}
	inline bool include(const std::string& str, const char* sub, size_t len){
		return (str.find(sub, len) != std::string::npos);
	}

	inline std::string& replace(std::string& str, const std::string& replaced, const std::string& sub){
		size_t idx = str.find(replaced);
		if (idx == std::string::npos) return str;
		return str.replace(idx, replaced.length(), sub);
	}

	inline std::string& replace(std::string& str, char replaced, char sub){
		size_t idx = str.find(replaced);
		if (idx == std::string::npos) return str;
		return str.replace(idx, 1, 1, sub);
	}

	std::string& replace_all(std::string& str, const std::string& replaced, const std::string& sub);

	std::string& replace_all(std::string& str, char replaced, char sub);
		
	/*inline bool match(const std::string& str, const std::string& regexp){
		return std::regex_match(str.c_str(), std::regex(regexp));
	}

	inline std::vector<std::string>& search(const std::string& str, const std::string& regexp, std::vector<std::string>& out){
		out.clear();
		std::match_results<std::string::const_iterator> mrs;
		std::string s = str;
		while (std::regex_search(s, mrs, std::regex(regexp))){
			out.push_back(mrs.str());
			s = mrs.suffix().str();		
		}
		return out;
	}

	inline std::string& search(const std::string& str, const std::string& regexp, std::string& out){
		out.clear();
		std::match_results<std::string::const_iterator> mrs;
		std::regex rx(regexp); 
		if (std::regex_search(str, mrs, rx)){
			out = mrs.str();
		}
		return out;
	}

	static std::string& sub(std::string& str, const std::string& regexp, const std::string& fmt){
		if (has_catch(fmt)){
			std::cmatch mrs;
			if (std::regex_search(str.c_str(), str.c_str()+ str.length(), mrs, std::regex(regexp))){
				std::string s;
				str = mrs.prefix().str();
				std::string suf = mrs.suffix().str();
				str += sub_catch(mrs, fmt, s);
				str += suf;		
			} 
		} else {
			str = std::regex_replace(str, std::regex(regexp), fmt, std::regex_constants::format_first_only);
		}
	
		return str;
	}

	static std::string& gsub(std::string& str, const std::string& regexp, const std::string& fmt){
		if (has_catch(fmt)){
			std::cmatch mrs;
			std::regex rx(regexp);
			std::string suf = str;
			str.clear();
			while (std::regex_search(suf.c_str(), suf.c_str()+ suf.length(), mrs, rx, std::regex_constants::format_first_only)){
				std::string s;
				str += mrs.prefix();
				suf = mrs.suffix();
				str += sub_catch(mrs, fmt, s);
			}
			str += suf;
		} else {
			str = std::regex_replace(str, std::regex(regexp), fmt);
		}

		return str;
	}*/
		
}

__XNS_END_NAMESPACE
