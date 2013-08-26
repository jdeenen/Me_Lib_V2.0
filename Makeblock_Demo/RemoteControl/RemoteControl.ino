#include <Me_BaseShield.h>
#include <SoftwareSerial.h>
#include <Me_InfraredReceiverDecode.h>
#include <Me_BaseShieldMotorDriver.h>

Me_BaseShieldMotorDriver baseShieldMotorDriver;// use M1 and M2 ports on BaseShield
Me_InfraredReceiverDecode infraredReceiverDecode(PORT_3);

int leftSpeed = 150;
int rightSpeed = 150;

void setup()
{
    Serial.begin(9600);
    baseShieldMotorDriver.begin();
    infraredReceiverDecode.begin();
}

void loop()
{
    if(infraredReceiverDecode.available())
    {
        switch(infraredReceiverDecode.read())
        {
            case IR_BUTTON_PLUS: 
                 runForward();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_PREVIOUS: 
                 runLeft();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_NEXT: 
                 runRight();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            case IR_BUTTON_MINUS: 
                 runBack();
                 while(infraredReceiverDecode.buttonState());
                 runStop();
                 break;
            default:break;
        }
    }
}

void runForward()
{
    Serial.println("run forward");
    baseShieldMotorDriver.runMotors(leftSpeed,rightSpeed);
}

void runLeft()
{
    Serial.println("run left");
    baseShieldMotorDriver.runMotors(64,-64);
}
void runRight()
{
    Serial.println("run right");
    baseShieldMotorDriver.runMotors(-64,64);
}
void runStop()
{
    Serial.println("run stop");
    baseShieldMotorDriver.stopMotors();
}
void runBack()
{
    Serial.println("run back");
    baseShieldMotorDriver.runMotors(-leftSpeed,-rightSpeed);
}

