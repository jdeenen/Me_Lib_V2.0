/******************************************************************************
* File Name          : Me_ServoDriver.h
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

#include <Arduino.h>
#include <inttypes.h>
#include <Me_BaseShield.h>
#include <SoftwareServo.h>

#ifndef Me_SoftServoDriver_h
#define Me_SoftServoDriver_h
typedef uint8_t boolean;
typedef uint8_t byte;

class Me_SoftServoDriver
{
public:
	Me_SoftServoDriver();
	//portNum can only be 1 or 2
	Me_SoftServoDriver(int portNum);
	void Servos_begin();
	void Servo1_begin();
	void Servo2_begin();
	void detachServo1();
	void detachServo2();
	void detachAll();
	
	void writeServo1(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
	void writeServo2(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
	void writeServo1Microseconds(int value); // Write pulse width in microseconds 
	void writeServo2Microseconds(int value); // Write pulse width in microseconds 
	int readServo1();                        // returns current pulse width as an angle between 0 and 180 degrees
	int readServo2();                        // returns current pulse width as an angle between 0 and 180 degrees
	int readServo1Microseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
	int readServo2Microseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
	bool servo1Attached();                   // return true if this servo is attached, otherwise false 
	bool servo2Attached();                   // return true if this servo is attached, otherwise false 
  
private:
	int servo1Pin;
	int servo2Pin;
	int initialPos1;
	int initialPos2;
	SoftwareServo servo1;
	SoftwareServo servo2;
};
#endif

