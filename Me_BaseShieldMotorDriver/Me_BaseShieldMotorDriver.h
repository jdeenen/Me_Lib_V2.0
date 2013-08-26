/******************************************************************************
* File Name          : Me_BaseShieldMotorDriver.h
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me-Base Shield 
                       Motor Driver.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <Me_BaseShield.h>

#ifndef Me_BaseShieldMotorDriver_h
#define Me_BaseShieldMotorDriver_h

class Me_BaseShieldMotorDriver
{
public:
	Me_BaseShieldMotorDriver();
	void begin();
	void runMotors(int M1Spd = 128, int M2Spd = 128);
	void runMotor1(int spd = 128);
	void runMotor2(int spd = 128);
	void stopMotors();
	void stopMotor1();
	void stopMotor2();
};
#endif

