

//------------------------------------------------------------------------------
//      Includes
//------------------------------------------------------------------------------
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */
#include <linux/sched.h>
#include <linux/interrupt.h>
//#include <zz/reg_rw.h>

#include "common.h"
//#include "device.h"
//#include "board.h"
//#include "trace.h"


#include "usb.h"
#include "standard.h"

#define USB_MAJOR 242 
//------------------------------------------------------------------------------
//      Structures
//------------------------------------------------------------------------------

//! \brief  Represents all the data which must be sent when the host requests
//!         a configuration descriptor.
//! \param  sConfiguration Configuration descriptor
//! \param  sInterface     First interface descriptor
//! \see    S_usb_configuration_descriptor
//! \see    S_usb_interface_descriptor
//! \see    usb_20.pdf - Section 9.4.3
typedef struct {

    S_usb_configuration_descriptor sConfiguration;
    S_usb_interface_descriptor     sInterface;
    S_usb_endpoint_descriptor      sBulkOut;       //!< Bulk OUT endpoint
    S_usb_endpoint_descriptor      sBulkIn;        //!< Bulk IN endpoint

} S_core_configuration_descriptor;

//------------------------------------------------------------------------------
//      Prototypes
//------------------------------------------------------------------------------

//! \brief  Initialization callback
static void CBK_Init(const S_usb *pUsb);

//! \brief  Suspend callback
static void CBK_Suspend(const S_usb *pUsb);

//! \brief  Resume callback
static void CBK_Resume(const S_usb *pUsb);

//! \brief  New request callback
static void CBK_NewRequest(const S_usb *pUsb);

//! \brief  New reset callback
//static void CBK_Reset(const S_usb *pUsb);

//! \brief  New SOF callback
//static void CBK_SOF(const S_usb *pUsb);

//------------------------------------------------------------------------------
//      Internal variables
//------------------------------------------------------------------------------

//! \brief  List of endpoints (including endpoint 0) used by the device.
//! \see    S_usb_endpoint
static S_usb_endpoint pEndpoints[] = {

    USB_ENDPOINT_SINGLEBANK, // Control endpoint 0
    USB_ENDPOINT_DUALBANK,
    USB_ENDPOINT_DUALBANK
};

//! \brief  Variable used to store the last received SETUP packet.
//! \see    S_usb_request
//! \see    S_usb
static S_usb_request sSetup;

//! \brief  Variable used to store the current device state
//! \see    S_usb
static unsigned int dState;

//! \brief  List of implemented callbacks
//! \see    S_usb_callbacks
//! \see    S_usb
static S_usb_callbacks sCallbacks = {

    CBK_Init,
    0,//CBK_Reset
    CBK_Suspend,
    CBK_Resume,
   CBK_NewRequest,// MY_REQUEST_HANDLE,
    0 //CBK_SOF
};

// \brief  Default driver when an UDP controller is present on a chip
static S_usb_driver sDefaultDriver; 
/*= {

    AT91C_BASE_UDP,
    0,
    0,
    AT91C_ID_UDP,
    AT91C_PMC_UDP,
    &sUDPMethods
};*/
//! \brief  USB driver instance
//! \see    S_usb
static S_usb sUsb;
/* = {

    &sDefaultDriver,
    pEndpoints,
    3,
    &sCallbacks,
    &sSetup,
    &dState
};*/

// Descriptors
//! Device descriptor
static const S_usb_device_descriptor sDeviceDescriptor = {

    sizeof(S_usb_device_descriptor), // Size of this descriptor in bytes
    USB_DEVICE_DESCRIPTOR,           // DEVICE Descriptor Type
    0x0200,                         // USB Specification 2.0
    0xdc,                            // Class is specified in the interface descriptor.
    0x00,                            // Subclass is specified in the interface descriptor.
    0x00,                            // Protocol is specified in the interface descriptor.
    USB_ENDPOINT0_MAXPACKETSIZE,     // Maximum packet size for endpoint zero
    0x03eb,                // Vendor ID "ATMEL"
    0x4444,                          // Product ID
    0x0100,                          // Device release number
    0x00,                            // Index 1: manufacturer string
    0x00,                            // Index 2: product string
    0x00,                            // Index 3: serial number string
    0x01                             // One possible configurations
};

//! \brief  Device configuration, which includes the configuration descriptor
//!         and the first interface descriptor in this case.
//! \see    S_core_configuration_descriptor
static const S_core_configuration_descriptor sConfigurationDescriptor = {

    // Configuration descriptor
    {
        sizeof(S_usb_configuration_descriptor),  // Size of this descriptor
        USB_CONFIGURATION_DESCRIPTOR,            // CONFIGURATION descriptor
        sizeof(S_core_configuration_descriptor), // Total length
        0x01,                                    // Number of interfaces
        0x01,                                    // Value to select this configuration
        0x00,                                    // No index for describing this configuration
        USB_CONFIG_SELF_NOWAKEUP,//0x60,                // Device attributes
        USB_POWER_MA(100)                        // maximum power consumption in mA
    },
    // Interface Descriptor
    {
        sizeof(S_usb_interface_descriptor), // Size of this descriptor in bytes
        USB_INTERFACE_DESCRIPTOR,           // INTERFACE Descriptor Type
        0x00,                               // Interface number 0
        0x00,                               // Value used to select this setting
        COMM_NUM_ENDPOINTS-1,                               // Number of endpoints used by this
                                            // interface (excluding endpoint 0).
        0xdc,                   // Interface class
        0xa0,                               // Interface subclass
        0xb0,                               // Interface protocol
        0x00                                // Index of string descriptor
    },
    // Bulk-OUT Endpoint Descriptor
    {
        sizeof(S_usb_endpoint_descriptor),   // Size of this descriptor in bytes
        USB_ENDPOINT_DESCRIPTOR,             // ENDPOINT descriptor type
        0x01,//USB_ENDPOINT_OUT | BOT_EPT_BULK_OUT, // OUT endpoint, address 01h
        ENDPOINT_TYPE_BULK,                  // Bulk endpoint
        64,                                  // Maximum packet size is 64 bytes
        0,                                // Must be 0 for full-speed bulk
    },
    // Bulk_IN Endpoint Descriptor
    {
        sizeof(S_usb_endpoint_descriptor), // Size of this descriptor in bytes
        USB_ENDPOINT_DESCRIPTOR,           // ENDPOINT descriptor type
        0x82,//USB_ENDPOINT_IN | BOT_EPT_BULK_IN, // IN endpoint, address 02h
        ENDPOINT_TYPE_BULK,                // Bulk endpoint
        64,                                // Maximum packet size if 64 bytes
        0,                              // Must be 0 for full-speed bulk
    }
};
const S_usb_endpoint_descriptor* InOutEP[2]={&(sConfigurationDescriptor.sBulkOut),&(sConfigurationDescriptor.sBulkIn)};
// String descriptors
//! \brief  Language ID
static const S_usb_language_id sLanguageID = {

    USB_STRING_DESCRIPTOR_SIZE(1),
    USB_STRING_DESCRIPTOR,
    USB_LANGUAGE_ENGLISH_US
};

//! \brief  Manufacturer description
static const char pManufacturer[] = {

    USB_STRING_DESCRIPTOR_SIZE(5),
    USB_STRING_DESCRIPTOR,
    USB_UNICODE('A'),
    USB_UNICODE('T'),
    USB_UNICODE('M'),
    USB_UNICODE('E'),
    USB_UNICODE('L')
};

//! \brief  Product descriptor
static const char pProduct[] = {

    USB_STRING_DESCRIPTOR_SIZE(15),
    USB_STRING_DESCRIPTOR,
    USB_UNICODE('A'),
    USB_UNICODE('T'),
    USB_UNICODE('M'),
    USB_UNICODE('E'),
    USB_UNICODE('L'),
    USB_UNICODE(' '),
    USB_UNICODE('A'),
    USB_UNICODE('T'),
    USB_UNICODE('9'),
    USB_UNICODE('1'),
    USB_UNICODE(' '),
    USB_UNICODE('E'),
    USB_UNICODE('N'),
    USB_UNICODE('U'),
    USB_UNICODE('M')
};

//! \brief  Serial number
static const char pSerial[] = {

    USB_STRING_DESCRIPTOR_SIZE(12),
    USB_STRING_DESCRIPTOR,
    USB_UNICODE('0'),
    USB_UNICODE('1'),
    USB_UNICODE('2'),
    USB_UNICODE('3'),
    USB_UNICODE('4'),
    USB_UNICODE('5'),
    USB_UNICODE('6'),
    USB_UNICODE('7'),
    USB_UNICODE('8'),
    USB_UNICODE('9'),
    USB_UNICODE('A'),
    USB_UNICODE('F')
};

//! \brief  List of string descriptors used by the device
static const char *pStringDescriptors[] = {

    (char *) &sLanguageID,
    pManufacturer,
    pProduct,
    pSerial
};

//! \brief  List of descriptors used by the device
//! \see    S_std_descriptors
S_std_descriptors sDescriptors = {

    &sDeviceDescriptor,
    (S_usb_configuration_descriptor *) &sConfigurationDescriptor,
    pStringDescriptors,
    InOutEP
};

//! \brief  Standard class driver
//! \see    S_std_class
S_std_class sClass;
/* = {

    &sUsb,
    &sDescriptors,
    (unsigned short)0,
    (unsigned short)0
};*/

//------------------------------------------------------------------------------
//      Internal Functions
//------------------------------------------------------------------------------

// Interrupt Service Routines
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! \brief  Handler for the USB controller interrupt
//!
//!         Defers the call to the USB_Handler function.
//------------------------------------------------------------------------------
static irqreturn_t usb_interrupt(int irq, void *dev_id/*, struct pt_regs *regs*/)
{
    USB_Handler(&sUsb);

    return IRQ_HANDLED;
}

//------------------------------------------------------------------------------
//! \brief  Handler for the VBus state change interrupt
//!
//!         This method calls the USB_Attach function to perform the necessary
//!         operations.
//------------------------------------------------------------------------------
#if !defined(USB_BUS_POWERED)
void ISR_VBus(void)
{
    USB_Attach(&sUsb);

    // Acknowledge the interrupt
    AT91F_PIO_GetInterruptStatus(AT91C_PIO_VBUS);
}
#endif // !defined(USB_BUS_POWERED)

// Callbacks
//------------------------------------------------------------------------------
extern void DRIVER_AsmUARTInterruptHandler(void);
extern void DRIVER_AsmVBUSInterruptHandler(void);

//------------------------------------------------------------------------------
//! \brief  Callback invoked during the initialization of the USB driver
//!
//!         Configures and enables USB controller and VBus monitoring interrupts
//! \param  pUsb    Pointer to a S_usb instance
//------------------------------------------------------------------------------
static void CBK_Init(const S_usb *pUsb)
{


    // Power up the USB controller
    USB_Attach(pUsb);
}
//------------------------------------------------------------------------------
//! \brief  Callback invoked when the device becomes suspended
//!
//!         Disables LEDs (if they are used) and then puts the device into
//!         low-power mode. When traces are used, the device does not enter
//!         low-power mode to avoid losing some outputs.
//! \param  pUsb    Pointer to a S_usb instance
//------------------------------------------------------------------------------
static void CBK_Suspend(const S_usb *pUsb)
{


#if defined(NOTRACES)
    DEV_Suspend();
#endif
}

//------------------------------------------------------------------------------
//! \brief  Callback invoked when the device leaves the suspended state
//!
//!         The device is first returned to a normal operating mode and LEDs are
//!         re-enabled. When traces are used, the device does not enter
//!         low-power mode to avoid losing some outputs.
//! \param  pUsb    Pointer to a S_usb instance
//------------------------------------------------------------------------------
static void CBK_Resume(const S_usb *pUsb)
{
#if defined(NOTRACES)
    DEV_Resume();
#endif

}

//------------------------------------------------------------------------------
//! \brief  Callback invoked when a new SETUP request is received
//!
//!         The new request if forwarded to the standard request handler,
//!         which performs the enumeration of the device.
//! \param  pUsb   Pointer to a S_usb instance
//------------------------------------------------------------------------------
static void CBK_NewRequest(const S_usb *pUsb)
{
    AT9261_UDP_REQUEST_HANDLE(&sClass);//STD_RequestHandler(&sClass);
}


//------------------------------------------------------------------------------
//          Main
//------------------------------------------------------------------------------

static void iniBuf(void)
{
	AT9261_UDP_IN_BUFFER_LENGTH=0;
	AT9261_UDP_OUT_BUFFER_LENGTH=0;
	CancelButtonPressed=0;
}

static int HasInitial=false;
static int Major;
AT91PS_PMC AT91C_BASE_PMC;
AT91PS_MATRIX AT91C_BASE_MATRIX;
AT91PS_AIC AT91C_BASE_AIC;
AT91PS_UDP AT91C_BASE_UDP;
AT91PS_PIO AT91C_BASE_PIOA;

static int udp_open(struct inode *mynode, struct file *myfile)
{
    printk(KERN_ALERT"here in open_func!\n");
	if(!HasInitial)
	{
	// Configure and enable the USB controller interrupt
    //AT91F_AIC_ConfigureIt(AT91C_BASE_AIC,
    //                      USB_GetDriverID(&sUsb),
    //                      AT91C_AIC_PRIOR_HIGHEST,
    //                      0, //AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL,
    //                      ISR_Driver);

   // AT91F_AIC_EnableIt(AT91C_BASE_AIC, USB_GetDriverID(&sUsb));
    //request_irq(10, usb_interrupt, 0, "USB_TEST", NULL);
   	
		USB_Init(&sUsb);
		iniBuf();
		while (!ISSET(USB_GetState(&sUsb), USB_STATE_POWERED));
    	USB_Connect(&sUsb);
   		HasInitial=true;
        request_irq(10, usb_interrupt, 0, "USB_TEST", NULL);
	SET (AT91C_BASE_PIOA->PIO_SODR, 1 << 16);	
	//at91_pio_set_output(PIOA_BASE,1<<16);
	}
    printk(KERN_ALERT"get out of open_func!\n");
	if(!ISSET(USB_GetState(&sUsb), USB_STATE_CONFIGURED))
		return 0;
	return 1;
}
static int udp_close(struct inode *mynode, struct file *myfile)
{
	//AT91F_AIC_DisableIt(AT91C_BASE_AIC,USB_GetDriverID(&sUsb));
	
	SET (AT91C_BASE_PIOA->PIO_CODR, 1 << 16);
	//at91_pio_clear_output(PIOA_BASE,1<<16);
	free_irq(10, NULL);
	UDP_Disconnect(&sUsb);
   	USB_Attach(&sUsb);
   	HasInitial=false;
   	return 1;
}

//读USB数据，返回值为实际读取长度
static ssize_t ReadUSB(struct file *filp, char __user *buf, size_t length, loff_t *off)
{
	if(!ISSET(USB_GetState(&sUsb), USB_STATE_CONFIGURED))
	{
		//printk(KERN_ALERT"ReadUSB:NOT CONFIGURE!\n");
		return 0;
	}
	if(AT9261_UDP_IN_BUFFER_LENGTH==0)
	{
		//printk(KERN_ALERT"ReadUSB:BUFFER 0!\n");
		return 0;
	}
	if(CancelButtonPressed)
	{
		CancelButtonPressed=0;
		return -1;
	}
//printk(KERN_ALERT"now begin COPY_TO_USER!\n");
    copy_to_user(buf,AT9261_UDP_IN_BUFFER,PACKET_LENGTH);
    AT9261_UDP_IN_BUFFER_LENGTH=0;
//printk(KERN_ALERT"now end COPY_TO_USER!\n");
    return PACKET_LENGTH;			
}

static ssize_t WriteUSB(struct file *filp, const char __user *buf,size_t length, loff_t *off)
{
	if(!ISSET(USB_GetState(&sUsb), USB_STATE_CONFIGURED))
		return 0;
	if(AT9261_UDP_OUT_BUFFER_LENGTH>0)
		return 0;
	if(CancelButtonPressed)
	{
		CancelButtonPressed=0;
		return -1;
	}
	copy_from_user(AT9261_UDP_OUT_BUFFER,buf,length);
	AT9261_UDP_OUT_BUFFER_LENGTH=length;
	//USB_Write(p1->pUsb,2,OUT_BUFFER,PACKET_LENGTH,(Callback_f)FINISHED_WRITE,0);

	return 1;
}
static struct file_operations fops = {
	.read = ReadUSB,
	.write = WriteUSB,
	.open = udp_open,
	.release = udp_close
};


static int init_usb_module(void)
{
	if (register_chrdev(USB_MAJOR, "TP11USB", &fops))
	{
		printk(KERN_ALERT "usb device major is %d", USB_MAJOR);
		Major = USB_MAJOR;
	}
	else /* if (Major < 0) */
	{
		printk("USBDEV: Registering the character device failed with %d\n", Major);
		return Major;
	}

	AT91C_BASE_PMC=(AT91PS_PMC)ioremap(0xFFFFFC00,0x0084);
	AT91C_BASE_MATRIX=(AT91PS_MATRIX)ioremap(0xFFFFEE00,19*4);
	AT91C_BASE_AIC=(AT91PS_AIC)ioremap(0xFFFFF000,0x14c);
	AT91C_BASE_UDP=(AT91PS_UDP)ioremap(0xFFFA4000,0x78);
	AT91C_BASE_PIOA= (AT91PS_PIO)ioremap(0xFFFFF400,0xa8);

	sDefaultDriver.pInterface=AT91C_BASE_UDP;
	sDefaultDriver.pEndpointFIFO=0;
	sDefaultDriver.pDMAInterface=0;
	sDefaultDriver.dID=AT91C_ID_UDP;
	sDefaultDriver.dPMC=AT91C_PMC_UDP;
	sDefaultDriver.pMethods=&sUDPMethods;

	sUsb.pDriver=&sDefaultDriver;
	sUsb.pEndpoints=pEndpoints;
	sUsb.dNumEndpoints=3;
	sUsb.pCallbacks=&sCallbacks;
	sUsb.pSetup=&sSetup;
	sUsb.pState=&dState;
	sClass.pUsb=&sUsb;
	sClass.pDescriptors=&sDescriptors;
	sClass.wDeviceStatus=(unsigned short)0;
	sClass.wData=(unsigned short)0;
	AT9261_UDP_IN_BUFFER=(char *)__get_free_page(GFP_KERNEL);
	AT9261_UDP_OUT_BUFFER=(char *)__get_free_page(GFP_KERNEL);
	
	SET (AT91C_BASE_PIOA->PIO_PER, 1 << 16);
	SET (AT91C_BASE_PIOA->PIO_OER, 1 << 16);
	SET (AT91C_BASE_PIOA->PIO_CODR, 1 << 16);

	return 0;

}
static void cleanup_usb_module(void)
{
//	int ret;
	unregister_chrdev(Major, "TP11USB");
//	if (ret < 0)
//		printk(KERN_ALERT"Error in unregister_chrdev: %d\n", ret);
	iounmap(AT91C_BASE_PMC);
	iounmap(AT91C_BASE_MATRIX);
	iounmap(AT91C_BASE_AIC);
	iounmap(AT91C_BASE_UDP);	
}

module_init(init_usb_module);
module_exit(cleanup_usb_module);

