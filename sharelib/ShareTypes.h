#pragma once
#include "stdafx.h"
#include "ShareMemory.h"

namespace Share {

	class StringArray;

	class String : public CopyOnWrite<std::string>
	{
	public:
		friend class StringArray;
		typedef std::string::iterator iterator;
		/** Construct from a string. */
		String(const char* str) : CopyOnWrite<std::string>(str) {}
		String(std::string& str) : CopyOnWrite<std::string>(str) {}
		String() : CopyOnWrite<std::string>() {}
		String& append(const char *str) { Data().append(str); return *this; }
		String& append(String& str)		{ Data().append(str.Data()); return *this; }
		String& append(char ch, size_t repeat = 1)			{ Data().append(ch, repeat); return *this; }
		auto at(int index)-> decltype(Data().at(index))	{ return Data().at(index); }
		auto at(int index) const -> decltype(Data().at(index))	{ return Data().at(index); }
		auto begin()-> decltype(Data().begin())	{ return Data().begin(); }
		auto begin() const -> decltype(Data().begin())	{ return Data().begin(); }
		auto	c_str()-> decltype(Data().c_str()) { return Data().c_str(); }
		auto	cbegin() const -> decltype(Data().cbegin())	{ return Data().cbegin(); }
		auto	cend() const ->decltype(Data().cend())		{ return Data().cend(); }
		auto	end()->decltype(Data().end())		{ return Data().end(); }
		auto	end() const ->decltype(Data().end())		{ return Data().end(); }
		auto	length() const ->decltype(Data().length())	{ return Data().length(); }
		String& replace(size_t pos, size_t len, const String& str) { Data().replace(pos, len, str.Data()); return *this; }
		String& replace(iterator i1, iterator i2, const String& str)	{ Data().replace(i1, i2, str.Data()); return *this; }
		String& replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen)	{ Data().replace(pos, len, str.Data(), subpos, sublen); return *this; }
		String& replace(size_t pos, size_t len, const char* s)	{ Data().replace(pos, len, s); return *this; }
		String& replace(size_t pos, size_t len, const char* s, size_t n)	{ Data().replace(pos, len, s, n); return *this; }
		String& replace(iterator i1, iterator i2, const char* s, size_t n)	{ Data().replace(i1, i2, s, n); return *this; }
		String& replace(size_t pos, size_t len, size_t n, char c)	{ Data().replace(pos, len, n, c); return *this; }
		String& replace(iterator i1, iterator i2, size_t n, char c)	{ Data().replace(i1, i2, n, c); return *this; }
		String	substr(size_t pos = 0, size_t len = -1) const	{ return String(Data().substr(pos, len)); }
	};

	class StringArray : public CopyOnWrite<std::vector<String>>
	{
	public:
		typedef std::vector<String>::iterator	iterator;
		StringArray() : CopyOnWrite<std::vector<String>>() {}
		StringArray(size_t i) : CopyOnWrite<std::vector<String>>(i)	{}
		auto back() -> decltype(Data().back())	{ return Data().back(); }
		auto back() const -> decltype(Data().back())	{ return Data().back(); }
		auto begin() -> decltype(Data().begin())	{ return Data().begin(); }
		auto begin() const -> decltype(Data().begin())	{ return Data().begin(); }
		auto end() -> decltype(Data().end())	{ return Data().end(); }
		auto end() const -> decltype(Data().end())	{ return Data().end(); }
		auto front() -> decltype(Data().front())	{ return Data().front(); }
		auto front() const -> decltype(Data().front())	{ return Data().front(); }
		StringArray& push_back(String& str)	{ Data().push_back(str); return *this; }
		auto operator[](int index) -> decltype(Data()[index])	{ return Data()[index]; }
		auto operator[](int index) const -> decltype(Data()[index])	{ return Data()[index]; }
		StringArray& operator +=(const String& str) { Data().push_back(str); return *this; }
	};


	/** All characters by default are UTF8 characters, single encoding. */
	union Char
	{
		char m_val;
	};

	template<typename T>
	class CopyOnWriteArray : public CopyOnWrite<std::vector<T>>
	{
	public:
		typedef typename std::vector<T>::const_iterator	const_iterator;
		typedef typename std::vector<T>::const_reference const_reference;
		typedef typename std::vector<T>::iterator	iterator;
		typedef typename std::vector<T>::reference reference;
		typedef typename std::vector<T>::size_type	size_type;
		typedef typename std::vector<T>::value_type value_type;
		CopyOnWriteArray() : CopyOnWrite<std::vector<T>>() {}
		CopyOnWriteArray(size_t i) : CopyOnWrite<std::vector<T>>(i)	{}
		void assign(size_type n, const value_type& val);
		auto at(size_type pos) ->decltype(Data().at(pos))	{ return at(pos); }
		auto at(size_type pos) const ->decltype(Data().at(pos))	{ return at(pos); }
		auto back() -> decltype(Data().back()) { return Data().back(); }
		auto back() const -> decltype(Data().back()) { return Data().back(); }
		auto begin() -> decltype(Data().begin())	{ return Data().begin();  }
		auto begin() const -> decltype(Data().begin())	{ return Data().begin(); }
		size_type capacity() const					{ return Data().capacity(); }
		const_iterator cbegin() const				{ return Data().cbegin(); }
		value_type* data()							{ return Data().data(); }
		const value_type* data() const				{ return Data().data();  }
		template <class... Args>
		iterator emplace(const_iterator position, Args&&... args)	{ return Data().emplace(args...); }
		template <class... Args>
		void emplace_back(Args&&... args)			{ Data().emplace_back(args...); }
		bool empty() const							{ return Data().empty();  }
		iterator erase(iterator position)			{ return Data().erase(position);  }
		iterator erase(iterator first, iterator last)	{ return Data().erase(first, last);  }
		auto end() -> decltype(Data().end())		{ return Data().end(); }
		auto end() const -> decltype(Data().end())	{ return Data().end(); }
		auto front() -> decltype(Data().front())	{ return Data().front(); }
		auto front() const -> decltype(Data().front())	{ return Data().front(); }
		auto push_back(value_type b) -> CopyOnWriteArray&	{ Data().push_back(b); return *this; }
		auto operator[](int index) -> decltype(Data()[index])	{ return Data()[index]; }
		auto operator[](int index) const -> decltype(Data()[index])	{ return Data()[index]; }
		auto operator +=(unsigned char b) -> CopyOnWriteArray& { Data().push_back(b); return *this; }
		auto size() const ->decltype(Data().size()) { return Data().size(); }
	};

	typedef CopyOnWriteArray<unsigned char>	ByteArray;
};

using namespace Share;
