/**
When an element is identified as belonging to a particular branch, it means that
whatever the branch is set to for a particular author at a particular time, they can only
modify elements which are marked as being on that branch. Attempting to modify an element
with a different branch tag will result in a copy being made and being marked as belonging to that
branch. The user can then make all the changes they want. The branch they are subscribed
to must belong to the group who manages that branch.

Interim commits in a branch, simply result in 
*/
#include "stdafx.h"
#include "ShareCodeBranch.h"

namespace Share { namespace Code {

	Branch::Branch(void)
	{
	}

	Branch::~Branch(void)
	{
	}

}; };
