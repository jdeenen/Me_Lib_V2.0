/*************************************************************************
* File Name          : TestLimitSwitch.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 5/27/2013
* Description        : Example for Makeblock Electronic modules of 
                       Me-LimitSwitch. The module can only be connected to 
                       the PORT_3, PORT_4, PORT_5, and PORT_6 of Me - 
                       Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_LimitSwitch.h>

Me_LimitSwitch limitSwitch(PORT_4); //Me_LimitSwitch module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield.

void setup()
{
    limitSwitch.begin();
    Serial.begin(9600);
    Serial.println("Start.");
}

void loop()
{
   if(limitSwitch.readUpPin()) //If the limit switch is up, the "readUpPin" return value is true.
   {
     Serial.println("State: UP.");
     delay(5);  //We have designed the hardware disappears shakes circuit, add software disappears shakes to improve reliability.
     //Delay time is usually 2 to 10 ms.
     while(limitSwitch.readUpPin()); //Repeat check the switch state, until released.
   }
   if(limitSwitch.readDownPin()) //If the limit switch is down, the "readDownPin" return value is true.
   {
     Serial.println("State: DOWN.");
     delay(5);
     while(limitSwitch.readDownPin());
   }
   
}

