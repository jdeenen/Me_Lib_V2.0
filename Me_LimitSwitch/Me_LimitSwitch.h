/******************************************************************************
* File Name          : Me_LimitSwitch.h
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

#include <Arduino.h>
#include <Me_BaseShield.h>

#ifndef Me_LimitSwitch_h
#define Me_LimitSwitch_h

class Me_LimitSwitch
{
public:
	Me_LimitSwitch();
	//portNum can only be 3, 4, 5, 6
	Me_LimitSwitch(int portNum);
	void begin();
	int readUpPin();//HIGH when the switch is UP.
	int readDownPin();//HIGH when the switch is DOWN.

private:
	int upPin;
	int downPin;
	
};
#endif

