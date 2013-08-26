/*************************************************************************
* File Name          : TestInfraredReceiverDecode.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 05/16/2013
* Description        : Example for Makeblock Electronic modules of Me -  
                       InfraredReceiverDecode. The module can only be connected to the 
                       port 3, 4, 5, 6 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <SoftwareSerial.h>
#include <Me_InfraredReceiverDecode.h>

Me_InfraredReceiverDecode infraredReceiverDecode(PORT_6);

void setup()
{
    Serial.begin(9600);
    infraredReceiverDecode.begin();
    Serial.println("InfraredReceiverDecode Start!");
}

void loop()
{
    if(infraredReceiverDecode.available())
    {
        switch(infraredReceiverDecode.read())
        {
            case IR_BUTTON_POWER: printButtonState("Press Power.");break;
            case IR_BUTTON_MENU: printButtonState("Press Menu.");break;
            case IR_BUTTON_TEST: printButtonState("Press Test.");break;
            case IR_BUTTON_PLUS: printButtonState("Press Plus.");break;
            case IR_BUTTON_RETURN: printButtonState("Press Return.");break;
            case IR_BUTTON_PREVIOUS: printButtonState("Press Previous.");break;
            case IR_BUTTON_PLAY: printButtonState("Press Play.");break;
            case IR_BUTTON_NEXT: printButtonState("Press Next.");break;
            case IR_BUTTON_MINUS: printButtonState("Press Minus.");break;
            case IR_BUTTON_CLR: printButtonState("Press Clr.");break;
            case IR_BUTTON_0: printButtonState("Press 0.");break;
            case IR_BUTTON_1: printButtonState("Press 1.");break;
            case IR_BUTTON_2: printButtonState("Press 2.");break;
            case IR_BUTTON_3: printButtonState("Press 3.");break;
            case IR_BUTTON_4: printButtonState("Press 4.");break;
            case IR_BUTTON_5: printButtonState("Press 5.");break;
            case IR_BUTTON_6: printButtonState("Press 6.");break;
            case IR_BUTTON_7: printButtonState("Press 7.");break;
            case IR_BUTTON_8: printButtonState("Press 8.");break;
            case IR_BUTTON_9: printButtonState("Press 9.");break;
            default:break;
        }
    }
}

void printButtonState(String buttonName)
{
  Serial.println(buttonName);
  while(infraredReceiverDecode.buttonState());
  Serial.println("Release.");
}

