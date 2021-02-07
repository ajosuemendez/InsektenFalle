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
#include <Wind_Direction.h>
#include <I2C.h>

int Get_Wind_Direction()
{
    int32 Integer;
  
    float32 Wind_Direction_Degrees;
    float32 Voltage_Ratio_Degree;
    
    
    Opamp_Start();
    ADC_DelSig_Start();
    
    ADC_DelSig_StartConvert();
    ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT);
    
    Integer = ADC_DelSig_GetResult32();                                 //Offset of 2700-2800?
    
    ADC_DelSig_StopConvert();
    ADC_DelSig_Stop();
    Opamp_Stop();
        
    Voltage_Ratio_Degree    = (5000/360);                             //The equivalent Voltage for 1 degree 
   

    Wind_Direction_Degrees       = (ADC_DelSig_CountsTo_mVolts(Integer)/Voltage_Ratio_Degree)-20;
     
    return Wind_Direction_Degrees;
}
/* [] END OF FILE */
