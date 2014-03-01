#pragma once
#include "ShareCodeNamespace.h"
#include "ShareCodeComponent.h"

namespace Share { namespace Code {

	/*!<  */
	class Project : public DbRecordElement
	{
	public:
		Project(void);
		~Project(void);
	private:
		ElementId	m_entryFunction;
		std::vector<Component>		GetComponents();	/*!< Returns a list of projects associated with this workspace. */

		std::vector<std::shared_ptr<Assembly>>			m_loadedAssemblies;		/*!< Assemblies referenced with this project. */
	};

}; };

