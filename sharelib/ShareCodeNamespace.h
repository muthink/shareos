#pragma once

#include "ShareCodeBase.h"
#include "ShareCodeAuthor.h"
#include "ShareCodeType.h"
#include "ShareCodeFunction.h"

namespace Share { namespace Code {

	class Assembly;
	class Function;
	class Namespace;
	class Type;

	/** A namespace contains multiple Aliases for functions, types and variables.

	*/
	class Alias
	{
	public:
		Alias();
		~Alias();
		virtual String		GetName();		/*!< Returns the alias name within this n */
		virtual Namespace&	GetNamespace();	/*!< Returns the namespace this alias is within. */
	};

	class AliasType : public Alias
	{
	public:
	};

	class AliasParameter : public Alias
	{
	public:
	};

	class AliasFunction : public Alias
	{
	private:
		std::vector<AliasParameter>	m_params;
	};

	/** Alias pointing to an internal function */
	class AliasFunctionInternal : public Alias
	{
	public:
	};

	class Namespace : public DbRecordElement
	{
	public:
		Namespace(void);
		~Namespace(void);
		std::vector<Alias>			GetAliases();			/*!< Returns a list of all the aliases in the namespace */
		Assembly&					GetAssembly();			/*!< returns a reference to the assembly for this namespace */
		std::vector<AliasFunction>	GetFunctionAliases();	/*!< Returns all the function aliases in this namespace */
		std::string					GetName();				/*!< Returns the name of this namespace */
		std::vector<AliasType>		GetTypeAliases();		/*!< Returns all the type aliases in this namespace */
	};

	/** An assembly is a collection of namespaces */
	class Assembly : public DbRecordElement
	{
	public:
		Author&					GetAuthor();		/*!< Returns the author of this assembly. */
		std::vector<Function>	GetFunctions();		/*!< Returns all the types associated with this namespace*/
		std::vector<Namespace>	GetNamespaces();	/*!< Gets all namespaces within this assembly. */
		std::string				GetPublishedName();	/*!< Returns the public name of this assembly. */
		std::vector<Type>		GetTypes();			/*!< Returns an array to the types stored in this assembly. */
	};

}; };

