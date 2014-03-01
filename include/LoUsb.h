#include <wx/string.h>
#include <wx/vector.h>

struct libusb_device;
struct libusb_device_handle;

namespace Lo {
	/* Device and/or Interface Class codes */
	enum UsbClass
	{
		USB_CLASS_PER_INTERFACE = 0,
		USB_CLASS_AUDIO = 1,			/*!< Audio class */
		USB_CLASS_COMM = 2,				/*!< Communications class */
		USB_CLASS_HID = 3,				/*!< Human Interface Device class */
		USB_CLASS_PHYSICAL = 5,			/*!< Physical */
		USB_CLASS_PRINTER = 7,			/*!< Printer class */
		USB_CLASS_PTP = 6,				/*!< legacy name from libusb-0.1 usb.h */
		USB_CLASS_IMAGE = 6,			/*!< Image class */
		USB_CLASS_MASS_STORAGE = 8,		/*!< Mass storage class */
		USB_CLASS_HUB = 9,				/*!< Hub class */
		USB_CLASS_DATA = 10,			/*!< Data class */
		USB_CLASS_SMART_CARD = 0x0b,	/*!< Smart Card */
		USB_CLASS_CONTENT_SECURITY = 0x0d,	/*!< Content Security */
		USB_CLASS_VIDEO = 0x0e,			/*!< Video */
		USB_CLASS_PERSONAL_HEALTHCARE = 0x0f,/*!< Personal Healthcare */
		USB_CLASS_DIAGNOSTIC_DEVICE = 0xdc,/*!< Diagnostic Device */
		USB_CLASS_WIRELESS = 0xe0,		/*!< Wireless class */
		USB_CLASS_APPLICATION = 0xfe,	/*!< Application class */
		USB_CLASS_VENDOR_SPEC = 0xff	/*! Class is vendor-specific */
	};
	/**
	 * Error codes. Most libusb functions return 0 on success or one of these
	 * codes on failure.
	 */
	enum UsbError {
		USB_SUCCESS = 0,				/*!< Success (no error) */
		USB_ERROR_IO = -1,				/*!< Input/output error */
		USB_ERROR_INVALID_PARAM = -2,	/*!< Invalid parameter */
		USB_ERROR_ACCESS = -3,			/*!< Access denied (insufficient permissions) */
		USB_ERROR_NO_DEVICE = -4,		/*!< No such device (it may have been disconnected) */
		USB_ERROR_NOT_FOUND = -5,		/*!< Entity not found */
		USB_ERROR_BUSY = -6,			/*!< Resource busy */
		USB_ERROR_TIMEOUT = -7,			/*!< Operation timed out */
		USB_ERROR_OVERFLOW = -8,		/*!< Overflow */
		USB_ERROR_PIPE = -9,			/*!< Pipe error */
		USB_ERROR_INTERRUPTED = -10,	/*!< System call interrupted (perhaps due to signal) */
		USB_ERROR_NO_MEM = -11,			/*!< Insufficient memory */
		USB_ERROR_NOT_SUPPORTED = -12,	/*!< Operation not supported or unimplemented on this platform */
		USB_ERROR_OTHER = -99			/*!< Other error */
	};

	class UsbDeviceList;
	class UsbDevice;

	class UsbOpenDevice
	{
		friend class UsbDevice;
	public:
		/** Only UsbDevice can open this class. */
		UsbOpenDevice( UsbDevice *device );
		/** When deleted, automatically closes the device. */
		~UsbOpenDevice();
		UsbError		GetLastError()	{ return m_lastError; }
		/** Close the device */
		void			Close();
		/** Returns true if open */
		bool			IsOpen();
		/** Reads data synchronously. */
		UsbError		Read(void *data, size_t len, size_t* read = nullptr);
		/** Writes data synchronously. */
		UsbError		Write(const void *data, size_t len, size_t* written = nullptr);
		/** Set timeout */
		void			SetTimeout(int timeout)	{ m_timeout = timeout; }
		static const int	DEFAULT_TIMEOUT = 15*1000;
	private:
		/** No copying of this. */
		UsbOpenDevice(const UsbOpenDevice& source );
		libusb_device_handle		*m_pimpl;
		UsbError					m_lastError;
		int							m_timeout;
	};

	/**
	Each USB device that registers in the system is stored in this class.
	You can only obtain a pointer to this class, because once an instance is created, it is never destroyed.
	*/
	class UsbDevice
	{
		friend class UsbDeviceList;
	public:
		UsbDevice(const UsbDevice& source);
		~UsbDevice();
		// Data accessors for static data.
		unsigned		get_Bus() const;
		/** Returns the number of the device on the bus. */
		unsigned		get_Number() const;
		/** Gets the device class */
		UsbClass		get_DeviceClass() const;
		/** Gets the USB version. */
		unsigned		get_MajorVersion() const;
		unsigned		get_MinorVersion() const;
		/** Get the Product ID */
		unsigned		get_ProductID() const;
		/** Get the Vendor ID */
		unsigned		get_VendorID() const;
		/** Gets the last USB error */
		UsbError		GetLastError() const		{ return m_lastError; }
		/** Get the serial number */
		wxString		GetSerialNumber();
		/** Get the given string */
		wxString		GetString(int index);
	private:
		UsbDevice(struct libusb_device *dev);	/*!< Only UsbDeviceList can create and delete this class. */
	private:
		struct libusb_device	*m_pimpl;		/*!< We index into the array stored by UsbDeviceList */
		UsbError				m_lastError;
		wxString				m_serialNumber;	/*!< Serial number */
	private: // Prevent deletion of this class by anyone other than UsbDeviceList
		void *operator new(size_t);
		void *operator new[](size_t);
	};

	/**
	This class should be initialized on startup of the library and/or exe and shutdown on termination.
	There must only be one instance per application.
	Anymore than one will throw exception.
	*/
	class UsbDeviceList
	{
	public:
		/** Initializes the USB library */
		UsbDeviceList();
		/** Terminates the USB library */
		~UsbDeviceList();
		/** Gets the device associated with the given vidpid and index */
		UsbDevice				GetDevice(unsigned vidPid, unsigned index = 0 );
		/** Counts the number of devices which have the given vid & pid */
		size_t					GetCount(unsigned vidPid );
		/** Counts the number of devices which have the given vid */
		size_t					CountByManufacturer( unsigned vid );
		/** Returns a vector of objects */
		wxVector<UsbDevice>		FilterByManufacturer( unsigned vid );		
		/** Gets a reference to the device list that can be used to manipulate the device. */
		wxVector<UsbDevice>&	GetDevices();
		/** Refresh the device list, which will not delete any internal UsbDevice structure. */
		void					Refresh();
	private:
		void					Clear();
		static wxVector<UsbDevice>		*m_devices;	/*!< This internal table can only grow. */
		static struct libusb_device		**m_pimpl;	/*!< Pimpl implementation. */
		static int						m_refCount;	/*!< The number of times this class is references. */
	};

}