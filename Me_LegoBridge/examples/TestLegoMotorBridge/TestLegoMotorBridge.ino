/*************************************************************************
* File Name          : TestMotorBridge_light.ino
* Author             : Eric
* Updated            : Eric
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Test for Makeblock Electronic modules of Me - Lego 
                       Motor Bridge for driving 2 Lego Motors. 
                       In this case the module can ONLY be connected to 
                       the PORT_1 and PORT_2 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include<Me_BaseShield.h>
#include<Me_I2cMaster.h>
#include<Me_LegoMotor.h>

// An instance of class for software master, using software I2C.
Me_LegoMotor legoMotor(PORT_1);

void setup(void)
{
    legoMotor.begin();
    Serial.begin(9600);           // start serial for output
}
void loop(void)
{
  legoMotor.Run(Speed_RPM_M1,100,Duration_Degrees_M1,720,Completion_Dont_Wait);        //Motor 1 run in RPM mode.
  legoMotor.Run(Speed_RPM_M2,100,Duration_Degrees_M2,720,Completion_Wait_For);        //Motor 2 run in RPM mode.
  delay(1000);
  legoMotor.Run(Speed_Power_M1,-100,Duration_Degrees_M1,720,Completion_Dont_Wait);        //Motor 1 run in Power mode.
  legoMotor.Run(Speed_Power_M2,-100,Duration_Degrees_M2,720,Completion_Wait_For);        //Motor 2 run in Power mode.
  delay(1000);
}
