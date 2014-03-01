/**
LoWinLib wraps Windows API functions
*/
#pragma once
#include "LoLib.h"
#include <wininet.h>

namespace Lo {

	class Hinternet
	{
	public:
		Hinternet(HINTERNET hinternet=NULL) : m_hinternet(hinternet) {}
		__inline ~Hinternet()	{ if(m_hinternet!=NULL)	InternetCloseHandle(m_hinternet); }
		operator HINTERNET()	{ return m_hinternet; }
	private:
		HINTERNET m_hinternet;
	};

	class HandleZero
	{
	public:
		HandleZero(HANDLE handle=NULL) : m_handle(handle) {}
		__inline ~HandleZero()	{ if(m_handle!=NULL)	CloseHandle(m_handle); }
		operator HANDLE()	{ return m_handle; }
		operator HANDLE *()	{ return &m_handle; }
		__inline bool isInvalid()	{return m_handle == NULL;}
	private:
		HANDLE m_handle;
	};

	class HandleNegativeOne
	{
	public:
		HandleNegativeOne(HANDLE val = INVALID_HANDLE_VALUE) : m_handle(val) {}
		__inline ~HandleNegativeOne()	{ if(m_handle!=INVALID_HANDLE_VALUE)	CloseHandle(m_handle); }
		HandleNegativeOne& operator=(HANDLE	hHandle)
		{
			Close();
			m_handle = hHandle;
			return *this;
		}
		bool				isInvalid() { return m_handle==INVALID_HANDLE_VALUE; }
		void Close()		{ if(m_handle!=INVALID_HANDLE_VALUE)	{	CloseHandle(m_handle); m_handle = INVALID_HANDLE_VALUE; } }
		operator HANDLE()	{ return m_handle; }
		operator HANDLE *()	{ return &m_handle; }
	private:
		HANDLE m_handle;
	};

	class PrinterHandle
	{
	public:
		PrinterHandle() : m_handle(NULL), m_owner(true) {}
		PrinterHandle(PrinterHandle &source) : m_handle(source.m_handle), m_owner(true)
		{
			source.m_owner = false;
		}
		__inline ~PrinterHandle()	{ Close(); }
		PrinterHandle& operator=(PrinterHandle &source)
		{
			Close();
			source.m_owner = false;
			m_owner = true;
			m_handle = source.m_handle;
			return *this;
		}
		operator HANDLE()			{ return m_handle; }
		operator HANDLE *()			{ Close(); return &m_handle; }
		void	Close()
		{
			if( m_owner && !isInvalid())
			{
				ClosePrinter(m_handle);
				m_handle = NULL;
			}
		}
		__inline bool isInvalid()	{return m_handle == NULL;}
	private:
		HANDLE	m_handle;
		bool	m_owner;
	};


	class RegistryKey
	{
	public:
		RegistryKey() : m_handle(NULL) {}
		__inline ~RegistryKey()	{ Close(); }
		void Close()	{ if(!isInvalid()) {	RegCloseKey(m_handle); m_handle=NULL; } }
		operator HKEY()	{ return m_handle; }
		operator HKEY *()	{ return &m_handle; }
		__inline bool isInvalid()	{return m_handle == NULL;}
	private:
		HKEY m_handle;
	};

	class WindowsApi
	{
	public:
		static Buffer	getPrinter(HANDLE hPrinter, int level);
		static Buffer	enumPrinterDrivers(int level, DWORD& number, LPWSTR serverName=NULL);
	};

#define PROPERTY(t,n)	t get_##n () const { return m_info->##n ;} \
	__declspec(property(get = get_##n )) t n;

#define PROPERTYGETSET(t,n)	t get_##n () const { return m_info->##n ;} \
	void put_##n (t val) { m_info->##n = val; } \
	__declspec(property(get = get_##n, put = put_##n )) t n;

	class PrinterHelper
	{
	public:
		PrinterHelper(HANDLE hPrinter);
		~PrinterHelper();
		void setPrinter();
		PROPERTY(LPWSTR,pServerName);
		PROPERTY(LPWSTR,pPrinterName);
		PROPERTY(LPWSTR,pShareName);
		PROPERTY(LPWSTR,pPortName);
		PROPERTY(LPWSTR,pDriverName);
		PROPERTY(LPWSTR,pComment);
		PROPERTY(LPWSTR,pLocation);
		PROPERTYGETSET(LPDEVMODE, pDevMode);
		PROPERTY(LPWSTR,pSepFile);
		PROPERTY(LPWSTR,pPrintProcessor);
		PROPERTY(LPWSTR,pDatatype);
		PROPERTY(LPWSTR,pParameters);
		PROPERTY(PSECURITY_DESCRIPTOR,pSecurityDescriptor);
		PROPERTY(DWORD,Attributes);
		PROPERTY(DWORD,Priority);
		PROPERTY(DWORD,DefaultPriority);
		PROPERTY(DWORD,StartTime);
		PROPERTY(DWORD,UntilTime);
		PROPERTY(DWORD,Status);
		PROPERTY(DWORD,cJobs);
		PROPERTY(DWORD,AveragePPM);
	protected:
		PPRINTER_INFO_2W	m_info;
	};

	/**
	Gets version information from the executable.
	\note There is a bug in Version.dll, which appears as a memory leak. Therefore free this VersionInfo soon.
	*/
	class VersionInfo {
	public:
		VersionInfo(CSZ path = nullptr);
		~VersionInfo();
		/**
		Finds the version info string within the resources of this executable file.
		\retval bool True if it was found.
		*/
		SZ	GetString(const char * key);
		__declspec(property(get=GetFileVersion))	Version FileVersion;
		Version	GetFileVersion();
		__declspec(property(get=GetProductVersion))	Version ProductVersion;
		Version	GetProductVersion();
		DWORD	GetFileOS();
		enum FileType {
						INVALID = 0,				// Data not loaded
						APP = 0x00000001L,			// The file contains an application.
						DLL = 0x00000002L,			// The file contains a DLL.
						DRV = 0x00000003L,			// The file contains a device driver. If dwFileType is VFT_DRV, dwFileSubtype contains a more specific description of the driver.
						FONT = 0x00000004L,			// The file contains a font. If dwFileType is VFT_FONT, dwFileSubtype contains a more specific description of the font file.
						STATIC_LIB = 0x00000007L,	// The file contains a static-link library.
						UNKNOWN = 0x00000000L,		// The file type is unknown to the system.
						VXD = 0x00000005L };
		enum FileSubType {
			DRV_COMM = 0x0000000AL,			// The file contains a communications driver.
			DRV_DISPLAY = 0x00000004L,			// The file contains a display driver.
			DRV_INSTALLABLE = 0x00000008L,		// The file contains an installable driver.
			DRV_KEYBOARD = 0x00000002L,		// The file contains a keyboard driver.
			DRV_LANGUAGE = 0x00000003L,		// The file contains a language driver.
			DRV_MOUSE = 0x00000005L,			// The file contains a mouse driver.
			DRV_NETWORK = 0x00000006L,			// The file contains a network driver.
			DRV_PRINTER = 0x00000001L,			// The file contains a printer driver.
			DRV_SOUND = 0x00000009L,			// The file contains a sound driver.
			DRV_SYSTEM = 0x00000007L,			// The file contains a system driver.
			DRV_VERSIONED_PRINTER = 0x0000000CL, // The file contains a versioned printer driver.
			DRV_UNKNOWN = 0x00000000L
		};
		FileType	GetFileType();
		FileSubType GetFileSubType();
		unsigned __int64	GetFileDate();
		static	bool SelfTest();
	private:
		typedef BOOL (APIENTRY *PVerQueryValueW)( LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID * lplpBuffer, PUINT puLen );
		PVerQueryValueW		pVerQueryValue;
		unsigned char *	m_buffer;
		void * m_fixed;
		HMODULE	m_hModule;
	};

	struct LoPrinterInstallPrivate;

	/**
	Class to install printer driver.
	*/
	class LoPrinterInstaller
	{
	public:
		/** Installs a printer driver. If it is a 64 bit driver, then set is64Bit to true. */
		LoPrinterInstaller(bool is64Bit = false);
		~LoPrinterInstaller();
		void set_SourceFileRenderer(CSZ sourceFile);
		void set_SourceFileUI(CSZ sourceFile);
		void set_SourceFileHelpfile(CSZ helpFile);
		bool InstallDriver();
		bool InstallPrinter();
		bool DeleteDriver(CSZ driverName);
		bool DeletePrinter(CSZ printerName);
	private:
		LoPrinterInstallPrivate *m_pimpl;
	};

}

