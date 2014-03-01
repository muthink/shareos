#pragma once
#include "ShareCodeBase.h"
#include "ShareCodeDbRecord.h"

namespace Share { namespace Code {

	/** A collection of components goes into one workspace */
	class Component : public DbRecordElement
	{
	public:
		Component();				/*!< Create a new blank workspace */
		Component(ElementId);		/*!< Loads a record with the given ID */
		~Component(void);
	};

}; };

