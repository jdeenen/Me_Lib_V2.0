/******************************************************************************
* File Name          : Me_BaseShield.cpp
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me-Base Shield.
                       Pin 4, 5, 6, and 7 are used by the onboard motor driver 
                       chip. Others are brought to 8 RJ10 connectors.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_BaseShield.h"

MePort_t mePort[9] = {{NC, NC}, {11, 10}, {3, 9}, {13, 12}, {2, 8},
                      {19, 18}, {17, 16}, {15,NC}, {14, NC}}; 

Me_BaseShield::Me_BaseShield()
{
}

void Me_BaseShield::begin()
{
	pinMode(ME_BASESHIELD_M1_DRC_PIN,OUTPUT);
	pinMode(ME_BASESHIELD_M2_DRC_PIN,OUTPUT);
	pinMode(ME_BASESHIELD_M1_SPEED_PIN,OUTPUT);
	pinMode(ME_BASESHIELD_M2_SPEED_PIN,OUTPUT);
	digitalWrite(ME_BASESHIELD_M1_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M2_DRC_PIN,HIGH);
	digitalWrite(ME_BASESHIELD_M1_SPEED_PIN,LOW);
	digitalWrite(ME_BASESHIELD_M2_SPEED_PIN,LOW);

	pinMode(mePort[PORT_1].innersidePin, OUTPUT);
	pinMode(mePort[PORT_1].outsidePin, OUTPUT);
	pinMode(mePort[PORT_2].innersidePin, OUTPUT);
	pinMode(mePort[PORT_2].outsidePin, OUTPUT);
	digitalWrite(mePort[PORT_1].innersidePin,HIGH);
	digitalWrite(mePort[PORT_1].outsidePin,LOW);
	digitalWrite(mePort[PORT_2].innersidePin,HIGH);
	digitalWrite(mePort[PORT_2].outsidePin,LOW);

	for(int i = PORT_3; i <= PORT_6; i++)
	{
		pinMode(mePort[i].innersidePin, INPUT);
		pinMode(mePort[i].outsidePin, INPUT);	
	}
	
	pinMode(mePort[PORT_7 ].outsidePin, INPUT);	
	pinMode(mePort[PORT_8 ].outsidePin, INPUT);	
	
	//Serial.begin(9600);
}

void Me_BaseShield::setMePort(int port, int outsidePinState, int innersidePinState)
{	
	if(port>=PORT_1 && port <= PORT_6)
	{
		pinMode(mePort[port].outsidePin, OUTPUT);
		pinMode(mePort[port].innersidePin, OUTPUT);
		digitalWrite(mePort[port].outsidePin, outsidePinState);
		digitalWrite(mePort[port].innersidePin, innersidePinState);
	}
	else if(port == PORT_7 || port == PORT_8)
	{
		pinMode(mePort[port].outsidePin, OUTPUT);
		digitalWrite(mePort[port].outsidePin, outsidePinState);
	}
}

void Me_BaseShield::setMePortOutsidePin(int port, int state)
{
	if(port>=PORT_1 && port <= PORT_8)
	{
		pinMode(mePort[port].outsidePin, OUTPUT);
		digitalWrite(mePort[port].outsidePin, state);
	}
}

void Me_BaseShield::setMePortInnersidePin(int port, int state)
{
	if(port>=PORT_1 && port <= PORT_6)
	{
		pinMode(mePort[port].innersidePin, OUTPUT);
		digitalWrite(mePort[port].innersidePin, state);
	}
}
	
void Me_BaseShield::readMePort(int port, int *outsidePinState, int *innersidePinState)
{
	if(port>=PORT_1 && port <= PORT_6)
	{
		pinMode(mePort[port].outsidePin, INPUT);
		pinMode(mePort[port].innersidePin, INPUT);
		*outsidePinState = digitalRead(mePort[port].outsidePin);
		*innersidePinState = digitalRead(mePort[port].innersidePin);
	}
	else if(port == PORT_7 || port == PORT_8)
	{
		pinMode(mePort[port].outsidePin, INPUT);
		*outsidePinState = digitalRead(mePort[port].outsidePin);
	}
}

int Me_BaseShield::readMePortOutsidePin(int port)
{
	if(port>=PORT_1 && port <= PORT_8)
	{
		pinMode(mePort[port].outsidePin, INPUT);
		return digitalRead(mePort[port].outsidePin);
	}
	else
	{
		return -1;
	}
}

int Me_BaseShield::readMePortInnersidePin(int port)
{
	if(port>=PORT_1 && port <= PORT_6)
	{
		pinMode(mePort[port].innersidePin, INPUT);
		return digitalRead(mePort[port].innersidePin);
	}
	else
	{
		return -1;
	}
}
	
void Me_BaseShield::readAnalogMePort(int port, int *outsideADValue, int *innersideADValue)
{
	if(port>=PORT_5 && port <= PORT_6)
	{
		*outsideADValue = analogRead(mePort[port].outsidePin - 14);
		*innersideADValue = analogRead(mePort[port].innersidePin - 14);
	}
	else if(port == PORT_7 || port == PORT_8)
	{
		*outsideADValue = analogRead(mePort[port].outsidePin - 14);
	}
}

int Me_BaseShield::readAnalogMePortOutsidePin(int port)
{
	if(port>=PORT_5 && port <= PORT_8)
	{
		return analogRead(mePort[port].outsidePin - 14);
	}
	else
	{
		return -1;
	}
}

int Me_BaseShield::readAnalogMePortInnersidePin(int port)
{
	if(port>=PORT_5 && port <= PORT_6)
	{
		return analogRead(mePort[port].innersidePin - 14);
	}
	else
	{
		return -1;
	}
}


