/******************************************************************************
* File Name          : Me_SoftServoDriver.cpp
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me-Servo 
                       Driver. The module can only be connected to the port 1, 
                       2 of Me - Base Shield. One module can drive two servos.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/
extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <avr/interrupt.h>
}
#include "Me_SoftServoDriver.h"
#define usToTicks(_us)    (( clockCyclesPerMicrosecond()* _us) / 128)
Me_SoftServoDriver::Me_SoftServoDriver()
{
	servo1Pin = mePort[PORT_1].innersidePin;
	servo2Pin = mePort[PORT_1].outsidePin;
	initialPos1 = 90;
	initialPos2 = 90;
}

Me_SoftServoDriver::Me_SoftServoDriver(int portNum)
{
	if(portNum > 0 && portNum < 3)
	{
		servo1Pin = mePort[portNum].innersidePin;
		servo2Pin = mePort[portNum].outsidePin;
	}
	initialPos1 = 90;
	initialPos2 = 90;
}

void Me_SoftServoDriver::Servos_begin()
{
	//Me_BaseShield::begin();
	servo1.attach(servo1Pin);
	servo2.attach(servo2Pin);
	writeServo1(initialPos1);
	writeServo2(initialPos2);
}

void Me_SoftServoDriver::Servo1_begin()
{
	//Me_BaseShield::begin();
	servo1.attach(servo1Pin);
	//pinMode(servo1Pin,OUTPUT);
}

void Me_SoftServoDriver::Servo2_begin()
{
	//Me_BaseShield::begin();
	servo2.attach(servo2Pin);
	//pinMode(servo2Pin,OUTPUT);
}

void Me_SoftServoDriver::detachServo1()
{
	servo1.detach();
}

void Me_SoftServoDriver::detachServo2()
{
	servo2.detach();
}

void Me_SoftServoDriver::detachAll()
{
	servo1.detach();
	servo2.detach();
}

void Me_SoftServoDriver::writeServo1(int value)
{
	servo1.write(value);
}

void Me_SoftServoDriver::writeServo2(int value)
{
	servo2.write(value);
}

void Me_SoftServoDriver::writeServo1Microseconds(int value)
{
	//servo1.writeMicroseconds(value);
}

void Me_SoftServoDriver::writeServo2Microseconds(int value)
{
	//servo2.writeMicroseconds(value);
}

int Me_SoftServoDriver::readServo1()
{
	return servo1.read();
}

int Me_SoftServoDriver::readServo2()
{
	return servo2.read();
}

int Me_SoftServoDriver::readServo1Microseconds()
{
	return 0;//servo1.readMicroseconds();
}

int Me_SoftServoDriver::readServo2Microseconds()
{
	return 0;//servo2.readMicroseconds();
}

bool Me_SoftServoDriver::servo1Attached()
{
	return servo1.attached();
}

bool Me_SoftServoDriver::servo2Attached()
{
	return servo2.attached();
}
 
