/******************************************************************************
* File Name          : Me_ServoDriver.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.1
* Date               : 5/17/2013
* Description        : Class for Makeblock Electronic modules of Me-Servo 
                       Driver. The module can only be connected to the port 1, 
                       2 of Me - Base Shield. One module can drive two servos.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_ServoDriver.h"

Me_ServoDriver::Me_ServoDriver()
{
	servo1Pin = mePort[PORT_1].innersidePin;
	servo2Pin = mePort[PORT_1].outsidePin;
}

Me_ServoDriver::Me_ServoDriver(int portNum)
{
	if(portNum > 0 && portNum < 3)
	{
		servo1Pin = mePort[portNum].innersidePin;
		servo2Pin = mePort[portNum].outsidePin;
	}
}


uint8_t Me_ServoDriver::beginServo1()
{
		return this->servo1.attach(servo1Pin);
}

uint8_t Me_ServoDriver::beginServo1(int min, int max)
{
		return this->servo1.attach(servo1Pin, min, max);
}

uint8_t Me_ServoDriver::beginServo2()
{
		return this->servo2.attach(servo2Pin);
}

uint8_t Me_ServoDriver::beginServo2(int min, int max)
{
		return this->servo2.attach(servo2Pin, min, max);
}

void Me_ServoDriver::detachServos()
{
	servo1.detach();
	servo2.detach();
}

void Me_ServoDriver::detachServo1()
{
	servo1.detach();
}

void Me_ServoDriver::detachServo2()
{
	servo2.detach();
}

int Me_ServoDriver::readServo1()
{
	return servo1.read();
}

int Me_ServoDriver::readServo2()
{
	return servo2.read();
}

void Me_ServoDriver::writeServo1(int value)
{
	servo1.write(value);
}

void Me_ServoDriver::writeServo2(int value)
{
	servo2.write(value);
}

int Me_ServoDriver::readMicrosecondsServo1()
{
	return servo1.readMicroseconds();
}

int Me_ServoDriver::readMicrosecondsServo2()
{
	return servo2.readMicroseconds();
}

void Me_ServoDriver::writeMicrosecondsServo1(int value)
{
	servo1.writeMicroseconds(value);
}

void Me_ServoDriver::writeMicrosecondsServo2(int value)
{
	servo2.writeMicroseconds(value);
}
