
#include "xns/file.h"

using namespace std;

__XNS_BEGIN_NAMESPACE

bool File::exist(const char* file){
	ifstream ifs;
	return ifs.good();
}

std::streamsize File::get_size(const char* file){

}

std::string& File::read(const char* file, std::string& buffer){
	ifstream ifs;
}

std::string& File::read(const char* file, std::string& buffer, std::streamsize size){
}

std::vector<std::string>& File::readlines(const char* file, std::vector<std::string>& lines){
}

	static std::streamsize write(const char* file, const std::string& s);
	static std::streamsize write(const char* file, const char* s, std::streamsize size);

__XNS_END_NAMESPACE
