/******************************************************************************
* File Name          : Me_BaseShieldMotorDriver.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me-Base Shield 
                       Motor Driver.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_BaseShieldMotorDriver.h"
Me_BaseShieldMotorDriver::Me_BaseShieldMotorDriver()
{
}

void Me_BaseShieldMotorDriver::begin()
{
	pinMode(ME_BASESHIELD_M1_DRC_PIN,OUTPUT);
	pinMode(ME_BASESHIELD_M2_DRC_PIN,OUTPUT);
	pinMode(ME_BASESHIELD_M1_SPEED_PIN,OUTPUT);
	pinMode(ME_BASESHIELD_M2_SPEED_PIN,OUTPUT);
	digitalWrite(ME_BASESHIELD_M1_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M2_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M1_SPEED_PIN,LOW);
	digitalWrite(ME_BASESHIELD_M2_SPEED_PIN,LOW);
}

void Me_BaseShieldMotorDriver::runMotors(int M1Spd, int M2Spd)	// value: between -255 and 255.
{
	runMotor1(M1Spd);
	runMotor2(M2Spd);
}

void Me_BaseShieldMotorDriver::runMotor1(int spd)	// value: between -255 and 255.
{
	spd = spd >  255?  255:spd;
	spd = spd < -255? -255:spd;

	if(spd >= 0)
	{
		digitalWrite(ME_BASESHIELD_M1_DRC_PIN,HIGH);
		analogWrite(ME_BASESHIELD_M1_SPEED_PIN,spd);
	}
	else
	{
		digitalWrite(ME_BASESHIELD_M1_DRC_PIN,LOW);
		analogWrite(ME_BASESHIELD_M1_SPEED_PIN,-spd);
	}
}

void Me_BaseShieldMotorDriver::runMotor2(int spd)	// value: between -255 and 255.
{
	spd = spd >  255?  255:spd;
	spd = spd < -255? -255:spd;

	if(spd >= 0)
	{
		digitalWrite(ME_BASESHIELD_M2_DRC_PIN,HIGH);
		analogWrite(ME_BASESHIELD_M2_SPEED_PIN,spd);
	}
	else
	{
		digitalWrite(ME_BASESHIELD_M2_DRC_PIN,LOW);
		analogWrite(ME_BASESHIELD_M2_SPEED_PIN,-spd);
	}
}

void Me_BaseShieldMotorDriver::stopMotors()
{
	digitalWrite(ME_BASESHIELD_M1_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M2_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M1_SPEED_PIN,LOW);
	digitalWrite(ME_BASESHIELD_M2_SPEED_PIN,LOW);
}

void Me_BaseShieldMotorDriver::stopMotor1()
{
	digitalWrite(ME_BASESHIELD_M1_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M1_SPEED_PIN,LOW);
}

void Me_BaseShieldMotorDriver::stopMotor2()
{
	digitalWrite(ME_BASESHIELD_M2_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M2_SPEED_PIN,LOW);
}

