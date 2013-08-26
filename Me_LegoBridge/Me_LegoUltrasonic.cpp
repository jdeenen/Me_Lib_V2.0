/*
Name: Me_LegoUltrasonic.h
Desciption: Class for Makeblock Electronic modules of Me -  Lego Digital Bridge. The module is used to 
connect the NXT Ultrasonic sensor to Arduino. It can be connected to  PORT_3, PROT_4, PORT_6 of Me - Base Shield. 
Updated: by Steve, 2/19/2013
License:  CC-BY-SA 3.0
Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*/


#include "Me_LegoUltrasonic.h"

//default port is PORT_5
Me_LegoUltrasonic::Me_LegoUltrasonic():softI2cMaster(mePort[PORT_5].innersidePin, mePort[PORT_5].outsidePin)
{
	port = PORT_5;
}

Me_LegoUltrasonic::Me_LegoUltrasonic(int portNum):softI2cMaster(mePort[portNum].innersidePin, mePort[portNum].outsidePin)
{
	port = portNum;
}

void Me_LegoUltrasonic::begin()
{
	pinMode(mePort[port].innersidePin, OUTPUT);
	pinMode(mePort[port].outsidePin, OUTPUT);
	digitalWrite(mePort[port].innersidePin, HIGH);
	digitalWrite(mePort[port].outsidePin, HIGH);
}

int Me_LegoUltrasonic::read()
{

	  // issue a start condition, send device address and write direction bit
  if (!softI2cMaster.start(LEGO_ULTRASONIC_ADDR | I2C_WRITE)) return -1;

    // send the getting distance address
  if (!softI2cMaster.write(0x42)) return -1;

   // issue a repeated start condition, send device address and read direction bit
  if (!softI2cMaster.restart(LEGO_ULTRASONIC_ADDR | I2C_READ)) return -1;
  
  int count = 1;
  // read data from the ultrasonic module
  int distance = softI2cMaster.read(1);

  // issue a stop condition
  softI2cMaster.stop();
  
  return distance;
}

