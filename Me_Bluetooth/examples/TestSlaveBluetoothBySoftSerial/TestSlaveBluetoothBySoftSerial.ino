/*************************************************************************
* File Name          : TestSlaveBluetoothBySoftSerial.ino
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.1
* Date               : 5/17/2013
* Description        : Example for Makeblock Electronic modules of Me -  
                       Bluetooth. The module can only be connected to the 
                       port 3, 4, 5, 6 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <SoftwareSerial.h>
#include <Me_Bluetooth.h>

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.
*/
Me_Bluetooth bluetooth(PORT_4);

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);
    Serial.println("Bluetooth Start!");
}

void loop()
{
    char inDat;
    char outDat;
    if(bluetooth.available())
    {
        inDat = bluetooth.read();
        Serial.print(inDat);
    }
    if(Serial.available())
    {
        outDat = Serial.read();
        bluetooth.write(outDat);
    }
}

