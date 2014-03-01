#pragma once
#include "ShareCodeBase.h"

namespace Share { namespace Code { namespace Language {

	/** Virtual base case to define a language. */
	class Description
	{
	public:
		Description();
		~Description();
	};

	/** Controls parsed input and output. */
	class Parser
	{
	public:
		Parser();
		~Parser();
	};

	/** Block of Code */
	class CodeBlock
	{
	public:
		virtual Description					GetLanguage();	/*!< Returns the language of this block of code. */
		virtual std::vector<unsigned char>	GetRawData();	/*!< Returns the raw data of this block of code. */
	};

	/**
	The universal language forms like so.
	int a = 5;	// DeclareLocal, Assign
	*/
	namespace Universal { // Declarations for defining a universal language for ShareOS

		enum class InstructionType {
			DeclareLocal,			// Declaring a local variable
			Assign,					// Assigning a value to a variable
			If,						// If true, executes the next then statement (children are the tests)
			Then,					// Result of the last true condition (children are the statements)
			IfElse,					// If else tied to previous If
			Else,					// Final option of If Else block.
			FunctionCall,			// We are calling a function (children are the parameters being passed in)
		};

		class Instruction
		{
		public:
			std::vector<Instruction>	m_subblock;		/*!< List of instructions, forming the sub-block */
		};

		/** Declare a local variable */
		class InstructionDeclareLocal : public Instruction
		{
		public:
		};

		/** Defines an assignment instruction. */
		class InstructionAssign : public Instruction
		{
		public:
		};

		enum class UnaryOperators {
			Nothing,
			LogicalNot,			// !
			AddressOf,			// &
			OnesComplement,		// ~
			PointerDereference,	// 	*
			Unaryplus,			// + 
			IncrementPrefix,	// ++
			IncrementSuffix,	// ++
			UnaryNegation,		// -
			DecrementPrefix,	// --
			DecrementSuffix		// --
		};

		class UnaryOperation : public Instruction
		{
		public:
			LocalElementId	m_id;
			UnaryOperators	m_operator;
		};

	};


}; }; }; // Namespace Share::Code::Language

