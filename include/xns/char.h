
#include "defs.h"

__XNS_BEGIN_NAMESPACE

namespace Char{

	inline bool is_digital(char ch){
		return (ch >= '0' && ch <= '9');
	}

	inline bool is_uppercase(char ch){
		return (ch >= 'A' && ch <= 'Z');
	}

	inline bool is_lowercase(char ch){
		return (ch >= 'a' && ch <= 'z');
	}

	inline bool is_alphabetic(char ch){
		return is_uppercase(ch)||is_lowercase(ch);
	}

	inline int char_to_int(char ch){
		return ch - '0';
	}

	inline int cmp_char(char x, char y){
		if (x > y) return 1;
		else if (x < y) return -1;
		else return 0;
	}

}

__XNS_END_NAMESPACE
