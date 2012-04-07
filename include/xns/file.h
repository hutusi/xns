
#pragma once 

#include "path.h"
#include <fstream>

__XNS_BEGIN_NAMESPACE

class File{
public:
	File(const char* path);
	File(const std::string& path);
	File(const Path& path);
	File(const File& path);
	~File();

	bool exist();
	std::string& read();
	std::string& read(std::streamsize size);
	std::streamsize write(const std::string& s);
	std::streamsize write(const char* s, std::streamsize size);

	inline const std::string& path() const { return path_.path(); }
	inline const std::string& name() const { return path_.name(); }
	inline const std::string& directory() const { return path_.directory(); }

	inline const std::string& basename() const { return basename_; }
	inline const std::string& extname() const { return extname_; }

private:
	Path path_;
	std::string basename_;
	std::string extname_;
	std::string read_buf_;
};

__XNS_END_NAMESPACE
