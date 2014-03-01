#pragma once
#include <vector>
#include "ShareCodeParameter.h"

namespace Share { namespace Code {

	// An interface is a method of accessing a function.
	// Parameters are a form of interface, where copies of variables
	// Are passed into the function.
	class Interface
	{
	public:
		Interface(void);
		~Interface(void);
	};

	/** A text command can be of any form, which takes a specific string. */
	class ShareCodeTextCommand : public Interface
	{
	public:
		virtual	const char *GetDefaultString() = 0;
	};

}; };
