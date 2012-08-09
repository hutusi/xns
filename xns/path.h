
#pragma once 

#include "defs.h"
#include <string>

__XNS_BEGIN_NAMESPACE

class Path{
public:
	static const char* get_current();
	static const bool chdir(const char* new_dir);

public:
	Path();
	Path(const char* str);
	Path(const std::string& str);
	Path(const Path& path);
	virtual ~Path();

	Path& operator=(const Path& path);
	Path& operator=(const char* str);
	Path& operator=(const std::string& str);

	bool operator==(const Path& path) const;
	bool operator==(const char* str) const;
	bool operator==(const std::string& str) const;

	inline const std::string& path() const { return path_; }
	inline const std::string& directory() const { return dir_; }
	inline const std::string& name() const { return name_; }
	// inline const std::string& parent() const { return dir_; }

	bool exist();
	bool is_file();
	bool is_directory();
	bool is_absolute();
	
private:
	std::string path_;
	std::string dir_;
	std::string name_;

	void parse();
	void format();
	// void expand(); // expand system environment variables
};

__XNS_END_NAMESPACE
