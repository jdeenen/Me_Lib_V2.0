/******************************************************************************
* File Name          : Me_LegoMotor.h
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me -  Lego 
                       Digital Bridge. The module is used to connect the NXT 
                       Lego Motor Driver to Arduino. The module can only be 
                       connected to the port 1, 2 of Me - Base Shield. One 
                       module can drive two Lego Motor.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include <Arduino.h>
#include <Me_BaseShield.h>
#include <Me_I2cMaster.h>


#ifndef Me_LegoMotor_h
#define Me_LegoMotor_h
#define SLAVE_ADDRESS 0x08

//Currernt Time Status of Motor 1
#define M1_Seconds_Read 0x01
//Currernt Time Status of Motor 2
#define M2_Seconds_Read 0x05
//Current Tacho Status of Motor 1
#define M1_Degrees_Read 0x09
//Current Tacho Status of Motor 2
#define M2_Degrees_Read 0x0D
//Currernt Speed Status of Motor 1
#define M1_Speed_Read 0x11
//Currernt Speed Status of Motor 2
#define M2_Speed_Read 0x13
//Duration is done or not
/*#define M1_Time_Status 0x15
#define M2_Time_Status 0x16
#define M1_Degrees_Status 0x17
#define M2_Degrees_Status 0x18*/
#define Duration_Status 0x19

//Set PID
#define Set_KP 0x9B
#define Set_KI 0x9C
#define Set_KD 0x9D

typedef enum
{
	Reset_Seconds_M1 = 0x20,
	Reset_Seconds_M2 = 0x21,
	Reset_Degrees_M1 = 0x22,
	Reset_Degrees_M2 = 0x23
}Me_Reset_Mode;

//Speed Mode
typedef enum 
{
	Speed_Power_M1 = 0x81,   
 	Speed_RPM_M1   = 0x83,
	Speed_Power_M2 = 0x85,
	Speed_RPM_M2   = 0x87
} Me_Speed_Mode;
//Duration mode
typedef enum
{
	Duration_Unlimited_M1 = 0x89,
	Duration_Seconds_M1 	= 0x8A,
	Duration_Degrees_M1 	= 0x8E,
	Duration_Unlimited_M2 = 0x92,
	Duration_Seconds_M2 	= 0x93,
	Duration_Degrees_M2 	= 0x97
} Me_Duration_Mode;
//Next action
typedef enum 
{
	Brake_M1 = 0x24,
	Coast_M1 = 0x25,
	Brake_M2 = 0x26,
	Coast_M2 = 0x27
} Me_Next_Action;
//Wait
typedef enum 
{
  Completion_Dont_Wait = 0x00,  
 	Completion_Wait_For  = 0x01  
 } Completion_Wait;

class Me_LegoMotor
{
public:
	Me_LegoMotor();
	//portNum can only be 1 & 2
	Me_LegoMotor(int portNum);
	void begin();
	void writeByte(uint8_t Address, uint8_t dat);
	void writeData(uint8_t slAddress, uint8_t dtAddress,uint8_t data);
	uint8_t readByte(uint8_t slAddress, uint8_t dtAddress);
	int readInt(uint8_t slAddress,uint8_t dtAddress);
	long readLong(uint8_t slAddress,uint8_t dtAddress);
	int Motor1GetSpeedStatus();
	int Motor2GetSpeedStatus();
	long Motor1GetSecondsStatus();
	long Motor2GetSecondsStatus();
	long Motor1GetDegreesStatus();
	long Motor2GetDegreesStatus();
	void Reset(Me_Reset_Mode reset_mode);
	void MotorSetPID(uint8_t KP, uint8_t KI, uint8_t KD);
	void MotorSetSpeed(Me_Speed_Mode speed_mode, int speed);
	void MotorSetDuration(Me_Duration_Mode duration_mode, uint32_t duration);
	void MotorSetSpeedAndDuration(Me_Speed_Mode speed_mode, int speed, Me_Duration_Mode duration_mode, uint32_t duration);
	void Stop(Me_Next_Action next_action);
	void Run(Me_Speed_Mode speed_mode,	int speed,	Me_Duration_Mode duration_mode,	uint32_t duration,	Completion_Wait wait_for_completion);
private:
	int port;
	Me_SoftI2cMaster softI2cMaster;
};
#endif