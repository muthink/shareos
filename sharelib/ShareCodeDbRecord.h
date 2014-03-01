#pragma once
#include "ShareCodeBase.h"
#include "sqlite3.h"

namespace Share {
	namespace Code {

		struct NameTypePair
		{
			NameTypePair() {}
			const char *m_name;			/*!< Name of the field */
			int			m_type;			/*!< Type of the field */
			size_t		m_offset;		/*!< Offset into the datastructure */
			const char*	m_columnSpec;	/*!< Create column specification */
			NameTypePair(const char *name, int type, size_t offset, const char* columnSpec) :
				m_name(name), m_type(type), m_offset(offset), m_columnSpec(columnSpec) { }
		};

		/** Any kind of database record. */
		class DbRecord
		{
		public:
			DbRecord();
			~DbRecord();
			virtual std::vector<NameTypePair>	GetNameTypePairs() = 0;	/*!< Returns the name type pairs. */
			bool	SynchronizeWithServer();					/*!< Synchronize this record with server. */
			void	Update();									/*!< Insert or update this record */
		private:
			static sqlite3	*m_sqlite;
			static int		m_refCount;
			static bool		m_isOk;
		};

		/** A database record describing an element: function, namespace, assembly, type, snippet, etc... */
		class DbRecordElement : public DbRecord
		{
			virtual std::vector<NameTypePair>	GetNameTypePairs() override;	/*!< Returns the name type pairs. */
		protected:
			ElementId			m_id;				/*!< */
			ElementVersion		m_version;			/*!< */
			ElementId			m_previousVersion;	/*!< */
			ElementId			m_branch;			/*!< */
			PublishingStatus	m_publishingStatus;	/*!< */
		};
	}
}
