
#include "xns/path.h"
#include <xns/string.h>
#include <Windows.h>

using namespace std;

__XNS_BEGIN_NAMESPACE

#define SPLITTER '\\'

const char* Path::get_current(){
	static char* curr_path = 0;
	static DWORD len = MAX_PATH;
	if (!curr_path) { curr_path = new char[len];}

	DWORD ret = GetCurrentDirectory(len, curr_path);
	if (ret == 0) { }
	if (ret > len) {
		delete[] curr_path;
		curr_path = new char[ret];
		GetCurrentDirectory(ret, curr_path);
	}

	return curr_path;
}

const bool Path::chdir(const char* new_dir){
	return (0 != SetCurrentDirectory(new_dir));
}


Path::Path(){
}

Path::Path(const string& str){
	path_ = str;
	parse();
}

Path::Path(const Path& path) {
	path_ = path.path_;
	dir_ = path.dir_;
	name_ = path.name_;
}

Path::~Path() throw(){
}

Path& Path::operator=(const Path& path){
	path_ = path.path_;
	dir_ = path.dir_;
	name_ = path.name_;

	return *this;
}

Path& Path::operator=(const std::string& str){
	path_ = str;
	parse();

	return *this;
}

void Path::parse(){
	
}

void Path::format(){
	String::replace_all(path_, '/', SPLITTER);
}

__XNS_END_NAMESPACE
