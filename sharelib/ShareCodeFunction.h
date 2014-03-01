#pragma once

#include "ShareCodeParameter.h"
#include "ShareCodeLanguage.h"
#include "ShareCodeInterface.h"

namespace Share { namespace Code {

	class Argument
	{
	public:
		Parameter&	GetParameterDefinition();	/*!<  */
	};

	/** Base class for defining a function */
	class FunctionBase
	{
	public:
		virtual std::vector<Parameter>	GetParameters();
		virtual Type					GetReturnType();
	};

	/** Virtual Base class for defining a function whose definition resides in the code */
	class FunctionInternal : public FunctionBase
	{
	public:
		typedef std::vector<Argument>	Arguments;
		virtual bool		Run( Arguments& arguments ) = 0;	/*!< Executes an internal function */
		virtual const char*	GetDefaultCommand() = 0;
		virtual String		GetHelp() = 0;
	};

	/** Function from FunctionBase */
	class Function : public FunctionBase, public DbRecordElement
	{
	public:
		Function();
		~Function();		
		Language::CodeBlock		GetCodeBlock();		/*!< Returns a code block for a function. */
		std::string				GetDescription();	/*!< Gets a description in the preferred language. */
		void					SetCodeBlock( const Language::CodeBlock& codeBlock );	/*!< Sets a code block */
	};

}; };
