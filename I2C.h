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
#include <project.h>
#include <math.h>

    #define TEMP_HUMID_SENSOR_ADDR      (0x44)  // Pg 9 DS

    #define MSB                         (0x24)  //Most Significant Bit is the same for all the conditions
    #define H_LSB                       (0x00)  //Least Significant Bit for High Repeatability
    #define M_LSB                       (0x0B)  //Least Significant Bit for Medium Repeatability
    #define L_LSB                       (0x16)  //Least Significant Bit for Low Repeatability
    #define HIGH                           (1)
    #define LOW                            (0)
    #define MSB_REP                      (0x27)
    #define LSB_REP                      (0x37)


    uint8 *Temp_Humid_ReadReg();
    
    void Temp_Humid_WriteReg(uint8 MSB_Value, uint8 LSB_Value);
    
    float Convert2Humidity(int Raw_Humi);
    float Convert2Temperature(int Raw_Temp);
    
    int Hexadecimal2Decimal(int Value);
    
    int Is_Param_Good(int Real_Parameter, int Lower_Limit, int Upper_Limit); 
    

/* [] END OF FILE */
