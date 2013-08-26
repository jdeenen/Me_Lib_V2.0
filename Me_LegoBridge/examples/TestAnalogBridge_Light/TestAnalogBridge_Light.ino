/*************************************************************************
* File Name          : TestAnalogBridge_light.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Test for Makeblock Electronic modules of Me - Lego 
                       Analgo Bridge for driving Lego Ultrasonic Sensor. 
                       In this case the module can ONLY be connected to 
                       the PORT_5, PORT_6 of Me - Base Shield.
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
  int rawLightValue = getEnvironmentLight(PORT_6);//the brighter, the smaller
  Serial.print("Raw Environment light value: ");
  Serial.println(rawLightValue);
  
  delay(1000);
  int rawReflectiveLightValue = getReflectiveLight(PORT_6);
  Serial.print("Reflective light: ");
  Serial.println(rawReflectiveLightValue);
  Serial.println();

  delay(1000);
}

int getEnvironmentLight(int portNum)
{
  //turn off the LED on the Lego Light Sensor
  baseShield.setMePortInnersidePin(portNum, LOW);
  delay(100);//delay some time after turning off the LED
  return (baseShield.readAnalogMePortOutsidePin(portNum));

}

int getReflectiveLight(int portNum)
{
  //turn on the LED on the Lego Light Sensor
  baseShield.setMePortInnersidePin(portNum, HIGH);
  delay(200);//delay some time after turning on the LED
  return (baseShield.readAnalogMePortOutsidePin(portNum));
}

