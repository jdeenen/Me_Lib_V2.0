/******************************************************************************
* File Name          : Me_BaseShield.h
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

#include <Arduino.h>

#ifndef Me_BaseShield_h
#define Me_BaseShield_h

//PORT_1 and PORT_2 are for high power Me modules, like Me - Motor Driver and Me - Servo Driver.
//PORT_3 and PORT_4 are for digital Me modules, like Me - Line Finder and Me - Bluetooth.
//PORT_5, PORT_6, PORT_7 and PORT_8 are for analog and digital modules.
enum MePortOnBaseShield{PORT_1 = 1, PORT_2, PORT_3, PORT_4, PORT_5, PORT_6, PORT_7, PORT_8};

//the following pins are used by Me - Base Shield
#define ME_BASESHIELD_M1_DRC_PIN 7
#define ME_BASESHIELD_M1_SPEED_PIN 6
#define ME_BASESHIELD_M2_DRC_PIN 4
#define ME_BASESHIELD_M2_SPEED_PIN 5

#define NC -1

typedef struct {
  int outsidePin;
  int innersidePin;
}MePort_t;

extern MePort_t mePort[9];//mePort[0] is nonsense

class Me_BaseShield
{
public:
	Me_BaseShield();
	static void begin();
	
	void setMePort(int port, int outsidePinState = -1, int innersidePinState = -1);
	void setMePortOutsidePin(int port, int state);
	void setMePortInnersidePin(int port, int state);
	
	void readMePort(int port, int *outsidePinState = NULL, int *innersidePinState = NULL);
	int readMePortOutsidePin(int port);
	int readMePortInnersidePin(int port);
	
	void readAnalogMePort(int port, int *outsideADValue = NULL, int *innersideADValue = NULL);
	int readAnalogMePortOutsidePin(int port);
	int readAnalogMePortInnersidePin(int port);
};
#endif

