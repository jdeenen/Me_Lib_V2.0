/******************************************************************************
* File Name          : Me_MotorDriver.h
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/17/2013
* Description        : Class for Makeblock Electronic modules of Me-Motor 
                       Driver. The module can only be connected to the PORT_1, 
                       PORT_2 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <Me_BaseShield.h>

#ifndef Me_MotorDriver_h
#define Me_MotorDriver_h

class Me_MotorDriver
{
public:
	Me_MotorDriver();
	//portNum can ONLY be PORT_1 or PORT_2
	Me_MotorDriver(int portNum);
	void begin();
	//speed - 0->lowest, 255->fastest clockwise, -255 -> fastest anticlockwise
	void run(int speed);
	void stop();
	
private:
	uint8_t drcPin;
	uint8_t speedPin;
	
};
#endif

