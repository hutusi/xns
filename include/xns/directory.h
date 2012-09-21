
#pragma once 

#include "path.h"
#include "file.h"

#include <vector>

__XNS_BEGIN_NAMESPACE

class Directory{
public:
	Directory(const char* path);
	Directory(const std::string& path);
	Directory(const Path& path);
	Directory(const Directory& path);
	~Directory();
	
	inline const std::string& path() const { return path_.path(); }
	inline const std::string& name() const { return path_.name(); }
	inline const std::string& parent_dir() const {return path_.directory(); }

	std::vector<Directory>& folders();
	std::vector<File>& files();

	bool exist();
	Directory& parent();

	bool has(const char* str);
	bool has(const std::string& str);
	bool has(const Path& path);
	bool has(const File& file);
	bool has(const Directory& folder);

	static std::vector<std::string>& folders(const char* dir, std::vector<std::string>& out);
	static std::vector<std::string>& files(const char* dir, std::vector<std::string>& out);

	static bool include(const char* file);

private:
	Path path_;
	std::vector<Directory> folders_;
	std::vector<File> files_;
	bool searched_;

	void search(); 
};

__XNS_END_NAMESPACE
