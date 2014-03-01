#pragma once
#include <stdarg.h>
#include <intrin.h>

#ifdef _WIN32
#include <Windows.h>
namespace Lo {
typedef wchar_t			Char;
typedef wchar_t*		SZ;
typedef const wchar_t*	CSZ;
}
#define LoAlloc(x)		GlobalAlloc(GPTR,x);
#define LoFree(x)		GlobalFree((HGLOBAL)x);
#define LoCSZ(x)		L##x
#endif

namespace Lo {

	/** Provides a way of passing a string with length information. */
	template<typename T,int N>
	class FixedString {
	public:
		void copyFrom(const char * source)	{ for(int i = 0; i < N && source[i]; ++i)	str[i] = (T)source[i]; str[i]=0; }
		void copyFrom(const wchar_t * source)	{ for(int i = 0; i < N && source[i]; ++i)	str[i] = (T)source[i]; str[i]=0; }
		__inline operator T*()	{return str;}
		__inline size_t count()	{return N;}
		T	str[N+1];
	};

	typedef FixedString<WCHAR,MAX_PATH-1>	PathString;

class Buffer
{
public:
	static const unsigned BLOCK_SIZE = 1024;
	Buffer(unsigned initialSize = 0);
	Buffer(Buffer &buffer);
	~Buffer();
	Buffer& operator=(const Buffer &source);
	Buffer& add(unsigned char ch);
	unsigned size()	const;
	unsigned char *get();
	const unsigned char *get() const;
	static int checkAllocCount();
protected:
	struct BufferInternal {
		int m_count;				// Reference count
		unsigned m_used;			// Used portion of buffer
		unsigned m_allocSize;		// Allocated size of buffer
	};
	static int globalAllocCount;
	BufferInternal *m_buffer;
	unsigned char *getActualBuffer();
	unsigned roundup(unsigned size);
	void createBuffer(unsigned size=0);
	void decreaseRef();
	void increaseRef();
};

class String : public Buffer
{
public:
	String(String &string);
	String(unsigned initialChars = 0);
	String(const char *initialString);
	String(const wchar_t *initialString, unsigned extraChars = 0);
	String& add(wchar_t ch);
	String& add(const wchar_t * string);
	String& add(const char * string);
	void trimend(int chars);
	// Cast to a system string
	operator CSZ();
	// Assignment
	String& operator=(const char *newString);
	/** Returns true if the string is empty. */
	bool		isEmpty();
	/** Returns the length of the string */
	unsigned	length();
	/** Returns the used size of the string in characters */
	unsigned	size();
	/** Returns a pointer to the buffer */
	SZ			get();
	/** Fixes up the used part after a function call */
	void		fix();
private:
	bool		isNull;
};


/**
\subpage Tracing Tracing
Traces contain different levels of error, Severe errors are reported to server.
Everything else depends upon the presence of the pipe server.
Any functions using tracing must have self-cleaning objects only.

Traces are sent to the pipes if the pipes are attached. Traces look like the following:
?P######§T#####§O#####§MMODULE.EEE§SData °(SYSERR:#######)§

Traces can contain many different fields, separated by §.

The first character indicates the level: %=FATAL, !=ERROR, &=WARNING, ?=Verbose
P - The Hex number after this is the process id
T - The Hex number after this is the thread id
O - The Hex number after this is the RVA from where the trace was sent
M - The Module from where the trace was sent
S - An additional information string sent in the trace
°() - Indicates a particular error string id is included from the given module SYSERR
*/

/** The different trace levels */
enum TraceLevel{
	Severe = 0,	/** The module has an unexpected error that must be reported. */
	Error = 1,	/** The function has an error - unclear if recoverable or not */
	Warning = 2,/** A warning - a recoverable error has occurred */
	Verbose = 3	/** Extra information that might be useful is emitted */
};

class Trace;

/** Function for building tracer strings. */
class TString
{
public:
	friend class Trace;
	TString(const char *header = nullptr);
	TString& Append(const char *val);
	TString& Value(const char *name,void *address);
	/** Quick function to report an integer without adding a newline.*/
	TString& Value(const char *name, int val);
	/** Quick function to report a string without adding a newline.*/
	TString& Value(const char *name, const char *val);
	/** Quick function to report a string without adding a newline.*/
	TString& Value(const char *name, const wchar_t *val);
	const char	*GetStr() const	{ return (const char*)m_str; }
	int			GetLength() const	{ return m_length; }
private:
	void		AppendLine(const char *val);
	char		m_str[256];
	int			m_length;
};

/** Function for tracing. */
class Trace
{
public:
	/** Version of constructor with optional string */
	Trace(const char *functionName, const TString& tstring, bool isVoidReturn = false);
	Trace(const char *functionName = nullptr, bool isVoidReturn = false);
	/** The destructor is where the leave function is registered */
	~Trace();
	/** Output with escalation to error level */
	void LogError(const char *msg = nullptr);
	void LogError(const TString &tstring)	{ LogError(tstring.GetStr()); }
	/** Escalates to severe error, but does not report until destructor */
	void LogSevere(const char *msg = nullptr);
	/** Verbose information output - does not escalate */
	void LogVerbose(const char *msg = nullptr);
	void LogVerbose(const TString &tstring)	{ LogVerbose(tstring.GetStr()); }
	/** Escalates function to warning level, appending the msg. */
	void LogWarning(const char *msg = nullptr);
	void LogWarning( const TString &tstring )	{ LogWarning(tstring.GetStr()); }
	template<typename Ty>
	__inline Ty ReturnSuccess(Ty retval)
	{
		m_returnSet = true;
		Leave(m_level);
		return retval;
	}
	template<typename Ty>
	__inline Ty ReturnError(Ty retval, const char *msg = nullptr)
	{
		m_returnSet = true;
		LogError(msg);
		Leave(Error);
		return retval;
	}
	template<typename T>
	__inline T ReturnSevere(T retval, const char *msg = nullptr)
	{
		m_returnSet = true;
		LogSevere(msg);
		Leave(Severe);
		return retval;
	}
	template<typename T>
	__inline T Return(T retval, T success )
	{
		return (retval == success) ? ReturnSuccess(success) : ReturnError(retval);
	}
private:
	/** Appends the internal string. */
	Trace &Append(const char *s);
	/** The function is being exited in a controlled manner. */
	void Leave(TraceLevel level);
	/** Initializes the trace routines */
	static bool Init();
	/** Print the entry parameters */
	void PrintEntry(const TString& extra);
	static bool			traceIsDisabled;	/// Quick value to determine if trace is disabled or not
	static TraceLevel	traceLevel;			/// Which trace level is activated
	// 
	TraceLevel	m_level;
	bool		m_returnSet;
	const char	*m_functionName;
	char		m_str[1024];				/// 1024 bytes is the maximum that can be reported in one function.
	int			m_length;
};

#define TraceEnterParams(s,...)		_t(__FUNCTION__ s,__VA_ARGS__)
#define TraceEnter()				_t(__FUNCTION__)
#define TraceEnterVoid()			_t(true,__FUNCTION__)
#define TraceEnterVoidParams(s,...)	_t(true,__FUNCTION__ s, __VA_ARGS__)
#define TraceInt(n,d)				_t.LogInt(n,d)
#define TraceLine()					_t.LogVerbose(Lo::TString().Value("line",__LINE__))
#define TraceString(n,s)			_t.LogString(n,s);
#define TraceReturnSuccess(t,val)	return _t.ReturnSuccess<t>(val)
#define TraceReturnError(t,val)		return _t.ReturnError<t>(val)
#define TraceVerbose(s,...)			_t.LogVerbose(s,__VAR_ARGS__)
#define TraceValue(s)				Value(#s,s)


/**
Gets the Unix linker time of the current module.
*/
unsigned GetLinkerTime();

/**
Gets the latest version of this file online
\retval unsigned 0 means it could not get the latest version, any other number is valid.
*/
unsigned GetLatestVersion();

/** Performs an HTTP get with the given url and extra parameters */
Buffer HttpGet(CSZ url,int numberOfParameters=0, CSZ *keys=nullptr, CSZ *values=nullptr);

#ifdef _WIN32
/**
Returns the base address of the given module.
\note for Windows only
*/
PIMAGE_DOS_HEADER GetModuleBaseAddress(HMODULE hModule);
#endif

class ModuleInfo
{
public:
	ModuleInfo(LPCWSTR fileName);
	ModuleInfo(HMODULE hModule) : m_baseAddress(GetModuleBaseAddress(hModule)) {}
	~ModuleInfo()	{}
	PIMAGE_DOS_HEADER GetBaseAddress();
	unsigned GetLinkerTime()	{ return Lo::GetLinkerTime(); }	// Fix this.
private:
	PIMAGE_DOS_HEADER	m_baseAddress;
};

/** Portable versioning */
union Version
{
public:
	Version() : m_version(0)	{  }
	Version(unsigned __int64 version) : m_version(version) {}
	Version(unsigned int high32, unsigned int low32 ) : 
		m_version( ((unsigned __int64)high32 << 32) | ((unsigned __int64)low32) ) {}
	Version(unsigned short major, unsigned short minor = 0, unsigned short build = 0, unsigned short revision = 0) :
		m_version( ((unsigned __int64)major << 48) | ((unsigned __int64)minor << 32)
					| ((unsigned __int64)build << 16) | ((unsigned __int64)revision))	{ }
	__inline operator unsigned __int64()	{ return m_version; }
	Version&	operator=(unsigned __int64 version)	{ m_version = version; return *this; }
	__declspec(property(get=get_Major))	unsigned short Major;
	unsigned short get_Major()	{ return (unsigned short)(m_version>>48); }
	__declspec(property(get=get_Minor))	unsigned short Minor;
	unsigned short get_Minor()	{ return (unsigned short)(m_version>>32); }
	__declspec(property(get=get_Build))	unsigned short Build;
	unsigned short get_Build()	{ return (unsigned short)(m_version>>16); }
	__declspec(property(get=get_Revision))	unsigned short Revision;
	unsigned short get_Revision()	{ return (unsigned short)(m_version); }
private:
	unsigned __int64	m_version;
};

void ReportLastError(CSZ optionalString);

}

