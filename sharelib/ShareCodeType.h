/**
Each type is part of 
*/
#pragma once
#include "ShareCodeDbRecord.h"
#include <string>

namespace Share { namespace Code {

	/** Base class for defining a type */
	class Type
	{
	public:
		virtual bool		IsConst()		{ return false;  }
		virtual bool		IsEnum()		{ return false; }
		virtual bool		IsIntegral()	{ return true; }
		virtual size_t		GetSizeOf()		{ return 0;  }
		Type(void);
		~Type(void);

	};



	/** Each normal type is a database element.
	*/
	class TypeNonIntrinsic : public Type, public DbRecordElement
	{
	};

	/** Basic types */
	class TypeIntrinsic : public Type
	{

	};

	class Void : public TypeIntrinsic
	{

	};

	class Int8 : public TypeIntrinsic
	{
		size_t		GetSizeOf() override	{ return 1; }	/*!< 1 byte big */
	};

	class Enum : public TypeNonIntrinsic
	{

	};

}; };

