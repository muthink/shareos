#pragma once
#include <memory>

namespace Share { namespace Memory {


	/**
	To create a reference type, first create a value type that stores the data.
	This value type must perform a deep copy when it copies.
	Everything in the value type will be inaccessible.
	Then derive a new type like so:
	class StringValue { define here... }
	class String : private CopyOnWrite<StringValue>
	{
	// Define public methods here.
	void print() const // A const method makes no copy, because it calls Data() const version.
	String& append() // A non-const method makes a copy if owned by more than one, because
	}
	There are two types of reference data: AlwaysShared, CopyOnWrite. Everything else is 

	*/

	/** Copy on write. Data structure T. T must have a default constructor and default copy constructor. */
	template<typename T>
	class CopyOnWrite
	{
	public:
		bool	IsNull()	{ return m_data == nullptr; }
	private:
		/** Struct of the object */
		class _PrivateBuffer : public T
		{
		public:
			/** Construct a new _PrivateBuffer with one owner. */
			template<class first, class... _valTy>
			_PrivateBuffer(first, _valTy... _Val) : T(_Val...), m_count(1) {}
			_PrivateBuffer() : T(), m_count(1) {}
			bool		hasMultipleOwners()	{ return m_count > 1; }
			size_t		m_count;	/*!< Usage count - */
		};
	protected:
		/** Create a new object. */
		template<class first, class... _valTy>
		CopyOnWrite(first, _valTy... _Val) : m_data(new _PrivateBuffer(_Val...))	{}
		CopyOnWrite() : m_data(new _PrivateBuffer()) {}
		/** */
		~CopyOnWrite()
		{
			DecRef();
		}
		/** Gets a write copy of the object */
		T&	Data()
		{
			if( m_data->hasMultipleOwners() )
			{
				DecRef();
				m_data = new _PrivateBuffer(*m_data);	// Construct with copy constructor
			}
			return *m_data;
		}
		/** */
		const T&	Data() const	{ return *m_data; }
	private:
		void	IncRef()	{ m_data->m_count++; }
		void	DecRef()
		{
			if( --m_data->m_count == 0 )
				delete m_data;
		}
		_PrivateBuffer	*m_data;
	};


}; }; // Share::Memory


using namespace Share::Memory;
