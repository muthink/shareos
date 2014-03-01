#include "stdafx.h"
#include "ShareCodeSettings.h"

namespace Share {
	namespace Code {

		/** Represents the current state of the system: usually a singleton. */
		Settings::Settings(void)
		{
		}


		Settings::~Settings(void)
		{
		}

		std::string Settings::GetLocalDatabasePath()
		{
			return "";
		}

	}
}