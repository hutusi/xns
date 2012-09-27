
#pragma once 

#include "defs.h"
#include <string>

__XNS_BEGIN_NAMESPACE

class Path{
public:
  // copy from boost
  #ifdef WINDOWS
	typedef wchar_t value_type;
  #else
    typedef char    value_type;
  #endif
	typedef std::basic_string<value_type>  string_type;

  static const char* get_current();
  static const bool chdir(const char* new_dir);

public:
  Path();
  Path(const std::string& str);
  Path(const Path& path);
  virtual ~Path() throw();

	Path& operator=(const Path& path);
	Path& operator=(const std::string& str);	

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

bool operator==(const Path& left, const Path& right);
bool operator==(const Path& left, const std::string& right);
bool operator==(const std::string& left, const Path& right);

__XNS_END_NAMESPACE
