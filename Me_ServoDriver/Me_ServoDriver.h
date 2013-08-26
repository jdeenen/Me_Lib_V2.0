/******************************************************************************
* File Name          : Me_ServoDriver.h
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.1
* Date               : 5/17/2013
* Description        : Class for Makeblock Electronic modules of Me-Servo 
                       Driver. The module can only be connected to the port 1, 
                       2 of Me - Base Shield. One module can drive two servos.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <Servo.h>
#include <Me_BaseShield.h>

#ifndef Me_ServoDriver_h
#define Me_ServoDriver_h

class Me_ServoDriver
{
public:
	Me_ServoDriver();
	//portNum can only be 1 or 2
	Me_ServoDriver(int portNum);
	uint8_t beginServo1();
	uint8_t beginServo1(int min, int max);
	uint8_t beginServo2();
	uint8_t beginServo2(int min, int max);
	void detachServos();
	void detachServo1();
	void detachServo2();
	int readServo1();                        // returns current pulse width as an angle between 0 and 180 degrees
	int readServo2();                        // returns current pulse width as an angle between 0 and 180 degrees
	void writeServo1(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
	void writeServo2(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
	int readMicrosecondsServo1();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
	int readMicrosecondsServo2();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
	void writeMicrosecondsServo1(int value); // Write pulse width in microseconds 
	void writeMicrosecondsServo2(int value); // Write pulse width in microseconds 
private:
	int servo1Pin;
	int servo2Pin;

	Servo servo1;
	Servo servo2;
};
#endif

