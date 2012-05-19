
#pragma once

#include "pattern_defs.h"

interface Prototype{
public:
	virtual Prototype* clone() = 0;
};
