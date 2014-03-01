#pragma once
#include "ShareCodeAuthor.h"
#include "ShareCodeFunction.h"
#include "ShareCodeNamespace.h"
#include "ShareCodeComponent.h"
#include <map>

namespace Share { namespace Code {

	/*!< Local settings are global in nature and only one has to be loaded at any one time. */
	class Settings
	{
	private:
		std::string												m_localDatabasePath;	/*!< Local database file. */
		std::vector<std::shared_ptr<Namespace>>					m_commandNamespaces;	/*!< Active namespaces for running on the command line */
		std::vector<std::shared_ptr<FunctionInternal>>			m_internalFunctions;	/*!< */
		std::shared_ptr<Component>								m_workspace;			/*!< Active namespace */
		std::map<ElementId, std::shared_ptr<DbRecordElement>>	m_elements;			/*!< All cached DB elements, referenced by ElementId */
	public:
		Settings(void);
		~Settings(void);
		std::shared_ptr<Author>									GetDefaultAuthor();
		std::string												GetLocalDatabasePath();		/*!< Path to local database. */
		void													SetLocalDatabasePath(const std::string& path );
		std::vector<std::shared_ptr<FunctionInternal>>&			GetInternalFunctions()		{ return m_internalFunctions; }
		auto	LoadAuthor(long long elementId) -> bool;
		std::shared_ptr<Namespace>								GetNamespace(long long elementId);
		std::shared_ptr<Function>								GetFunction(long long elementId);
		std::shared_ptr<Type>									GetType(long long elementId);
	};

} }
