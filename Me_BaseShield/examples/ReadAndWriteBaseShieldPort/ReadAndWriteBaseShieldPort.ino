/*************************************************************************
* File Name          : ReadAndWriteBaseShieldPort.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 11/30/2012
* Description        : Makeblock Electronic modules of Base Shield. Pin 4, 
                       5, 6, and 7 are used by the onboard motor driver 
                       chip.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>

Me_BaseShield baseShield;

void setup()
{
    baseShield.begin();
}

void loop()
{
    int portNo;
    for(portNo = PORT_1; portNo <= PORT_8; portNo++)
    {
        baseShield.setMePort(portNo, HIGH, HIGH);
    }
    delay(200);
    for(portNo = PORT_1; portNo <= PORT_8; portNo++)
    {
        baseShield.setMePort(portNo, LOW, LOW);
    }
    delay(200);
}
