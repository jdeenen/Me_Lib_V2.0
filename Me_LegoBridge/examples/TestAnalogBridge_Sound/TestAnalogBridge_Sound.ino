/*************************************************************************
* File Name          : TestAnalogBridge_Sound.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Test for Makeblock Electronic modules of Me - Lego 
                       Analog Bridge for driving Lego Sound Sensor. In 
                       this case the module can ONLY be connected to the 
                       PORT_5, PORT_6, PORT_7, PORT_8 of Me - Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>

Me_BaseShield baseShield;

void setup()
{
    Serial.begin(9600);
    baseShield.begin();
}

void loop()
{
    int rawSoundValue = baseShield.readAnalogMePortOutsidePin(PORT_8);
    Serial.print("Raw Sound value: ");
    Serial.println(rawSoundValue);

    delay(1000);
}

