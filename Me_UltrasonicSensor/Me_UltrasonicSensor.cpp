/******************************************************************************
* File Name          : Me_UltrasonicSensor.cpp
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Class for Makeblock Electronic modules of Me-Ultrasonic 
                       Sensor. The module can ONLY be connected to the PORT_3, 
                       PORT_4, PORT_6, PORT_7, PORT_8 of Me-Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_UltrasonicSensor.h"

Me_UltrasonicSensor::Me_UltrasonicSensor()
{
	signalPin = mePort[PORT_7].outsidePin;
}

Me_UltrasonicSensor::Me_UltrasonicSensor(int portNum)
{
	if(portNum > 2 && portNum < 9)
	{
		signalPin = mePort[portNum].outsidePin;
	}
}

void Me_UltrasonicSensor::begin()
{
	
}

long Me_UltrasonicSensor::distanceCm()
{
	long distance = measure();
	return ((distance/29)>>1);
}

long Me_UltrasonicSensor::distanceInch()
{
	long distance = measure();
	return ((distance/74)>>1);
}

long Me_UltrasonicSensor::measure()
{
	long duration;
	pinMode(signalPin, OUTPUT);
	digitalWrite(signalPin, LOW);
	delayMicroseconds(2);
	digitalWrite(signalPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(signalPin,LOW);
	pinMode(signalPin,INPUT);
	duration = pulseIn(signalPin,HIGH);
	return duration;
}

