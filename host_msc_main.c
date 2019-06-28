/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <stdio.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>
#include <ti/board/board.h>
#include <ti/board/src/lcdkOMAPL138/include/board_internal.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_usb.h>
#include <ti/csl/cslr_syscfg.h>
#include "ti/drv/usb/example/common/hardware.h"
#include <ti/fs/fatfs/diskio.h>
#include <ti/fs/fatfs/FATFS.h>
#include "timer.h"
#include "types.h"
#include "fatfs_port_usbmsc.h"
#include "fs_shell_app_utils.h"
#include <ti/drv/usb/usb_drv.h>
#include <ti/drv/usb/usb_osal.h>
#include "usblib.h"
#include "usbhost.h"
#include "usbhmsc.h"
#include <ti/drv/uart/UART_stdio.h>



/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <stdio.h>
#include <ti/sysbios/knl/Task.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>

#include <ti/board/board.h>

#if (!(defined (SOC_AM335x) && defined (SOC_AM437x)))
#include <ti/csl/soc.h>
#endif

#include "ti/drv/usb/example/common/hardware.h"

#include <ti/fs/fatfs/diskio.h>
#include <ti/fs/fatfs/FATFS.h>

#include "timer.h"
#include "types.h"
#include "fatfs_port_usbmsc.h"
#include "fs_shell_app_utils.h"

#include <ti/drv/usb/usb_drv.h>
#include <ti/drv/usb/usb_osal.h>
#include "usblib.h"
#include "usbhost.h"
#include "usbhmsc.h"
#include <ti/drv/uart/UART_stdio.h>

/*****************************************************************************
*
* The instance data for the MSC driver.
*
*****************************************************************************/
unsigned int g_ulMSCInstance = 0;


/*****************************************************************************
*
* Hold the current state for the application.
*
****************************************************************************/
typedef enum
{
    /*
    * No device is present.
    */
    STATE_NO_DEVICE,

    /*
    * Mass storage device is being enumerated.
    */
    STATE_DEVICE_ENUM,

    /*
    * Mass storage device is ready.
    */
    STATE_DEVICE_READY,

    /*
    * An unsupported device has been attached.
    */
    STATE_UNKNOWN_DEVICE,

    /*
    * A power fault has occurred.
    */
    STATE_POWER_FAULT
} tState;

volatile tState g_eState;



/*****************************************************************************
*
* FAT fs variables.
*
*****************************************************************************/
/* USBMSC function table for USB implementation */

FATFS_DrvFxnTable FATFS_drvFxnTable = {
    FATFSPortUSBDiskClose,      /* closeDrvFxn */
    FATFSPortUSBDiskIoctl,      /* controlDrvFxn */
    FATFSPortUSBDiskInitialize, /* initDrvFxn */
    FATFSPortUSBDiskOpen,       /* openDrvFxn */
    FATFSPortUSBDiskWrite,      /* writeDrvFxn */
    FATFSPortUSBDiskRead        /* readDrvFxn */
};

/* FATFS configuration structure */
FATFS_HwAttrs FATFS_initCfg[_VOLUMES] =
{
    {
        0U
    },
    {
        1U
    },
    {
        2U
    },
    {
        3U
    }
};

/* FATFS objects */
FATFS_Object FATFS_objects[_VOLUMES];

/* FATFS configuration structure */
const FATFS_Config FATFS_config[_VOLUMES + 1] = {
    {
        &FATFS_drvFxnTable,
        &FATFS_objects[0],
        &FATFS_initCfg[0]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[1],
         &FATFS_initCfg[1]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[2],
         &FATFS_initCfg[2]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[3],
         &FATFS_initCfg[3]
    },
    {NULL, NULL, NULL}
};

FATFS_Handle fatfsHandle = NULL;
uint32_t     g_fsHasOpened = 0;


/* ========================================================================== */
/*                                Prototypes                                  */
/* ========================================================================== */
void usbHostIntrConfig(USB_Params* usbParams);
void MSCCallback(uint32_t ulInstance, uint32_t ulEvent, void *pvData);
void usbCoreIntrHandler(uint32_t* pUsbParam);

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define USB_INSTANCE            0       /* USB #0 (the USB-A host port) on the EVM */
                                        /* USB #1 (the USB-OTG port) on the EVM */

/*****************************************************************************
* main 
*
*****************************************************************************/
Void taskFxn(UArg a0, UArg a1)
{
    USB_Params  usb_host_params;
    USB_Handle  usb_handle;
    int         rc;

    usb_host_params.usbMode      = USB_HOST_MSC_MODE;
    usb_host_params.instanceNo   = USB_INSTANCE;
    usb_handle = USB_open(usb_host_params.instanceNo, &usb_host_params);

    if (usb_handle == 0) 
    {
        /* failed to open the USB driver */
        while(1);
    }

    /*
    *Setup the INT Controller
    */
	usbHostIntrConfig (&usb_host_params);

    /*
    * Initialize the file system.
    */
    FATFS_init();


    /*
    * Open an instance of the mass storage class driver.
    */
    g_ulMSCInstance = USBHMSCDriveOpen(usb_host_params.instanceNo, 0, MSCCallback);

    while(1) {    
        rc = USBHCDMain(USB_INSTANCE, g_ulMSCInstance);

        if (rc != 0)
        {
            while(1);
        }
        if(g_eState == STATE_DEVICE_ENUM)
        {
            /*
            * Take it easy on the Mass storage device if it is slow to
            * start up after connecting.
            */
            if(USBHMSCDriveReady(g_ulMSCInstance) != 0)
            {
                /*
                * Wait about 100ms before attempting to check if the
                * device is ready again.
                */
                usb_osalDelayMs(100);
            }

            if (!g_fsHasOpened)
            {
                /* USBMSC FATFS initialization */
                rc = FATFS_open(0U, NULL, &fatfsHandle);
                if (rc != FR_OK)
                {
                }
                else
                {
                    g_fsHasOpened = 1;
                }
            }

            /* only do this when the device is already enummerated. */
            FSShellAppUtilsProcess();
        }
    }
}




void usbHostIntrConfig(USB_Params* usbParams)
{
    HwiP_Handle hwiHandle = NULL;
    OsalRegisterIntrParams_t interruptRegParams;

    /* Initialize with defaults */
    Osal_RegisterInterrupt_initParams(&interruptRegParams);

    /* Populate the interrupt parameters */
    interruptRegParams.corepacConfig.name=NULL;
    interruptRegParams.corepacConfig.corepacEventNum=SYS_INT_USB0; /* Event going in to CPU */
    interruptRegParams.corepacConfig.intVecNum= OSAL_REGINT_INTVEC_EVENT_COMBINER; /* Host Interrupt vector */
    interruptRegParams.corepacConfig.isrRoutine = (void (*)(uintptr_t))usbCoreIntrHandler;
    interruptRegParams.corepacConfig.arg = (uintptr_t)usbParams;

    Osal_RegisterInterrupt(&interruptRegParams,&hwiHandle);
    USB_irqConfig(usbParams->usbHandle, usbParams);
}



/*****************************************************************************
*
* This is the callback from the MSC driver.
*
* \param ulInstance is the driver instance which is needed when communicating
* with the driver.
* \param ulEvent is one of the events defined by the driver.
* \param pvData is a pointer to data passed into the initial call to register
* the callback.
*
* This function handles callback events from the MSC driver.  The only events
* currently handled are the MSC_EVENT_OPEN and MSC_EVENT_CLOSE.  This allows
* the main routine to know when an MSC device has been detected and
* enumerated and when an MSC device has been removed from the system.
*
* \return Returns \e true on success or \e false on failure.
*
*****************************************************************************/
void
MSCCallback(uint32_t ulInstance, uint32_t ulEvent, void *pvData)
{
    /*
    * Determine the event.
    */
    switch(ulEvent)
    {
        /*
        * Called when the device driver has successfully enumerated an MSC
        * device.
        */
        case MSC_EVENT_OPEN:
        {
            /*
            * Proceed to the enumeration state.
            */
            g_eState = STATE_DEVICE_ENUM;
            break;
        }

        /*
        * Called when the device driver has been unloaded due to error or
        * the device is no longer present.
        */
        case MSC_EVENT_CLOSE:
        {
            /*
            * Go back to the "no device" state and wait for a new connection.
            */
            g_eState = STATE_NO_DEVICE;

            g_fsHasOpened = 0;

            break;
        }

        default:
        {
            break;
        }
    }
}

/* main entry point for USB host core interrupt handler with USB Wrapper setup
* Matching interrupt call-back function API */
void usbCoreIntrHandler(uint32_t* pUsbParam)
{
    USB_coreIrqHandler(((USB_Params*)pUsbParam)->usbHandle, (USB_Params*)pUsbParam);
}

/*****************************************************************************
* main 
*
*****************************************************************************/
int main(void)
{
    Uint16 i;

    Task_Handle task;
    Task_Params params;
    Error_Block eb;

    CSL_SyscfgRegsOvly 	sysRegs = (CSL_SyscfgRegsOvly)(CSL_SYSCFG_0_REGS);
    CSL_Usb_otgRegsOvly usbRegs = (CSL_Usb_otgRegsOvly)CSL_USB_0_REGS;

    // BOARD UNLOCK
    sysRegs->KICK0R = 0x83e70b13; // Write Access Key 0
    sysRegs->KICK1R = 0x95A4F1E0; // Write Access Key 1

    //sysRegs->PINMUX9 |= (0x1 << 4); // Set bit4 Pinmux9 for USB Use
    //sysRegs->PINMUX9&= 0xFFFFFF7F;  // Clear bit 7 Pinmux9 for USB Use

    /* CONFIGURE THE DRVVBUS PIN HERE.*/
    /* See your device-specific System Reference Guide for more informationon how to set up the pinmux.*/
    CSL_FINST(sysRegs->PINMUX9, SYSCFG_PINMUX9_PINMUX9_7_4, USB0_DRVVBUS);

    // Reset the USB controller:
    usbRegs->CTRLR|= 0x00000001;

    // Wait until controller is finished with Reset.
    // When done, it will clear the RESET bit field.
    while((usbRegs->CTRLR& 0x1) == 1); 

    // RESET: Hold PHY in Reset
    sysRegs->CFGCHIP2 |= 0x00008000; // Hold PHY in Reset

    // Drive Reset for few clock cycles
    for (i=0;i<50; i++); sysRegs->CFGCHIP2&= 0xFFFF7FFF;// Release PHY from Reset

    /* Configure PHY with the Desired Operation*/

    // OTGMODE
    sysRegs->CFGCHIP2&= 0xFFFF9FFF;// 00=> Do Not OverridePHY Values

    // PHYPWDN
    sysRegs->CFGCHIP2&= 0xFFFFFBFF;// 1/0 => PowerdDown/NormalOperation

    // OTGPWRDN
    sysRegs->CFGCHIP2&= 0xFFFFFDFF;// 1/0 => PowerDown/NormalOperation

    // DATAPOL
    sysRegs->CFGCHIP2|= 0x00000100;// 1/0 => Normal/Reversed

    // SESNDEN
    sysRegs->CFGCHIP2|= 0x00000020;// 1/0 => NormalOperation/SessionEnd

    // VBDTCTEN
    sysRegs->CFGCHIP2|= 0x00000010;// 1/0 => VBUS Comparator Enable/Disable
/* Configure PHY PLL use and Select Source*/

    // REF_FREQ[3:0]
    sysRegs->CFGCHIP2|= 0x00000002;// 0010b=> 24MHzInputSource

    // USB2PHY CLK MUX: Select External Source
    sysRegs->CFGCHIP2&= 0xFFFFF7FF;// 1/0 => Internal/External(Pin)

    // PHY_PLLON: On Simulation PHY PLL is OFF
    sysRegs->CFGCHIP2|= 0x00000040;

    // Wait Until PHY Clock is Good.
    while((sysRegs->CFGCHIP2& 0x00020000)== 0);

    #ifndef HS_ENABLE
        // Disable high-speed
        CSL_FINS(usbRegs->POWER, USB_OTG_POWER_HSEN, 0);
    #else
        // Enable high-speed
        CSL_FINS(usbRegs->POWER, USB_OTG_POWER_HSEN, 1);
    #endif

    // Enable Interrupts
    // Enable interrupts in OTG block
    usbRegs->CTRLR&= 0xFFFFFFF7;

    // Enable PDR2.0 Interrupt
    usbRegs->INTRTXE= 0x1F;

    // Enable All Core Tx Endpoints Interrupts + EP0 Tx/Rx interrupt
    usbRegs->INTRRXE= 0x1E;

    // Enable All Core Rx Endpoints Interrupts
    // Enable all interrupts in OTG block
    usbRegs->INTMSKSETR= 0x01FF1E1F;

    // Enableall USB interruptsin MUSBMHDRC
    usbRegs->INTRUSBE= 0xFF;

    // Enable SUSPENDM so that suspend can be seen UTMI signal
    CSL_FINS(usbRegs->POWER,USB_OTG_POWER_ENSUSPM,1);

    // Clear all pending interrupts
    usbRegs->INTCLRR= usbRegs->INTSRCR;

    // Start a session in "HOST" Mode.
    CSL_FINS(usbRegs->DEVCTL, USB_OTG_DEVCTL_SESSION, 1);

    Error_init(&eb);
    Task_Params_init(&params);
    params.stackSize = 0x2000;
    task = Task_create(taskFxn, &params, &eb);
    if (task == NULL) {
        BIOS_exit(0);
    }

    // setup delay timer
    delayTimerSetup();

    BIOS_start();    /* does not return */

    return 0;
}


