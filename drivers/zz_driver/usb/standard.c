

//------------------------------------------------------------------------------
//      Includes
//------------------------------------------------------------------------------

#include "common.h"
//#include "device.h"
//#include "board.h"
//#include "trace.h"
#include <linux/kernel.h>
#include "usb.h"
#include "standard.h"
//------------------------------------------------------------------------------
//      Internal functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// \brief  Callback for the STD_SetConfiguration function.
//
//         Configures the device and the endpoints
// \param  pClass Pointer to a class driver instance
//------------------------------------------------------------------------------
static void STD_ConfigureEndpoints(const S_std_class *pClass)
{
    unsigned char i;

    // Enter the Configured state
    USB_SetConfiguration(pClass->pUsb);

    // Configure endpoints
    for (i = 0; i < (pClass->pUsb->dNumEndpoints-1); i++) {

        USB_ConfigureEndpoint(pClass->pUsb,
                              pClass->pDescriptors->pEndpoints[i]);
    }
}

//------------------------------------------------------------------------------
// \brief  Sends a zero-length packet and starts the configuration procedure.
// \param  pClass          Pointer to a class driver instance
// \param  bConfiguration  Newly selected configuration
//------------------------------------------------------------------------------
static void STD_SetConfiguration(S_std_class   *pClass,
                                 unsigned char bConfiguration)
{
    USB_SendZLP0(pClass->pUsb,
                 (Callback_f) STD_ConfigureEndpoints,
                 pClass);
}

//------------------------------------------------------------------------------
// \brief  Sends the currently selected configuration to the host.
// \param  pClass Pointer to a class driver instance
//------------------------------------------------------------------------------
static void STD_GetConfiguration(S_std_class *pClass)
{
    if (ISSET(USB_GetState(pClass->pUsb), USB_STATE_CONFIGURED)) {

        pClass->wData = 1;
    }
    else {

        pClass->wData = 0;
    }

    USB_Write(pClass->pUsb, 0, &(pClass->wData), 1, 0, 0);
}

//------------------------------------------------------------------------------
// \brief  Sends the current device status to the host.
// \param  pClass Pointer to a class driver interface
//------------------------------------------------------------------------------
static void STD_GetDeviceStatus(S_std_class *pClass)
{
    // Bus or self-powered ?
    if (ISSET(pClass->pDescriptors->pConfiguration->bmAttibutes,
              USB_CONFIG_SELF_NOWAKEUP)) {

        // Self powered device
        pClass->wDeviceStatus |= SELF_POWERED;
    }
    else {

        // Bus powered device
        pClass->wDeviceStatus &= ~SELF_POWERED;
    }

    // Return the device status
    USB_Write(pClass->pUsb, 0, &(pClass->wDeviceStatus), 2, 0, 0);
}

//------------------------------------------------------------------------------
// \brief  Sends the current status of specified endpoint to the host.
// \param  pClass    Pointer to a class driver instance
// \param  bEndpoint Endpoint number
//------------------------------------------------------------------------------
static void STD_GetEndpointStatus(S_std_class   *pClass,
                                  unsigned char bEndpoint)
{
    //! Retrieve the endpoint current status
    pClass->wData = (unsigned short) USB_Halt(pClass->pUsb,
                                              bEndpoint,
                                              USB_GET_STATUS);

    //! Return the endpoint status
    USB_Write(pClass->pUsb, 0, &(pClass->wData), 2, 0, 0);
}

//------------------------------------------------------------------------------
// \brief  Sends the device descriptor to the host.
//
//         The number of bytes actually sent depends on both the length
//         requested by the host and the actual length of the descriptor.
// \param  pClass  Pointer to a class driver instance
// \param  wLength Number of bytes requested by the host
//------------------------------------------------------------------------------
static void STD_GetDeviceDescriptor(const S_std_class *pClass,
                                    unsigned short    wLength)
{
    USB_Write(pClass->pUsb,
              0,
              (void *) pClass->pDescriptors->pDevice,
              min1(sizeof(S_usb_device_descriptor), wLength),
              0,
              0);
}

//------------------------------------------------------------------------------
// \brief  Sends the configuration descriptor to the host.
//
//         The number of bytes actually sent depends on both the length
//         requested by the host and the actual length of the descriptor.
// \param  pClass  Pointer to a class driver instance
// \param  wLength Number of bytes requested by the host
//------------------------------------------------------------------------------
static void STD_GetConfigurationDescriptor(const S_std_class *pClass,
                                           unsigned short    wLength)
{
    USB_Write(pClass->pUsb,
              0,
              (void *) pClass->pDescriptors->pConfiguration,
              min1(pClass->pDescriptors->pConfiguration->wTotalLength,
                  wLength),
              0,
              0);
}

#if defined(HIGHSPEED)
//------------------------------------------------------------------------------
// \brief  Sends the qualifier descriptor to the host.
//
//         The number of bytes actually sent depends on both the length
//         requested by the host and the actual length of the descriptor.
// \param  pClass  Pointer to a class driver instance
// \param  wLength Number of bytes requested by the host
//------------------------------------------------------------------------------
static void STD_GetQualifierDescriptor(const S_std_class *pClass,
                                       unsigned short    wLength)
{
    USB_Write(pClass->pUsb,
              0,
              (void *) pClass->pDescriptors->pQualifier,
              min1(pClass->pDescriptors->pQualifier->bLength, wLength),
              0,
              0);
}

//------------------------------------------------------------------------------
// \brief  Sends the other speed configuration descriptor to the host.
//
//         The number of bytes actually sent depends on both the length
//         requested by the host and the actual length of the descriptor.
// \param  pClass  Pointer to a class driver instance
// \param  wLength Number of bytes requested by the host
//------------------------------------------------------------------------------
static void STD_GetOSCDescriptor(const S_std_class *pClass,
                                 unsigned short    wLength)
{
    USB_Write(pClass->pUsb,
              0,
              (void *) pClass->pDescriptors->pOtherSpeedConfiguration,
              min1(pClass->pDescriptors->pOtherSpeedConfiguration->wTotalLength,
                  wLength),
              0,
              0);
}
#endif

//------------------------------------------------------------------------------
// \brief  Sends the specified string descriptor to the host
//
//         The number of bytes actually sent depends on both the length
//         requested by the host and the actual length of the descriptor.
// \param  pClass  Pointer to a class driver instance
// \param  wLength Number of bytes requested by the host
// \param  wIndex  Index of requested string descriptor
//------------------------------------------------------------------------------
static void STD_GetStringDescriptor(const S_std_class *pClass,
                                    unsigned short    wLength,
                                    unsigned char     bIndex)
{
    USB_Write(pClass->pUsb,
              0,
              (void *) pClass->pDescriptors->pStrings[bIndex],
              min1( *(pClass->pDescriptors->pStrings[bIndex]), wLength),
              0,
              0);
}

//------------------------------------------------------------------------------
//      Exported functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! \ingroup usb_std_req_hlr
//! \brief   Handles standard SETUP requests
//! \param   pClass Pointer to a class driver instance
//------------------------------------------------------------------------------
void STD_RequestHandler(S_std_class *pClass)
{
    S_usb_request *pSetup = USB_GetSetup(pClass->pUsb);


    // Handle incoming request
    switch (pSetup->bRequest) {
    //----------------------
    case USB_GET_DESCRIPTOR:
    //----------------------

        // The HBYTE macro returns the upper byte of a word
        switch (HBYTE(pSetup->wValue)) {
        //-------------------------
        case USB_DEVICE_DESCRIPTOR:
        //-------------------------
            STD_GetDeviceDescriptor(pClass, pSetup->wLength);
            break;

        //--------------------------------
        case USB_CONFIGURATION_DESCRIPTOR:
        //--------------------------------
            STD_GetConfigurationDescriptor(pClass, pSetup->wLength);
            break;

#if defined(HIGHSPEED)
        //-----------------------------------
        case USB_DEVICE_QUALIFIER_DESCRIPTOR:
        //-----------------------------------
            STD_GetQualifierDescriptor(pClass, pSetup->wLength);
            break;

        //--------------------------------------------
        case USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR:
        //--------------------------------------------
            STD_GetOSCDescriptor(pClass, pSetup->wLength);
            break;
#endif
        //-------------------------
        case USB_STRING_DESCRIPTOR:
        //-------------------------
            STD_GetStringDescriptor(pClass,
                                    pSetup->wLength,
                                    LBYTE(pSetup->wValue));
            break;

        //------
        default:
        //------

            USB_Stall(pClass->pUsb, 0);

        }
        break;

    //-------------------
    case USB_SET_ADDRESS:
    //-------------------
        USB_SendZLP0(pClass->pUsb,
                     (Callback_f) USB_SetAddress,
                     (void *) pClass->pUsb);
        break;

    //-------------------------
    case USB_SET_CONFIGURATION:
    //-------------------------
        STD_SetConfiguration(pClass, (char) pSetup->wValue);
        break;

    //-------------------------
    case USB_GET_CONFIGURATION:
    //-------------------------
        STD_GetConfiguration(pClass);
        break;

    //---------------------
    case USB_CLEAR_FEATURE:
    //---------------------

        switch (pSetup->wValue) {
            //---------------------
            case USB_ENDPOINT_HALT:
            //---------------------
                USB_Halt(pClass->pUsb, LBYTE(pSetup->wIndex), USB_CLEAR_FEATURE);
                USB_SendZLP0(pClass->pUsb, 0, 0);
                break;

            //----------------------------
            case USB_DEVICE_REMOTE_WAKEUP:
            //----------------------------
                pClass->wDeviceStatus &= ~REMOTE_WAKEUP; // Remote wakeup disabled
                USB_SendZLP0(pClass->pUsb, 0, 0);
                break;

            //------
            default:
            //------
                USB_Stall(pClass->pUsb, 0);

        }
        break;

    //------------------
    case USB_GET_STATUS:
    //------------------

        switch (USB_REQUEST_RECIPIENT(pSetup)) {
        //-------------------------
        case USB_RECIPIENT_DEVICE:
        //-------------------------
            STD_GetDeviceStatus(pClass);
            break;

        //---------------------------
        case USB_RECIPIENT_ENDPOINT:
        //---------------------------
            STD_GetEndpointStatus(pClass,
                                  LBYTE(pSetup->wIndex));
            break;

        //------
        default:
        //------

            USB_Stall(pClass->pUsb, 0);

        }
        break;

    //-------------------
    case USB_SET_FEATURE:
    //-------------------

        switch (pSetup->wValue) {
        //---------------------
        case USB_ENDPOINT_HALT:
        //---------------------
            USB_Halt(pClass->pUsb, LBYTE(pSetup->wIndex), USB_SET_FEATURE);
            USB_SendZLP0(pClass->pUsb, 0, 0);
            break;

        //----------------------------
        case USB_DEVICE_REMOTE_WAKEUP:
        //----------------------------
            pClass->wDeviceStatus |= REMOTE_WAKEUP; // Remote wakeup enabled
            USB_SendZLP0(pClass->pUsb, 0, 0);
            break;

        //------
        default:
        //------

            USB_Stall(pClass->pUsb, 0);

        }
        break;

    //------
    default:
    //------

        USB_Stall(pClass->pUsb, 0);
    }
}
static char DataParseInSetup[16];
//char AT9261_UDP_IN_BUFFER[PACKET_LENGTH];
char* AT9261_UDP_IN_BUFFER;
volatile int AT9261_UDP_IN_BUFFER_LENGTH;
//char AT9261_UDP_OUT_BUFFER[PACKET_LENGTH];
char* AT9261_UDP_OUT_BUFFER;
volatile int AT9261_UDP_OUT_BUFFER_LENGTH;
volatile int CancelButtonPressed;


void FINISHED_WRITE(int p1,int p2,int p3,int p4)
{
	AT9261_UDP_OUT_BUFFER_LENGTH=0;
}
void FINISHED_READ(void)
{
	AT9261_UDP_IN_BUFFER_LENGTH=PACKET_LENGTH;
}

/*void dataPraseInSetup(S_std_class * p1,int p2,int p3,int p4)//接收到了一个Register命令数据
{
	int high,low,all;
	if(DataParseInSetup[5]==0x81)//读
	{
		if(OUT_BUFFER_LENGTH==0)
		{
			USB_Stall(p1->pUsb, 0);
			return;
		}
		
		high =DataParseInSetup[4];
		low = DataParseInSetup[3];
		all=(high*256)+low;
		USB_Write(p1->pUsb,2,OUT_BUFFER,all,(Callback_f)FINISHED_WRITE,0);			
		USB_SendZLP0(p1->pUsb, 0, 0);
		
		
	}

	else if(DataParseInSetup[5]==0x80)//写
	{
		if(IN_BUFFER_LENGTH!=0)
		{
			USB_Stall(p1->pUsb, 0);
			return;
		}
		high = DataParseInSetup[4];
		low = DataParseInSetup[3];
		all=(high*256)+low;
					
		USB_SendZLP0(((S_std_class *)p1)->pUsb, 0, 0);
		USB_Read(p1->pUsb,1,IN_BUFFER,all,(Callback_f)FINISHED_READ,0);
	}
}*/

extern void AT9261_UDP_REQUEST_HANDLE(S_std_class *pClass)
{
    S_usb_request *pSetup = USB_GetSetup(pClass->pUsb);
    unsigned char type=pSetup->bmRequestType & 0x60;
//	printk1(KERN_ALERT"I am in AT9261_UDP_REQUEST_HANDLE!\n");
    if(type==0x40)//自定义请求
	{
		/*if(pSetup->wIndex==0x0471||pSetup->wIndex==0x0472)
		{
			USB_Read(pClass->pUsb,0,DataParseInSetup,pSetup->wLength,(Callback_f)dataPraseInSetup,pClass);
			USB_SendZLP0(pClass->pUsb, 0, 0);
		}*/
		if(pSetup->wIndex==0x0471)
		{
//			printk1(KERN_ALERT"now enter RequestHandler!\n");
			if(AT9261_UDP_IN_BUFFER_LENGTH!=0)
			{
//				printk1(KERN_ALERT"REQUEST_HANDLE STALL!\n");
				USB_Stall(pClass->pUsb, 0);
				return;
			}
			USB_SendZLP0(((S_std_class *)pClass)->pUsb, 0, 0);
			USB_Read(pClass->pUsb,1,AT9261_UDP_IN_BUFFER,PACKET_LENGTH,(Callback_f)FINISHED_READ,0);
//			printk1(KERN_ALERT"now exit RequestHandler!\n");
		}
		else if(pSetup->wIndex==0x0472)
		{
			if(AT9261_UDP_OUT_BUFFER_LENGTH==0)
			{
				USB_Stall(pClass->pUsb, 0);
				return;
			}
			USB_Write(pClass->pUsb,2,AT9261_UDP_OUT_BUFFER,PACKET_LENGTH,(Callback_f)FINISHED_WRITE,0);			
			USB_SendZLP0(pClass->pUsb, 0, 0);
		}
		else if(pSetup->wIndex==0x0474)
		{
			int m=PACKET_LENGTH;
			USB_Write(pClass->pUsb,0,&m,sizeof(m),0,0);
		}
		else if(pSetup->wIndex==0x0476)
		{
			int m=PACKET_LENGTH;
			USB_Write(pClass->pUsb,0,&m,sizeof(m),0,0);
		}
		//else if(pSetup->w)
		else if(pSetup->wIndex==0x0478)
		{
			CancelButtonPressed=1;
			USB_SendZLP0(pClass->pUsb,0,0);
		}
		else
		{
			USB_Stall(pClass->pUsb, 0);
		}
	}
	else if(type==0)
	{
		STD_RequestHandler(pClass);
	}
	else USB_Stall(pClass->pUsb, 0);
}



