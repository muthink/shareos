#include "stdafx.h"
#include "ShareCodeDbRecord.h"
#include "ShareCodeSettings.h"
#include "sqlite3.h"

namespace Share {
	namespace Code {

		int DbRecord::m_refCount = 0;
		sqlite3	* DbRecord::m_sqlite = nullptr;
		bool DbRecord::m_isOk = false;

		DbRecord::DbRecord()
		{
			if (m_refCount++ == 0)
				m_isOk = sqlite3_open(Settings().GetLocalDatabasePath().c_str(), &m_sqlite) == 0;
		}

		DbRecord::~DbRecord()
		{
			if (--m_refCount == 0)
			{
				sqlite3_close(m_sqlite);
				m_sqlite = nullptr;
			}
		}


		std::vector<NameTypePair> DbRecordElement::GetNameTypePairs()
		{
			std::vector<NameTypePair>	columns(5);
			columns.emplace_back("id", SQLITE_INTEGER, offsetof(DbRecordElement, m_id), "INTEGER PRIMARY KEY ASC");
			columns.emplace_back("id", SQLITE_INTEGER, offsetof(DbRecordElement, m_version), "INTEGER");
			columns.emplace_back("id", SQLITE_INTEGER, offsetof(DbRecordElement, m_previousVersion), "INTEGER");
			columns.emplace_back("id", SQLITE_INTEGER, offsetof(DbRecordElement, m_branch), "INTEGER");
			columns.emplace_back("id", SQLITE_INTEGER, offsetof(DbRecordElement, m_publishingStatus), "INTEGER");
			return columns;
		}

	}
}