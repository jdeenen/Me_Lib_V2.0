/******************************************************************************
* File Name          : Me_LineFinder.h
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

#include <Arduino.h>
#include <Me_BaseShield.h>

#ifndef Me_LineFinder_h
#define Me_LineFinder_h
	
//states of two sensors
#define	S1_IN_S2_IN 0x00 //sensor1 and sensor2 are both inside of black line
#define	S1_IN_S2_OUT 0x01 //sensor1 is inside of black line and sensor is outside of black line
#define	S1_OUT_S2_IN 0x02 //sensor1 is outside of black line and sensor is inside of black line 
#define	S1_OUT_S2_OUT 0x03 //sensor1 is outside of black line and sensor is outside of black line


class Me_LineFinder
{
public:
	Me_LineFinder();
	//portNum can only be 3, 4, 5, 6, 7
	Me_LineFinder(int portNum);
	void begin();
	int readSensor1();//HIGH when receiving reflective signal, LOW when finding black line.
	int readSensor2();//HIGH when receiving reflective signal, LOW when finding black line.
  int readSensors();
	   
private:
	int sensor1Pin;
	int sensor2Pin;
	
};
#endif

