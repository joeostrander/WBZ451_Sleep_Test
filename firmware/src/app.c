// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "app.h"
#include "definitions.h"


#include "FreeRTOS.h"
#include "task.h"
#include "peripheral/power/plib_power.h"
#include "system/console/sys_console.h"
#include "device_deep_sleep.h"
#include "phy.h"



// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

//static void shutdown(void);
static void reset(void);
/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;


    appData.appQueue = xQueueCreate( 64, sizeof(APP_Msg_T) );
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

#define KILL_IT_WITH_FIRE_MAGIC_NUMBER     (0xDEADBEEF)

extern uint32_t killitwithfire;

void APP_Tasks ( void )
{
    APP_Msg_T    appMsg[1];
    APP_Msg_T *p_appMsg;
    p_appMsg = appMsg;

//    static bool power_cycled = false;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            //appData.appQueue = xQueueCreate( 10, sizeof(APP_Msg_T) );

            
            
//
//            SYS_CONSOLE_PRINT("RCON_RSWRST: 0x%08X\r\n", RCON_REGS->RCON_RSWRST);
//            SYS_CONSOLE_PRINT("RCON_RCON: 0x%08X\r\n", RCON_REGS->RCON_RCON);
//            vTaskDelay(500);
            //11000000000000100000000000000011
            
//            if (RCON_RCON_SWR_SWR)  // A SOFTWARE RESET HAS OCCURRED
//            {
//                SYS_CONSOLE_PRINT("SHUTDOWN!!.\r\n");
//                vTaskDelay(500);
//                
//                // clear bit?
//                RCON_RCON_SWR(0);
//
//                shutdown();
//                while(1);
//            }

            //if (RCON_REGS->RCON_RCON & 1)  // A POWER ON RESET HAS OCCURRED
            //if (RCON_RCON_SWR_SWR)  // A SOFTWARE RESET HAS OCCURRED

//            if (RCON_REGS->RCON_RCON & RCON_RCON_SWR_Msk)
//            {
//                SYS_CONSOLE_PRINT("SOFTWARE RESET\r\n");
//                vTaskDelay(100);
//                //shutdown();
//            }
//            else
//            {
//                SYS_CONSOLE_PRINT("POWER ON\r\n");
//                SYS_CONSOLE_PRINT("PHY INIT!.\r\n");
//                power_cycled = true;
//                SYS_Load_Cal(WSS_ENABLE_ZB);
//                PHY_Init();
//                
//                if(app_P2P_Phy_Init() != true)
//                {
//
//                    appInitialized = false;
//                }
//            }
            

            if (appInitialized)
            {
                SYS_CONSOLE_PRINT("READY.\r\n");
                vTaskDelay(500);
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
//            if (OSAL_QUEUE_Receive(&appData.appQueue, &appMsg, OSAL_WAIT_FOREVER))
//            {
//                app_P2P_Phy_TaskHandler(p_appMsg);
//            }
            
            
            
            if (xTaskGetTickCount() > 5000)
            {
                killitwithfire = KILL_IT_WITH_FIRE_MAGIC_NUMBER;
                RCON_SoftwareReset();
                
            }
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

//static void shutdown(void)
//{
//    PHY_TrxSleep(DEEP_SLEEP_MODE);
//    DEVICE_EnterExtremeDeepSleep(false); 
//}
//static void shutdown(void)
//{
//    __asm volatile( "cpsid i" ::: "memory" );
//    __asm volatile( "dsb" );
//    __asm volatile( "isb" );
//    
//        GPIOA_REGS->GPIO_LAT = 0x0U; /* Initial Latch Value */
//    GPIOA_REGS->GPIO_TRISCLR = 0x67ffU; /* Direction Control */
//    
//        GPIOB_REGS->GPIO_LAT = 0x0U; /* Initial Latch Value */
//    GPIOB_REGS->GPIO_TRISCLR = 0x3fffU; /* Direction Control */
//    GPIOB_REGS->GPIO_ANSELCLR = 0xffU; /* Digital Mode Enable */
//    
////    SYS_Load_Cal(WSS_ENABLE_NONE);
//    
////    PMU_Set_Mode(PMU_MODE_BUCK_PSM);
////    /* Disable current sensor to improve current consumption. */
////    PMU_ConfigCurrentSensor(false);
//    
//    
////    PMU_Set_Mode(0);    // TESTING!!!
//    
//    
//    
//    PHY_RxEnable(PHY_STATE_TRX_OFF);
//    vTaskDelay(100);
//    taskDISABLE_INTERRUPTS();
//    PHY_TrxSleep(DEEP_SLEEP_MODE);
//    
//    
//    vTaskDelay(5000);
//    
//    POWER_LowPowerModeEnter(LOW_POWER_DEEP_SLEEP_MODE);
//    
//    DEVICE_EnterExtremeDeepSleep(false); 
//    
//
//}

//static void reset(void)
//{
//        GPIOA_REGS->GPIO_LAT = 0x0U; /* Initial Latch Value */
//    GPIOA_REGS->GPIO_TRISCLR = 0x67ffU; /* Direction Control */
//    
//        GPIOB_REGS->GPIO_LAT = 0x0U; /* Initial Latch Value */
//    GPIOB_REGS->GPIO_TRISCLR = 0x3fffU; /* Direction Control */
//    GPIOB_REGS->GPIO_ANSELCLR = 0xffU; /* Digital Mode Enable */
//    
//    __asm volatile( "cpsid i" ::: "memory" );
//    __asm volatile( "dsb" );
//    __asm volatile( "isb" );
//    
//    PHY_RxEnable(PHY_STATE_TRX_OFF);
//    taskDISABLE_INTERRUPTS();
//    PHY_TrxSleep(DEEP_SLEEP_MODE);
//    POWER_LowPowerModeEnter(LOW_POWER_DEEP_SLEEP_MODE);
////    DEVICE_EnterExtremeDeepSleep(false); 
//
//    /* Perform system unlock sequence */
//    CFG_REGS->CFG_SYSKEY = 0x00000000U;
//    CFG_REGS->CFG_SYSKEY = 0xAA996655U;
//    CFG_REGS->CFG_SYSKEY = 0x556699AAU;
//    
//    // set SWRST bit to arm reset
//    RCON_REGS->RCON_RSWRSTSET = 1;
//    
//    // read RSWRST register to trigger reset
//    (void)RCON_REGS->RCON_RSWRST;
//    
//    // prevent any unwanted code execution until reset occurs
//    while(1);
//}
//static void shutdown(void)
//{
//    __asm volatile( "cpsid i" ::: "memory" );
//    __asm volatile( "dsb" );
//    __asm volatile( "isb" );
//
//    taskDISABLE_INTERRUPTS();
//    PHY_TrxSleep(DEEP_SLEEP_MODE);
//
//    DEVICE_EnterExtremeDeepSleep(false); 
//    
//    
////                POWER_LowPowerModeEnter(LOW_POWER_DEEP_SLEEP_MODE);
//}

/*******************************************************************************
 End of File
 */
