/*************************************************************************
* File Name          : TestAnalogBridge_Touch.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Test for Makeblock Electronic modules of Me - Lego 
                       Analog Bridge for driving Lego Touch Sensor. In 
                       this case the module can ONLY be connected to the 
                       PORT_3, PORT_4, PORT_5, PORT_6, PORT_7, PORT_8 of 
                       Me - Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>

Me_BaseShield baseShield;
int state = HIGH;

void setup()
{
    Serial.begin(9600);
    baseShield.begin();
}

void loop()
{
    int newState  = baseShield.readMePortOutsidePin(PORT_8);   	
    if(state != newState)
    {
        state = newState;
        if(state == LOW)
        {
            Serial.println("Touched");
        }
        else
        {
            Serial.println("Untouched");
        }
    }
}

