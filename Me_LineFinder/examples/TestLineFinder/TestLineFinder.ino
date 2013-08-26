/*************************************************************************
* File Name          : TestLineFinder.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.1
* Date               : 5/27/2013
* Description        : Example for Makeblock Electronic modules of Me - 
                       Line Finder. The module can only be connected to 
                       the PORT_3, PORT_4, PORT_5, and PORT_6 of Me - 
                       Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_LineFinder.h>

Me_LineFinder lineFinder(PORT_3); //Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield.

void setup()
{
    Serial.begin(9600);
    lineFinder.begin();
}

void loop()
{
    int sensorState = lineFinder.readSensors();
    switch(sensorState)
    {
        case S1_IN_S2_IN:Serial.println("Sensor 1 and 2 are inside of black line");break;
        case S1_IN_S2_OUT:Serial.println("Sensor 2 is outside of black line");break;
        case S1_OUT_S2_IN:Serial.println("Sensor 1 is outside of black line");break;
        case S1_OUT_S2_OUT:Serial.println("Sensor 1 and 2 are outside of black line");break;
        default:break;
    }
    delay(200);
}

