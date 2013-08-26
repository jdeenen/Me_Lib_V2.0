/******************************************************************************
* File Name          : Me_LimitSwitch.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V0.1.0
* Date               : 5/22/2013
* Description        : Class for Makeblock Electronic modules of Me_LimitSwitch. 
                       The module can only be connected to the port 3, 4, 5, 6
                       (PORT_3,PORT_4,PORT_5,PORT_6) of Me - Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_LimitSwitch.h"

Me_LimitSwitch::Me_LimitSwitch()
{
	upPin = mePort[PORT_4].innersidePin;
	downPin = mePort[PORT_4].outsidePin;
}

Me_LimitSwitch::Me_LimitSwitch(int portNum)
{
	if(portNum > 2 && portNum < 7)
	{
		upPin = mePort[portNum].innersidePin;
		downPin = mePort[portNum].outsidePin;
	}
}

void Me_LimitSwitch::begin()
{
	pinMode(upPin, INPUT);
	pinMode(downPin, INPUT);
}

int Me_LimitSwitch::readUpPin()
{
	return(!digitalRead(upPin));
}

int Me_LimitSwitch::readDownPin()
{
	return(!digitalRead(downPin));
}

