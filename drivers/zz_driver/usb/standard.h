

#ifndef _STANDARD_H
#define _STANDARD_H

//! \brief Useful constants wDeviceStatus
//! \see S_std_class
//! \see usb_20.pdf - Section 9.4.5 - Figure 9-4
//! @{

//! \name wDeviceStatus
//! Information Returned by a GetStatus() Request to a Device.
//! @{

//! \brief 
#define SELF_POWERED              (1<<0)

//! \brief 
#define REMOTE_WAKEUP             (1<<1)

//! @}
//! @}

//------------------------------------------------------------------------------
//      Structures
//------------------------------------------------------------------------------

//! \ingroup usb_std_req_hlr
//! \brief   List of standard descriptors used by the device
typedef struct  {

    //! Device descriptor
    const S_usb_device_descriptor           *pDevice;
    //! Configuration descriptor
    const S_usb_configuration_descriptor    *pConfiguration;
    //! List of string descriptors
    const char                              **pStrings;
    //! List of endpoint descriptors
    const S_usb_endpoint_descriptor         **pEndpoints;
#if defined(HIGHSPEED)
    //! Qualifier descriptor (high-speed only)
    const S_usb_device_qualifier_descriptor *pQualifier;
    //! Other speed configuration descriptor (high-speed only)
    const S_usb_configuration_descriptor    *pOtherSpeedConfiguration;
#endif

} S_std_descriptors;

//! \ingroup usb_std_req_hlr
//! \brief   Standard USB class driver structure.
//!
//!          Used to provide standard driver information so external modules can
//!          still access an internal driver.
typedef struct {

    //! Pointer to a S_usb instance
    S_usb             *pUsb;
    //! Pointer to the list of descriptors used by the device
    S_std_descriptors *pDescriptors;
    //! Data buffer used for information returned by a GetStatus() request to
    //! a Device (Figure 9-4. in usb_20.pdf)
    unsigned short           wDeviceStatus;
    //! Data buffer
    unsigned short           wData;

} S_std_class;

//------------------------------------------------------------------------------
//      Exported symbols
//------------------------------------------------------------------------------

extern void STD_RequestHandler(S_std_class *pClass);

#endif // _STANDARD_H
extern void AT9261_UDP_REQUEST_HANDLE(S_std_class *pClass);
#define PACKET_LENGTH 4096

extern char* AT9261_UDP_IN_BUFFER;
extern volatile int AT9261_UDP_IN_BUFFER_LENGTH;
extern char* AT9261_UDP_OUT_BUFFER;
extern volatile int AT9261_UDP_OUT_BUFFER_LENGTH;
extern volatile int CancelButtonPressed;
extern void UDP_Disconnect(const S_usb *pUsb);


