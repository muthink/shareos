/**
Making a change in a project with multiple contributors will result in a new branch being made.

To generate the following template function, write:
nf = new template function
add;calculates the sum of \x and \y multiplied by 2<ENTER> = Default namespace name : Description of function is optionally written here.
x y = (x + y)*2<ENTER>

the types are automatically determined.

tabs are used to continue a function

nf ; create a new template function - i will default to int type and input will be generic
strlen->i;Returns the length of an arbitrary null terminated string<ENTER>
input = for i=0 input[i]!=0 ++i

cn namespace; change namespace section
nn namespace; new namespace section

do instruction
	next instruction
	last instruction

ef function name; edit function

et type name; edit type
et ../Namespace.TypeName

nte - new type enum
ntec - new type enum class
nts - new type struct
nti - new type interface
ntc - new type class
ntd - new typedef



*/
#pragma once
#include "ShareMemory.h"
#include "ShareTypes.h"

namespace Share { namespace Code {

	union ElementId
	{
		unsigned char m_uc8[8];
	};

	class LocalElementId
	{
		unsigned short		m_id;	// Unique local id, for local functions and 
	};

	enum class PublishingStatus {
		Private,	// One author - Changes can be made freely.
		Protected,	// Group of authors - Changes cannot be made without checking and notifying the group.
		Public		// Whole world - No changes can be made. Any changes represent a new version.
	};

	enum class ElementTypes
	{
		Function,	// Operates on a type
		Data,		// Instance of Type
		Type		// 
	};

	typedef unsigned __int64 ElementVersion;

}; };


using namespace Share::Code;
