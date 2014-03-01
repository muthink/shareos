#include "stdafx.h"
#include "ShareCodeFunction.h"

namespace Share { namespace Code {

	std::vector<Parameter>	FunctionBase::GetParameters()
	{
		return std::vector<Parameter>();	// No parameters are the default.
	}

	Share::Code::Type FunctionBase::GetReturnType()
	{
		return Void();
	}

	Function::Function(void)
	{
	}


	Function::~Function(void)
	{
	}

}; };
