/******************************************************************************
* File Name          : Me_InfraredReceiverDecode.h
* Author             : Evan
* Updated            : Evan
* Version            : V0.2.1
* Date               : 05/16/2013
* Description        : Class for Makeblock Electronic modules of Me-InfraredReceiverDecode. 
                       The module can only be connected to the port 3, 4, 5, 6
                       of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <Me_BaseShield.h>
#include <SoftwareSerial.h>
#include <WString.h>

#ifndef Me_InfraredReceiverDecode_h
#define Me_InfraredReceiverDecode_h

#define NEC 1
#define RC5 0

// NEC Code table
#define IR_BUTTON_POWER 0x45
#define IR_BUTTON_MENU 0x47
#define IR_BUTTON_TEST 0x44
#define IR_BUTTON_PLUS 0x40
#define IR_BUTTON_RETURN 0x43
#define IR_BUTTON_PREVIOUS 0x07
#define IR_BUTTON_PLAY 0x15
#define IR_BUTTON_NEXT 0x09
#define IR_BUTTON_MINUS 0x19
#define IR_BUTTON_CLR 0x0D
#define IR_BUTTON_0 0x16
#define IR_BUTTON_1 0x0C
#define IR_BUTTON_2 0x18
#define IR_BUTTON_3 0x5E
#define IR_BUTTON_4 0x08
#define IR_BUTTON_5 0x1C
#define IR_BUTTON_6 0x5A
#define IR_BUTTON_7 0x42
#define IR_BUTTON_8 0x52
#define IR_BUTTON_9 0x4A

// RC5(PHILIPS) Code table



class Me_InfraredReceiverDecode
{
public:
	Me_InfraredReceiverDecode();
	//portNum can only be 3, 4, 5, 6
	Me_InfraredReceiverDecode(int portNum);
	void begin();
	char read();
	int available();
	char buttonState();
	void modeSwitch(char codeMode);
private:
	int port;
	int stPin;
	SoftwareSerial swSerial;
};
#endif

