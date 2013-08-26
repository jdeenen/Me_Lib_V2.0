/******************************************************************************
* File Name          : Me_LineFinder.cpp
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 12/11/2012
* Description        : Class for Makeblock Electronic modules of Me-LineFinder. 
                       The module can only be connected to the port 3, 4, 5, 6
                       (PORT_3,PORT_4,PORT_5,PORT_6) of Me - Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_LineFinder.h"

Me_LineFinder::Me_LineFinder()
{
	sensor1Pin = mePort[PORT_4].innersidePin;
	sensor2Pin = mePort[PORT_4].outsidePin;
}

Me_LineFinder::Me_LineFinder(int portNum)
{
	if(portNum > 2 && portNum < 7)
	{
		sensor1Pin = mePort[portNum].innersidePin;
		sensor2Pin = mePort[portNum].outsidePin;
	}
}

void Me_LineFinder::begin()
{
	pinMode(sensor1Pin, INPUT);
	pinMode(sensor2Pin, INPUT);
}

int Me_LineFinder::readSensor1()
{
	return(digitalRead(sensor1Pin));
}

int Me_LineFinder::readSensor2()
{
	return(digitalRead(sensor2Pin));
}

//return the state of two sensors: S1_IN_S2_IN, S1_IN_S2_OUT, S1_OUT_S2_IN or S1_OUT_S2_OUT
int Me_LineFinder::readSensors()
{
	int state = S1_IN_S2_IN;
	int s1State = digitalRead(sensor1Pin);
	int s2State = digitalRead(sensor2Pin);

	state = ((1&s1State)<<1)|s2State;

	return state;
}



