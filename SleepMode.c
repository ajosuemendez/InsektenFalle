/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <SleepMode.h>

void GoSleepWTC(int SleepTime_Min)
{
    int Limit_Time = (SleepTime_Min*60*1000)/4096; //Transforming the Min in Milliseconds and then dividing it with the maximal sleeptime
    
    int Counts_WTC;
    
    for( Counts_WTC = 0; Counts_WTC < Limit_Time; Counts_WTC = Counts_WTC + 1 )
    {
        SleepTimer_Start();
        
        SleepTimer_SetInterval(SleepTimer__CTW_4096_MS );
        
        SleepTimer_GetStatus();
        CyDelay(4096);
    }
}

void GoSleepRTC(int SleepTime_Min)
{
         //PPS with 32Khz quarz

        int Counts_RTC;
        int Limit_Time_RTC =(SleepTime_Min*60);
    
        for( Counts_RTC = 0; Counts_RTC < Limit_Time_RTC; Counts_RTC = Counts_RTC + 1 )
        {
            /* Set system clocks for low power. */
        CyPmSaveClocks();
        
        //Output_LED_Write(1);
        
        /* Sleep until boost refresh is needed. */
        CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_ONE_PPS);
        
        //Output_LED_Write(0);
        
        CyDelay(1000);
        
        /* Restore system clocks. */
        CyPmRestoreClocks();
        }
}


/* [] END OF FILE */
