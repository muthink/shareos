#pragma once
#include "ShareCodeDbRecord.h"

namespace Share { namespace Code {

	/** A version of a code element can be tagged with a branch code. */
	class Branch : public DbRecord
	{
	public:
		Branch(void);
		~Branch(void);
		std::string		m_name;
	};

}; };
