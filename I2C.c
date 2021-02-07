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

#include <I2C.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


uint8 *Temp_Humid_ReadReg()
{
//    uint8 Write_Buf[1]  = {0};        //Buffer that will contain the register that will be read from
//    Write_Buf[0]        = Reg;
    
    uint8  Read_Buf[6];        // Buffer that will store the value read from the register
    uint8 *Ptr = Read_Buf;
    
    //Execute: Write The Addres in the Buffer and make sure we write all the bits
//    I2C_1_MasterWriteBuf(TEMP_HUMID_SENSOR_ADDR, (uint8 *)Write_Buf, 1, I2C_1_MODE_NO_STOP);
//    while((I2C_1_MasterStatus() & I2C_1_MSTAT_WR_CMPLT) == 0) {}
    
    
    // Execute: Read The Value in the Addres and make sure we read all the bits
    I2C_1_MasterReadBuf(TEMP_HUMID_SENSOR_ADDR, (uint8 *)Read_Buf, 6, I2C_1_MODE_COMPLETE_XFER);
    //while((I2C_1_MasterStatus() & I2C_1_MSTAT_RD_CMPLT) == 0) {}
   CyDelay(1000);

    //I2C_1_MasterReadByte(I2C_1_NAK_DATA);
    
    return Ptr;
}

void Temp_Humid_WriteReg(uint8 MSB_Value, uint8 LSB_Value)
{
    uint8 Write_Buf[2]  = {0};
   
   //Write_Buf[0]        = TEMP_HUMID_SENSOR_ADDR;           
   Write_Buf[0]        = MSB_Value;
   Write_Buf[1]        = LSB_Value;
    
 //   I2C_1_MasterSendStart(TEMP_HUMID_SENSOR_ADDR,0);
    I2C_1_MasterWriteBuf(TEMP_HUMID_SENSOR_ADDR, (uint8 *)Write_Buf, 2, I2C_1_MODE_COMPLETE_XFER );      //I2C_1_MODE_COMPLETE_XFER
 //   while((I2C_1_MasterStatus() & I2C_1_MSTAT_WR_CMPLT) == 0) {}
   // I2C_1_MasterSendStop();
  //CyDelay(1000);

    return;
}

int Hexadecimal2Decimal(int Value)
{
    char hex[17];
    sprintf(hex, "%i", Value);
    
    int Decimal_Num;
    int i   = 0;
    int val = 0;
    int len = 0;
    
    Decimal_Num = 0;
    
    
    len = strlen(hex);
    len--;
    
    for(i = 0; hex[i]!='\0'; i = i+1)
    {
        /* Find the decimal representation of hex[i] */
        if(hex[i]>='0' && hex[i]<='9')
        {
            val = hex[i] - 48;
        }
        else if(hex[i]>='a' && hex[i]<='f')
        {
            val = hex[i] - 97 + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F')
        {
            val = hex[i] - 65 + 10;
        }

        Decimal_Num += val * pow(16, len);
        len--;
    }
    return Decimal_Num;
}

float Convert2Temperature(int Raw_Temp)
{
    float Temperatur_Celsius = 0;
    
    Temperatur_Celsius = ((175*Raw_Temp)/(pow(2,16)-1)+23);
    
    return Temperatur_Celsius;
}

float Convert2Humidity(int Raw_Humi)
{
    float Humidity_Percent = 0;
    
    Humidity_Percent = ((100*Raw_Humi)/(pow(2,16)-1)+50);
    
    return Humidity_Percent;
}

int Is_Param_Good(int Real_Parameter, int Lower_Limit, int Upper_Limit)
{
    int Is_Good;
    
    if(Real_Parameter > Lower_Limit && Real_Parameter < Upper_Limit )
    {
        Is_Good = HIGH;
    }
    else
    {
        Is_Good = LOW;
    } 
    return Is_Good;
}




/* [] END OF FILE */
