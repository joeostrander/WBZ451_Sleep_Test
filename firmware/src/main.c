/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "device_deep_sleep.h"          // GRACO EDIT OR ADDITION

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


// GRACO EDIT OR ADDITION START
#define KILL_IT_WITH_FIRE_MAGIC_NUMBER     (0xDEADBEEF)

uint32_t __attribute__((persistent)) killitwithfire;

void _on_reset( void )
{
    RCON_RESET_CAUSE reset_cause = RCON_ResetCauseGet();
    RCON_ResetCauseClear( reset_cause );
    
    if( reset_cause & RCON_RESET_CAUSE_POR )
    {
        killitwithfire = 0;
    }
    else if( killitwithfire == KILL_IT_WITH_FIRE_MAGIC_NUMBER )
    {
        __asm volatile( "cpsid i" ::: "memory" );
        __asm volatile( "dsb" );
        __asm volatile( "isb" );

        PMU_Set_Mode(PMU_MODE_BUCK_PSM);

        /* Disable current sensor to improve current consumption. */
        PMU_ConfigCurrentSensor(false);

        DEVICE_EnterExtremeDeepSleep();        
    }
}
// GRACO EDIT OR ADDITION END
/*******************************************************************************
 End of File
*/

