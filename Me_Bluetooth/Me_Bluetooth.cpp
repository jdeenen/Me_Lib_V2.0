/******************************************************************************
* File Name          : Me_Bluetooth.cpp
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 12/12/2012
* Description        : Class for Makeblock Electronic modules of Me-Bluetooth. 
                       The module can only be connected to the port 3, 4, 6
                       of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_Bluetooth.h"

//default port is 4
Me_Bluetooth::Me_Bluetooth():swSerial(mePort[PORT_4].outsidePin, mePort[PORT_4].innersidePin)
{
	port = PORT_4;
	bluetoothState = BLUETOOTH_PAIRABLE;
}

Me_Bluetooth::Me_Bluetooth(int portNum):swSerial(mePort[portNum].outsidePin, mePort[portNum].innersidePin)
{
	port = portNum;
	bluetoothState = BLUETOOTH_PAIRABLE;
}

void Me_Bluetooth::begin(long baudrate)
{
	pinMode(mePort[port].innersidePin, OUTPUT);
	pinMode(mePort[port].outsidePin, INPUT);
	bdrate = baudrate;
	if(port > 2 && port < 7)
	{
		swSerial.begin(baudrate);
	}

}

int Me_Bluetooth::setName(String name)
{
	int isSuccess = 0;
	
	String recvBuf;
	char recvChar;
	
	String cmd("AT+NAME");
	cmd += name;
	cmd += '\r';
	cmd += '\n';
	int cmdLen = cmd.length();
	
	for(int i = 0; i < cmdLen; i++)
	{
		swSerial.write(cmd[i]);
	}
	
	delay(100);
	int len = 0;
	if(len = available())
	{
		for(int i = 0; i < len; i++)
		{
			recvChar = read();
			//Serial.print(recvChar);
			recvBuf += recvChar;
		}
		if(recvBuf.indexOf("OK") != -1)
		{
			isSuccess= 1;
		}
	}
	
	return isSuccess;
}

size_t Me_Bluetooth::write(uint8_t byte)
{
	return(swSerial.write(byte));
}

int Me_Bluetooth::read()
{
	return(swSerial.read());
}

int Me_Bluetooth::available()
{
	return(swSerial.available());
}

void Me_Bluetooth::flush()
{
	swSerial.flush();
}

int Me_Bluetooth::checkConnected()
{
	String conSymb = "+CONNECTED";//if connected, "+CONNECTED" will be sent back from the Bluetooth
	String parSymb = "+PAIRABLE";//if pairable, "+PAIRABLE" will be sent back from the Bluetooth
	String recvBuf;
	char recvChar;
	
	if(available())
	{
		recvChar = read();
		recvBuf += recvChar;
		if(recvBuf.indexOf(conSymb) != -1)
		{
			bluetoothState = BLUETOOTH_CONNECTED;
		}
		if(recvBuf.indexOf(parSymb) != -1)
		{
			bluetoothState = BLUETOOTH_PAIRABLE;
		}
	}
	return bluetoothState;
}

