/**
 * \file   timer.c
 *
 * \brief  This file contains various delay & timer functions that use
 *         OSAL timer.
 */

#include <ti/osal/osal.h>

#define TIMER1                      1
#define TIMER_ID                    TIMER1

void delayTmrIsr(void* arg);

TimerP_Params   delayTimerParams;
TimerP_Handle   delayTimerHandle;
TimerP_Status   timerStatus;
volatile unsigned int    delayTimerFlag;
volatile unsigned int    delayTimerCount;

void delayTimerSetup()
{
    TimerP_Params_init(&delayTimerParams);

    delayTimerParams.period = 1000000;  // 1s
    delayTimerParams.periodType = TimerP_PeriodType_MICROSECS;
    delayTimerParams.arg = 0;
    delayTimerParams.startMode = TimerP_StartMode_USER;
    delayTimerParams.runMode = TimerP_RunMode_ONESHOT;
    delayTimerHandle = TimerP_create(TIMER_ID,  (TimerP_Fxn)&delayTmrIsr,&delayTimerParams);
    
    delayTimerCount = 0;
    delayTimerFlag  = 0;
}

void delayTmrIsr(void* arg)
{
#if defined (evmOMAPL137) || defined (lcdkOMAPL138) || defined (lcdkC6748)
#ifndef TIRTOS
    TimerP_ClearInterrupt(delayTimerHandle);
#endif
#endif
    delayTimerCount++;
    delayTimerFlag  = 1;
}

void osalTimerStart(unsigned int ms)
{
    delayTimerCount = 0;
    delayTimerFlag  = 0;

    TimerP_setPeriodMicroSecs(delayTimerHandle, (uint32_t)(ms*1000));
    TimerP_start(delayTimerHandle);
}

void osalTimerStop()
{
    TimerP_stop(delayTimerHandle);

    delayTimerCount = 0;
    delayTimerFlag  = 0;
}

unsigned int osalTimerExpired()
{
    if (delayTimerFlag == 1) return 1; else return 0;
}


// a blocking delay function
void osalTimerDelay(unsigned int ms)
{
    osalTimerStart(ms);
    while (delayTimerFlag == 0);
}

/* A function to validate the delay length
 * calling delay(20ms) 250 times - which equates to about 5 seconds 
*/
void osalTimerTest()
{
    int i,j;

    for (i = 0; i<10; i++)
    {
        for (j=0;j<250;j++)
        {
            osalTimerDelay(20); // 20ms
        }

    }
}
