#pragma once
#include "ShareCodeDbRecord.h"

namespace Share { namespace Code {

	/**
	Every author has a record, along with private and public keys.
	This class represents a loaded author record.
	Private key is stored on local machine.
	*/
	class Author : public DbRecord
	{
	public:
		Author(void);		/*!< Creates a new blank author record. */
		Author(ElementId);	/*!< Loads an author record with the given id. */
		~Author(void);
		String		GetEmail();
		String		GetName();
		String		GetPublicKey();
		String		SetEmail( const String&& email );
		String		SetName( const String&& name );
		String		SetPublicKey( const String&& publicKey );
	private:
		String		m_name;					/*!< Name of the author */
		String		m_email;				/*!< Email of author */
		String		m_publicKey;			/*!< Public key of author */
		ElementId		m_lastOpenedWorkspace;	/*!< Last workspace opened by author */
	};

	enum class Rights
	{
		Administrator,		/*!< Can administrate objects that belong to this group. */
		CodeContributor,	/*!< Can contribute code to objects that belong to this group. */
		CodeReader,			/*!< Can read code objects and comment on them. */
		Reporter,			/*!< Can report on function status */
		Consumer,			/*!< Can consume objects that belong to this group. */
		Information			/*!< Can view information about  this object */
	};

	/** A record exists for every author in this group who has rights to that group. */
	class AuthorWithRights
	{
	public:
		Author&	GetAuthor();
		Rights	GetRights();
	};

}; };
