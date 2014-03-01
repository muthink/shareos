#pragma once
#include "ShareCodeAuthor.h"

namespace Share { namespace Code {

	/** Group of authors */
	class Group
	{
	public:
		Group(void);
		~Group(void);
		/** Returns a list of authors with the rights that belong to this group */
		std::vector<AuthorWithRights>	GetAuthors();
	};

}; };
