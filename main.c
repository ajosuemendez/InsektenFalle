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
#include "project.h"
#include <SleepMode.h>
#include <I2C.h>
#include <Wind_Direction.h>

#define OFF     0
#define ON      1

const int State_Motor_Calm = 4;
const int State_Motor_Turn = 5;

int CurrentState_MotorCheckUp = 4;



CY_ISR(Input_LS1_Handler)
    {
        Pin_Out_To_Rel_HV_Write(HIGH); 
        CyDelay(2000);
        Pin_Out_To_Rel_HV_Write(LOW);
        CyDelay(1000);   
              
        Input_LS1_Kef_ClearInterrupt();
    }




int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Input_LS1_Kef_Int_StartEx(Input_LS1_Handler);
   
        

    
    
    uint8 *MyData;
    uint8 Temp_MSB;
    uint8 Temp_LSB;
    uint8 Humidity_MSB;
    uint8 Humidity_LSB;
    
    uint16 Temp16;
    uint16 Humid16;
    
    //int Raw_Decimal_Temp;
   // int Raw_Decimal_Humid;
    
    int Wind_Direction;
    float Real_Temperature_Celsius;
    float Real_Humidity_Percentage;
    
    int Is_Wind_Good;
    int Is_Temp_Good;
    int Is_Humid_Good;
 

    for(;;)
    { 



            
                //Check the level
                int Is_Motor_On = LOW;
                do
                {
                    switch(CurrentState_MotorCheckUp)
                    {
                        case 4:
                        if(Input_LS2_Voll_Read() == LOW)
                        {
                            Pin_Out_To_Rel_Mot_Write(HIGH);
                            CyDelay(100);
                            Is_Motor_On = ON;
                            CurrentState_MotorCheckUp = State_Motor_Turn;
                        }
                        else
                        {
                            Pin_Out_To_Rel_Mot_Write(LOW);
                            Is_Motor_On = LOW;
                            CurrentState_MotorCheckUp = State_Motor_Calm;
                        }
                        break;
                        
                        case 5:
                        
                        if(Input_LS2_Voll_Read() == HIGH && Input_Micro_Switch_Read() == LOW ) // For testing: Test_Input_Micro_Switch_Read should be written otherwise just Input_Micro_Switch_Read()
                        {
                            Pin_Out_To_Rel_Mot_Write(LOW);
                            CyDelay(100);
                            Is_Motor_On = LOW;
                            CurrentState_MotorCheckUp = State_Motor_Calm;
                        }
                        else
                        {
                            Pin_Out_To_Rel_Mot_Write(HIGH);
                            Is_Motor_On = ON;
                            CurrentState_MotorCheckUp = State_Motor_Turn;
                        }
                        break;
                    }
                }while(Is_Motor_On == ON);
                
                
                //Do measurements
                
                
              Temp_Humid_WriteReg(MSB , H_LSB );                            //Telling The sensor What kind of measurement we want by giving the corresponding Sensor Address
              MyData = Temp_Humid_ReadReg();                                     //Reading the Data from the Sensor and Storing it in a pointer (Array) 
                
                Temp_MSB = MyData[0];
                Temp_LSB = MyData[1];
                
                
                Humidity_MSB = MyData[3];
                Humidity_LSB = MyData[4];
               
                
                Temp16  =  ((uint8) Temp_MSB) << 8 | Temp_LSB;                               //Creeating a 16 Bit Integer (Adding MSB 8 Bits With the LSB 8 Bits together)
                Humid16 =  ((uint8) Humidity_MSB) << 8 | Humidity_LSB;                       //Creeating a 16 Bit Integer (Adding MSB 8 Bits With the LSB 8 Bits together)
                
                
                //Raw_Decimal_Temp  = Hexadecimal2Decimal(Temp16);                                    //Converting Converting the Hexadecimal Data into Decimal Data 
                //Raw_Decimal_Humid = Hexadecimal2Decimal(Humid16);                                   //Converting Converting the Hexadecimal Data into Decimal Data
                
                Real_Temperature_Celsius = Convert2Temperature(Temp16);                   //Converting Raw Data into Useful Data
                Real_Humidity_Percentage = Convert2Humidity(Humid16);                     //Converting Raw Data into Useful Data
                
                Pin_Out_To_Wind_Write(HIGH);
                Wind_Direction = Get_Wind_Direction();
                CyDelay(3000);
                //Pin_Out_To_Wind_Write(LOW);
                
                
                Is_Wind_Good  = Is_Param_Good(Wind_Direction, 180, 360); 
                Is_Temp_Good  = Is_Param_Good(Real_Temperature_Celsius, 10, 35);                    // Arguments(Temperature, Lower_Limit, Upper_Limit)
                Is_Humid_Good = Is_Param_Good(Real_Humidity_Percentage, 20, 100);                   // Arguments(Humidity, Lower_Limit, Upper_Limit)
                
                if(Is_Wind_Good == HIGH && Is_Temp_Good == HIGH && Is_Humid_Good == HIGH)
                {
                    Pin_Out_To_WP_Write(HIGH);
                    CyDelay(3000);
                    Pin_Out_To_WP_Write(LOW);
                }
                
                
                //Go back to Sleep
                //GoSleepWTC(WakingUp_Interval_Time);
                
                Ouput_Led_Write(HIGH);
                CyDelay(1000);
                Ouput_Led_Write(LOW);
                CyDelay(1000);              //180mA in Sleep 
                

     
    }
}

/* [] END OF FILE */
