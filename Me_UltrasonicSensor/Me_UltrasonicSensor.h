/******************************************************************************
* File Name          : Me_UltrasonicSensor.h
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Class for Makeblock Electronic modules of Me-Ultrasonic 
                       Sensor. The module can ONLY be connected to the PORT_3, 
                       PORT_4, PORT_5, PORT_6, PORT_7, PORT_8 of Me-Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <Me_BaseShield.h>

#ifndef Me_UltrasonicSensor_h
#define Me_UltrasonicSensor_h
	

class Me_UltrasonicSensor
{
public:
	Me_UltrasonicSensor();
	//portNum can ONLY be 3, 4, 5, 6, 7, 8
	Me_UltrasonicSensor(int portNum);
	void begin();
	long distanceCm();
	long distanceInch();

private:
	int signalPin;
	long measure();
	
};
#endif

