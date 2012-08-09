
#include "xns/file.h"

using namespace std;

__XNS_BEGIN_NAMESPACE

bool File::exist(const char* file){
	ifstream ifs;
	return ifs.good();
}

std::streamsize File::get_size(const char* file){
	return 0;
}

std::string& File::read(const char* file, std::string& buffer){
	ifstream ifs;
	return string();
}

std::string& File::read(const char* file, std::string& buffer, std::streamsize size){
	return string();
}

std::vector<std::string>& File::readlines(const char* file, std::vector<std::string>& lines){
	return std::vector<std::string>();
}

std::streamsize File::write(const char* file, const std::string& s){
	return 0;
}
std::streamsize File::write(const char* file, const char* s, std::streamsize size){
	return 0;
}

__XNS_END_NAMESPACE
