/*
Name: Me_LegoUltrasonic.h
Desciption: Class for Makeblock Electronic modules of Me -  Lego Digital Bridge. The module is used to 
connect the NXT Ultrasonic sensor to Arduino. It can be connected to  PORT_3, PROT_4, PROT_5, PORT_6 of Me - Base Shield. 
Updated: by Steve, 2/19/2013
License:  CC-BY-SA 3.0
Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*/

#include <Arduino.h>
#include <Me_BaseShield.h>
#include <Me_I2cMaster.h>


#ifndef Me_LegoUltrasonic_h
#define Me_LegoUltrasonic_h
	
#define LEGO_ULTRASONIC_ADDR 0x02


class Me_LegoUltrasonic
{
public:
	Me_LegoUltrasonic();
	//portNum can only be 3, 4, 5, 6
	Me_LegoUltrasonic(int portNum);
	void begin();
	int read();
private:
	int port;
	Me_SoftI2cMaster softI2cMaster;
};
#endif

