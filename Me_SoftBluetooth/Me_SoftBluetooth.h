/******************************************************************************
* File Name          : Me_Bluetooth.h
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 12/12/2012
* Description        : Class for Makeblock Electronic modules of Me-Bluetooth. 
                       The module can only be connected to the port 3, 4, 5, 6
                       of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <iSoftwareSerial.h>
#include <Me_BaseShield.h>
#include <WString.h>

#ifndef Me_SoftBluetooth_h
#define Me_SoftBluetooth_h
	
#define BLUETOOTH_CONNECTED 1
#define BLUETOOTH_PAIRABLE 2


class Me_SoftBluetooth
{
public:
	Me_SoftBluetooth();
	//portNum can only be 3, 4, 5, 6
	Me_SoftBluetooth(int portNum);
	void begin(long baudrate);
	int setName(String name);
	size_t write(uint8_t byte);
	int read();
	int available();
	void flush();
	int connected();
	int checkConnected();
private:
	int port;
	long bdrate;
	iSoftwareSerial swSerial;
	int bluetoothState;
};
#endif

