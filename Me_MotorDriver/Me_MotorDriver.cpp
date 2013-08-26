/******************************************************************************
* File Name          : Me_MotorDriver.cpp
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

#include "Me_MotorDriver.h"

Me_MotorDriver::Me_MotorDriver()
{
	drcPin = mePort[PORT_1].innersidePin;
	speedPin = mePort[PORT_1].outsidePin;
}

Me_MotorDriver::Me_MotorDriver(int portNum)
{
	if(portNum>0 && portNum < 3 )
	{
		drcPin = mePort[portNum].innersidePin;
		speedPin = mePort[portNum].outsidePin;
	}
}

void Me_MotorDriver::begin()
{
	pinMode(drcPin,OUTPUT);
	pinMode(speedPin,OUTPUT);
	digitalWrite(drcPin,HIGH);
	digitalWrite(speedPin,LOW);
}

void Me_MotorDriver::run(int speed)
{
	speed = speed>255? 255:speed;
	speed = speed<-255?-255:speed;

	if(speed>=0)
	{
		digitalWrite(drcPin,HIGH);
		analogWrite(speedPin,speed);
	}
	else
	{
		digitalWrite(drcPin,LOW);
		analogWrite(speedPin,-speed);	
	}
}

void Me_MotorDriver::stop()
{
	digitalWrite(speedPin,LOW);
}

