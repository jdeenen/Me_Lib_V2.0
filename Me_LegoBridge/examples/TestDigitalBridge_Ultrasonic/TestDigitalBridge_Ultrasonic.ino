/*************************************************************************
* File Name          : TestDigitalBridge_Ultrasonic.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Test for Makeblock Electronic modules of Me - Lego 
                       Digital Bridge for driving Lego Ultrasonic Sensor. 
                       The module can ONLY be connected to the PORT_3, 
                       PORT_4, PORT_5, PORT_6 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>
#include <Me_I2cMaster.h>
#include <Me_LegoUltrasonic.h>

// An instance of class for software master, using software I2C.
Me_LegoUltrasonic legoUltrasonic(PORT_5);

void setup(void)
{
    Serial.begin(9600);
    legoUltrasonic.begin();
}

void loop(void)
{
    Serial.println();
    int distance = legoUltrasonic.read();
    if(distance >=0)
    {
        Serial.print("Distance:");
        Serial.println(distance);
    }
    else
    {
        Serial.println("Read distance error!");
    }
    delay(1000);
}
