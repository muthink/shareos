#pragma once
#include "ShareCodeDbRecord.h"
#include "ShareCodeType.h"
namespace Share { namespace Code {

	/** Represents the type of value. */
	class Parameter : public DbRecordElement
	{
	public:
		Parameter(void);
		~Parameter(void);
	};

} };

