/*
 * device.h - CC31xx/CC32xx Host Driver Implementation
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef __DEVICE_H__
#define	__DEVICE_H__

#include "simplelink.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef void (*P_INIT_CALLBACK)(unsigned long Status);


/*****************************************************************************

    API Prototypes

 *****************************************************************************/


/*!

    \addtogroup device
    @{

*/

#define SL_DEVICE_GENERAL_CONFIGURATION (1)
#define SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME (11)
#define SL_DEVICE_GENERAL_VERSION                 (12)
#define SL_DEVICE_STATUS                          (2)




/*!
    \brief     Internal function for setting device configurations

    \return    On success, zero is returned. On error, -1 is 
               returned
   
    \param[in] DeviceSetId   configuration id
    \param[in] Option	 configurations option
    \param[in] ConfigLen	 configurations len
    \param[in] pValues		 configurations values

    \sa         
    \note 
    \warning     
    \par
    \code
         Setting device time and date example:

         SlDateTime_t dateTime= {0};
         dateTime.sl_tm_day =   (unsigned long)23;          // Day of month (DD format) range 1-13
         dateTime.sl_tm_mon =   (unsigned long)6;           // Month (MM format) in the range of 1-12 
         dateTime.sl_tm_year =  (unsigned long)2014;        // Year (YYYY format) 
         dateTime.sl_tm_hour =  (unsigned long)17;          // Hours in the range of 0-23
         dateTime.sl_tm_min =   (unsigned long)55;          // Minutes in the range of 0-59
         dateTime.sl_tm_sec =   (unsigned long)22;          // Seconds in the range of  0-59
         sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION,SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,sizeof(SlDateTime_t),(unsigned char *)(&dateTime));


    \endcode   
*/
#if _SL_INCLUDE_FUNC(sl_DevSet)
long sl_DevSet(unsigned char DeviceSetId ,unsigned char Option,unsigned char ConfigLen, unsigned char *pValues);
#endif




/*!
    \brief     Internal function for getting device configurations

    \return    On success, zero is returned. On error, -1 is 
               returned
   
    \param[in] DeviceGetId   configuration id - example SL_DEVICE_STATUS							 

    \param[out] pOption   Get configurations option, example for get status options
							- SL_EVENT_CLASS_GLOBAL
							- SL_EVENT_CLASS_DEVICE
							- SL_EVENT_CLASS_WLAN  
							- SL_EVENT_CLASS_BSD   
							- SL_EVENT_CLASS_NETAPP
							- SL_EVENT_CLASS_NETCFG
							- SL_EVENT_CLASS_NVMEM 
							- SL_EVENT_CLASS_VERSION

    \param[out] pConfigLen   The length of the allocated memory as input, when the
                                        function complete, the value of this parameter would be
                             the len that actually read from the device.\n 
                                        If the device return length that is longer from the input 
                                        value, the function will cut the end of the returned structure
                                        and will return SL_ESMALLBUF
    \param[out] pValues     Get configurations values
    \sa         
    \note 
    \warning  
    \par  Examples:
    \code
     
     Example for getting WLAN class status:
     unsigned long statusWlan;
     unsigned char pConfigOpt;
     pConfigOpt = SL_EVENT_CLASS_WLAN;
     sl_DevGet(SL_DEVICE_GET_STATUS,&pConfigOpt,&pConfigLen,(unsigned char *)(&statusWlan));
     
     Example for getting version:
     
      SlVersionFull ver;
      pConfigOpt = SL_DEVICE_GENERAL_VERSION;
      sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION,&pConfigOpt,&pConfigLen,(unsigned char *)(&ver));
     
     printf("CHIP %d\nMAC 31.%d.%d.%d.%d\nPHY %d.%d.%d.%d\nNWP %d.%d.%d.%d\nROM %d\nHOST %d.%d.%d.%d\n",
             ver.ChipFwAndPhyVersion.ChipId,
             ver.ChipFwAndPhyVersion.FwVersion[0],ver.ChipFwAndPhyVersion.FwVersion[1],
             ver.ChipFwAndPhyVersion.FwVersion[2],ver.ChipFwAndPhyVersion.FwVersion[3],
             ver.ChipFwAndPhyVersion.PhyVersion[0],ver.ChipFwAndPhyVersion.PhyVersion[1],
             ver.ChipFwAndPhyVersion.PhyVersion[2],ver.ChipFwAndPhyVersion.PhyVersion[3],
             ver.NwpVersion[0],ver.NwpVersion[1],ver.NwpVersion[2],ver.NwpVersion[3],
             ver.RomVersion,
             SL_MAJOR_VERSION_NUM,SL_MINOR_VERSION_NUM,SL_VERSION_NUM,SL_SUB_VERSION_NUM);
     
     \endcode
     \code
         Getting Device time and date example:
         
         SlDateTime_t dateTime =  {0};  
         char configLen = sizeof(SlDateTime_t); 
         char configOpt = SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME;
         sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION,&configOpt, &configLen,(unsigned char *)(&dateTime)); 
         
         printf("Day %d,Mon %d,Year %d,Hour %,Min %d,Sec %d\n",dateTime.sl_tm_day,dateTime.sl_tm_mon,dateTime.sl_tm_year
                 dateTime.sl_tm_hour,dateTime.sl_tm_min,dateTime.sl_tm_sec);
     \endcode
*/
#if _SL_INCLUDE_FUNC(sl_DevGet)
long sl_DevGet(unsigned char DeviceGetId, unsigned char *pOption,unsigned char *pConfigLen, unsigned char *pValues);
#endif





/*
    Declare the different event group classifications
    The SimpleLink device send asynchronous events. Each event has a group 
    classification according to its nature.
*/
#define SL_EVENT_CLASS_GLOBAL   (0)
#define SL_EVENT_CLASS_DEVICE   (1)
#define SL_EVENT_CLASS_WLAN     (2)
#define SL_EVENT_CLASS_BSD      (3)
#define SL_EVENT_CLASS_NETAPP   (4)
#define SL_EVENT_CLASS_NETCFG   (5)
#define SL_EVENT_CLASS_NVMEM    (6)



/* SL_EVENT_CLASS_WLAN user events */
#define SL_WLAN_CONNECT_EVENT                     (1)
#define SL_WLAN_DISCONNECT_EVENT                  (2)
/* Smart Config events */
#define SL_WLAN_SMART_CONFIG_START_EVENT          (3)
#define SL_WLAN_SMART_CONFIG_STOP_EVENT           (4)

#define SL_WLAN_STA_CONNECTED_EVENT               (5)
#define SL_WLAN_STA_DISCONNECTED_EVENT            (6)

#define SL_WLAN_P2P_DEV_FOUND_EVENT			      (7)
#define	SL_WLAN_P2P_NEG_REQ_RECEIVED_EVENT		  (8)
#define SL_WLAN_CONNECTION_FAILED_EVENT		      (9)

/* SL_EVENT_CLASS_DEVICE user events */
#define SL_DEVICE_FATAL_ERROR_EVENT               (1)
/* SL_EVENT_CLASS_BSD user events */               
#define	SL_SOCKET_TX_FAILED_EVENT                 (1)                      
#define	SL_SOCKET_SSL_ACCEPT_EVENT                (2)
/* SL_EVENT_CLASS_NETAPP user events */   
#define	SL_NETAPP_IPACQUIRED_EVENT                (1)
#define	SL_NETAPP_IPACQUIRED_V6_EVENT             (2)

/* Receive this error in case there are no resources to issue the command
   If possible, increase the number of MAX_CUNCURENT_ACTIONS (result in memory increase)
   If not, try again later */
#define SL_POOL_IS_EMPTY -2000

/* Receive this error in case a given length for RX buffer was too small. 
   Receive payload was bigger than the given buffer size. therefore payload is cut according to receive size 
   Recommend to increase buffer size */
#define SL_ESMALLBUF -2001

/* Receive this error in case zero length is supplied to a get API
   Recommend to supply length according to requested information (view options defines for help) */
#define SL_EZEROLEN -2002

/* User supplied invalid parameter */
#define SL_INVALPARAM -2003
/*!
    Declare the different event group classifications for sl_DevGet
 */

/******************  DEVICE CLASS  ****************/
#define EVENT_DROPPED_DEVICE_ASYNC_GENERAL_ERROR          0x00000001L
#define STATUS_DEVICE_SMART_CONFIG_ACTIVE                 0x80000000L

/******************  WLAN CLASS  ****************/
#define EVENT_DROPPED_WLAN_WLANASYNCONNECTEDRESPONSE      0x00000001L
#define EVENT_DROPPED_WLAN_WLANASYNCDISCONNECTEDRESPONSE  0x00000002L
#define EVENT_DROPPED_WLAN_STA_CONNECTED                  0x00000004L
#define EVENT_DROPPED_WLAN_STA_DISCONNECTED               0x00000008L
  
#define STATUS_WLAN_STA_CONNECTED                         0x80000000L
  
/******************  NETAPP CLASS  ****************/
#define EVENT_DROPPED_NETAPP_IPACQUIRED                   0x00000001L
#define EVENT_DROPPED_NETAPP_IPACQUIRED_V6                0x00000002L
#define EVENT_DROPPED_NETAPP_IP_LEASED                    0x00000004L
#define EVENT_DROPPED_NETAPP_IP_RELEASED                  0x00000008L
                      
/******************  BSD CLASS  ****************/
#define EVENT_DROPPED_SOCKET_TXFAILEDASYNCRESPONSE        0x00000001L
  
/******************  FS CLASS  ****************/
  



typedef struct
{
	unsigned long	ChipId;
	unsigned long   FwVersion[4];
	unsigned char   PhyVersion[4];
}_SlPartialVersion;

typedef struct
{
	_SlPartialVersion ChipFwAndPhyVersion;
	unsigned long  NwpVersion[4];
	unsigned short  RomVersion;
	unsigned short  Padding;
}SlVersionFull;

typedef enum
{
    SL_ERR_SENDER_HEALTH_MON,
    SL_ERR_SENDER_CLI_UART,
    SL_ERR_SENDER_SUPPLICANT,
    SL_ERR_SENDER_NETWORK_STACK,

    SL_ERR_NUM_SENDER_LAST=0xFF
}SlErrorSender_e; 


typedef struct
{
    signed char 		status;
    SlErrorSender_e		sender;
}sl_DeviceReport;

typedef union
{
  sl_DeviceReport           deviceEvent; 
} SlDeviceEventData_u;


typedef struct
{
   unsigned long              Event;
   SlDeviceEventData_u        EventData;
} SlDeviceEvent_t;


typedef struct  
{
       /* time */
       unsigned long sl_tm_sec;
       unsigned long sl_tm_min;
       unsigned long sl_tm_hour;
       /* date */
       unsigned long sl_tm_day; /* 1-31 */
       unsigned long sl_tm_mon; /* 1-12 */
       unsigned long sl_tm_year; /*  YYYY 4 digits  */
       unsigned long sl_tm_week_day; /* not required */
       unsigned long sl_tm_year_day; /* not required */ 
       unsigned long reserved[3];  
}SlDateTime_t;




/*!
    \brief Start the SimpleLink device
    
    This function initialize the communication interface, set the enable pin 
    of the device, and call to the init complete callback.

    \param[in]      pIfHdl              Opened Interface Object. In case the interface 
                                        must be opened outside the SimpleLink Driver, the
                                        user might give the handler to be used in \n
                                        any access of the communication interface with the 
                                        device (UART/SPI). \n
                                        The SimpleLink driver will open an interface port
                                        only if this parameter is null! \n
    \param[in]      pDevName            The name of the device to open. Could be used when 
                                        the pIfHdl is null, to transfer information to the 
                                        open interface function \n
    \param[in]      pInitCallBack       Pointer to function that would be called
                                        on completion of the initialization process.\n
                                        If this parameter is NULL the function is 
                                        blocked until the device initialization 
                                        is completed, otherwise the function returns 
                                        immediately.

    \return         Roles 
                    - ROLE_STA, ROLE_AP, ROLE_P2P in case of success, 
                      otherwise in failure one of the following is return:
                    - ROLE_STA_ERR  (Failure to load MAC\PHY in STA role)
                    - ROLE_AP_ERR  (Failure to load MAC\PHY in AP role)
                    - ROLE_P2P_ERR  (Failure to load MAC\PHY in P2P role)

    
     \sa             sl_Stop

    \note           belongs to \ref basic_api

    \warning        This function must be called before any other SimpleLink API is used
    \par            Example:
    \code            
                   An example for open interface without callback routine. The interface name and handler are
                   handled by the sl_IfOpen routine: 

                   if( sl_Start(NULL, NULL, NULL) == 0)
                   {
                       LOG("Error opening interface to device\n"); 
                   }
    \endcode
*/
#if _SL_INCLUDE_FUNC(sl_Start)
int sl_Start(const void* pIfHdl, char* pDevName, const P_INIT_CALLBACK pInitCallBack);
#endif

/*!
    \brief Stop the SimpleLink device

    This function clears the enable pin of the device, closes the communication \n
	interface and invokes the stop complete callback 

    \param[in]      timeout                       Stop timeout in msec. Should be used to give the device time to finish \n 
                                                  any transmission/reception that is not completed when the function was called. \n
                    Addional options:
                    - 0                             Enter to hibernate immediately \n
                    - 0xFFFF                        Host waits for device's response before \n
                                                    hibernating, without timeout protection \n      
                    - 0 < Timeout[msec] < 0xFFFF    Host waits for device's response before \n
                                                    hibernating, with a defined timeout protection \n
                                                    This timeout defines the max time to wait. The NWP \n
                                                    response can be sent earlier than this timeout.

    \return         On success, zero is returned. On error, -1 is returned     
 
    \sa             sl_Start

    \note           This API will shutdown the device and invoke the "i/f close" function regardless \n
                    if it was opened implicitly or explicitly. \n
                    It is up to the platform interface library to properly handle interface close \n
                    routine \n
                    belongs to \ref basic_api \n
    \warning     
*/
#if _SL_INCLUDE_FUNC(sl_Stop)
int sl_Stop(unsigned short timeout);
#endif

/*!
    \brief          Set asynchronous event mask
    
    Mask asynchronous events from the device. Masked events do not
	generate asynchronous messages from the device. 
    
    
    \param[in]      EventClass          The classification groups that the 
                                        mask is referred to. Need to be one of
                                        the following:
                                        - SL_EVENT_CLASS_GLOBAL
                                        - SL_EVENT_CLASS_DEVICE
                                        - SL_EVENT_CLASS_WLAN  
                                        - SL_EVENT_CLASS_BSD   
                                        - SL_EVENT_CLASS_NETAPP
                                        - SL_EVENT_CLASS_NETCFG
                                        - SL_EVENT_CLASS_NVMEM 


    \param[in]      Mask               Event Mask bitmap. Valid mask are (per group):
                                        - SL_EVENT_CLASS_WLAN user events
                                          - SL_WLAN_CONNECT_EVENT                     
                                          - SL_WLAN_DISCONNECT_EVENT
                                          - SL_WLAN_STA_CONNECTED_EVENT
                                          - SL_WLAN_STA_DISCONNECTED_EVENT            
                                        - Smart Config events
                                          - SL_WLAN_SMART_CONFIG_START_EVENT          
                                          - SL_WLAN_SMART_CONFIG_STOP_EVENT
                                        - SL_EVENT_CLASS_DEVICE user events
                                          - SL_DEVICE_FATAL_ERROR_EVENT
                                        - SL_EVENT_CLASS_BSD user events
                                          - SL_SOCKET_TX_FAILED_EVENT     
                                          - SL_SOCKET_SSL_ACCEPT_EVENT 
                                        - SL_EVENT_CLASS_NETAPP user events
                                          - SL_NETAPP_IPACQUIRED_EVENT 
                                          - SL_NETAPP_IPACQUIRED_V6_EVENT
     
    \return         On success, zero is returned. On error, -1 is returned       

    \sa             sl_EventMaskGet

    \note           belongs to \ref ext_api
     
    \warning     
    \par           Example:
    \code          

    An example of masking out connection/disconnection from WLAN class:
                   sl_EventMaskSet(SL_EVENT_CLASS_WLAN, (SL_WLAN_CONNECT_EVENT | SL_WLAN_DISCONNECT_EVENT) );
    
    \endcode
*/
#if _SL_INCLUDE_FUNC(sl_EventMaskSet)
int sl_EventMaskSet(unsigned char EventClass , unsigned long Mask);
#endif
/*!
    \brief Get current event mask of the device
    
    return the events bit mask from the device. In case that event is 
    masked, the device is not sending this event.  
    
    \param[in]      EventClass          The classification groups that the 
                                        mask is referred to. Need to be one of
                                        the following:
                                        - SL_EVENT_CLASS_GLOBAL
                                        - SL_EVENT_CLASS_DEVICE
                                        - SL_EVENT_CLASS_WLAN  
                                        - SL_EVENT_CLASS_BSD   
                                        - SL_EVENT_CLASS_NETAPP
                                        - SL_EVENT_CLASS_NETCFG
                                        - SL_EVENT_CLASS_NVMEM 

    \param[out]      pMask              Pointer to Mask bitmap where the 
                                        value should be stored. Bitmasks are the same as in \ref sl_EventMaskSet
     
    \return         On success, zero is returned. On error, -1 is returned       
     
    \sa             sl_EventMaskSet         

    \note           belongs to \ref ext_api

    \warning     
    \par           Example:
    \code          

    An example of getting an event mask for WLAN class
    unsigned long maskWlan;
                   sl_StatusGet(SL_EVENT_CLASS_WLAN,&maskWlan);

   \endcode
*/
#if _SL_INCLUDE_FUNC(sl_EventMaskGet)
int sl_EventMaskGet(unsigned char EventClass, unsigned long *pMask);
#endif


/*!
    \brief the simple link task entry

    \Param
    This function must be called from the main loop or from dedicated thread in
    the following cases:
        - Non-Os Platform - should be called from the mail loop
        - Multi Threaded Platform when the user does not implement the external spawn functions - 
           should be called from dedicated thread allocated to the simplelink driver.
           In this mode the function never return.
    
    \return         None
    
    \sa             sl_Stop

    \note           belongs to \ref basic_api

    \warning        This function must be called from a thread that is start running before 
                    any call to other simple link API
*/
#if _SL_INCLUDE_FUNC(sl_Task)
void sl_Task();
#endif


/*!

 Close the Doxygen group.
 @}

 */


#ifdef  __cplusplus
}
#endif /*  __cplusplus */


#endif  /*  __DEVICE_H__ */
