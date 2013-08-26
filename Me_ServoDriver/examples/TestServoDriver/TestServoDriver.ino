/*************************************************************************
* File Name          : TestServoDriver.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.1
* Date               : 5/17/2013
* Description        : Test for Makeblock Electronic modules of Me -Servo 
                       Driver. The module can only be connected to the 
                       port 1, 2 of Me - Base Shield. One module can drive 
                       two servos.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_ServoDriver.h>
#include <Me_BaseShield.h>
#include <Servo.h>

/*
Class Me_ServoDriver has most of the functions from class Servo, 
see Me_ServoDriver.h for more details.
*/
Me_ServoDriver servoDriver(PORT_1);//can ONLY be PORT_1,PORT_2

int pos1 = 0;
int pos2 = 180;
void setup()
{
    servoDriver.beginServo1();
    servoDriver.beginServo2();
}

void loop()
{
    servoDriver.beginServo1();
    servoDriver.writeServo1(pos1);
    delay(1000);  // Wait for the servo rotation to the set position
    servoDriver.writeServo1(pos2);
    delay(1000);  // Wait for the servo rotation to the set position
    // Release the servo, not locked position.next.
    servoDriver.detachServo1();// Next control servo, must call the "begin" function again.
    delay(1000);
    
    servoDriver.writeServo2(pos1);
    delay(1000);  // Wait for the servo rotation to the set position
    servoDriver.writeServo2(pos2);
    delay(1000);  // Wait for the servo rotation to the set position
       
}
