/*************************************************************************
* File Name          : TestMotorDriver.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.1
* Date               : 5/18/2013
* Description        : Test for Makeblock Electronic modules of Me -Motor 
                       Driver. The module can only be connected to the 
                       PORT_1, PORT_2 of Me - Base Shield.. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_MotorDriver.h>

Me_MotorDriver motorDriver1(PORT_1);
Me_MotorDriver motorDriver2(PORT_2);

uint8_t motorSpeed = 100;

void setup()
{
	motorDriver1.begin();
	motorDriver2.begin();
}

void loop()
{
	motorDriver1.run(motorSpeed); // value: between -255 and 255.
	motorDriver2.run(motorSpeed); // value: between -255 and 255.
	delay(2000);
	motorDriver1.run(-motorSpeed);
	motorDriver2.run(-motorSpeed);
	delay(2000);
	motorDriver1.stop();
	motorDriver2.stop();
	delay(2000);
}

