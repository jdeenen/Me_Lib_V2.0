/******************************************************************************
* File Name          : Me_InfraredReceiverDecode.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V0.2.1
* Date               : 05/16/2013
* Description        : Class for Makeblock Electronic modules of Me-InfraredReceiverDecode. 
                       The module can only be connected to the port 3, 4, 6
                       of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_InfraredReceiverDecode.h"

//default port is 6
Me_InfraredReceiverDecode::Me_InfraredReceiverDecode():swSerial(mePort[PORT_6].outsidePin, NULL)
{
	port = PORT_6;
	stPin = mePort[PORT_6].innersidePin;
}

Me_InfraredReceiverDecode::Me_InfraredReceiverDecode(int portNum):swSerial(mePort[portNum].outsidePin, NULL)
{
	port = portNum;
	if(portNum > 2 && portNum < 7)
	{
		stPin = mePort[portNum].innersidePin;
	}
}

void Me_InfraredReceiverDecode::begin()
{
	pinMode(stPin, INPUT); // button state
	pinMode(mePort[port].outsidePin, INPUT);
	if(port > 2 && port < 7)
	{
		swSerial.begin(9600);
	}
}

char Me_InfraredReceiverDecode::read()
{
	return(swSerial.read());
}

int Me_InfraredReceiverDecode::available()
{
	return(swSerial.available());
}

char Me_InfraredReceiverDecode::buttonState()	// Not available in Switching mode
{
	return(!digitalRead(stPin));
}

void Me_InfraredReceiverDecode::modeSwitch(char codeMode)	// Not available by default mode 
{
	if(codeMode) digitalWrite(stPin,HIGH);
	else digitalWrite(stPin,LOW);
}
