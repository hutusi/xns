
// Copyright (c) 2012, John Hu 

#pragma once

#include "defs.h"
#include <string>
#include <vector>
#include <map>

__XNS_BEGIN_NAMESPACE

class IniFile{
public:
	IniFile(const char* file);

	static std::vector<std::string>& get_categories(const char* file, std::vector<std::string>& out);
	static std::vector<std::string>& get_keys(const char* file,  const char* category, std::vector<std::string>& out);
	static std::string& get_value(const char* file, const char* category, const char* key, std::string& out);

	std::vector<std::string>& get_categories();
	std::vector<std::string>& get_keys(const char* category);
	std::string& get_value(const char* category, const char* key);
private:
	std::string filename_;
	std::map<std::string, std::map<std::string, std::string>> content_;
};

__XNS_END_NAMESPACE
