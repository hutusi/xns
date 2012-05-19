
#pragma once

#include "command.h"
#include "factory_template.h"

typedef Factory<Command> CommandFactory;

#define REGISTER_COMMAND_CATEGORY(PRODUCT_CLASS, CATEGORY_TYPE) \
	REGISTER_PRODUCT_CATEGORY(Command, PRODUCT_CLASS, CATEGORY_TYPE)
#define DEFINE_COMMAND_MAKER(PRODUCT_CLASS) \
	DEFINE_PRODUCT_MAKER(Command, PRODUCT_CLASS)

/// usage:
/// 
/*
	class ACommand : public Command{
	public:
		DEFINE_COMMAND_MAKER(ACommand)
	};

	REGISTER_COMMAND_CATEGORY(ACommand, 1)
*/
