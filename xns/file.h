
#pragma once 

#include "path.h"
#include <fstream>
#include <vector>

__XNS_BEGIN_NAMESPACE

class File{
public:
	static bool exist(const char* file);
	static std::streamsize get_size(const char* file);

	static std::string& read(const char* file, std::string& buffer);
	static std::string& read(const char* file, std::string& buffer, std::streamsize size);
	static std::vector<std::string>& readlines(const char* file, std::vector<std::string>& lines);
	static std::streamsize write(const char* file, const std::string& s);
	static std::streamsize write(const char* file, const char* s, std::streamsize size);

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
