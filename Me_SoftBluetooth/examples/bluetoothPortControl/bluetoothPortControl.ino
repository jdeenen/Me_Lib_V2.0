
#include <Me_I2cMaster.h>
#include <iSoftwareSerial.h>
#include <SoftwareServo.h>
#include <Me_SoftServoDriver.h>
#include <Me_MotorDriver.h>
//#include <Me_InfraredReceiver.h>
#include <Me_BaseShieldMotorDriver.h>
#include <Me_LegoMotor.h>
#include <Me_LegoUltrasonic.h>
#include <Me_LineFinder.h>
#include <Me_UltrasonicSensor.h>
#include <Me_BaseShield.h>
#include <Me_SoftBluetooth.h>

Me_BaseShieldMotorDriver baseShieldMotorDriver;
Me_SoftBluetooth bluetooth;
Me_SoftServoDriver servoDrivers[2] = {0,0};
Me_MotorDriver motorDrivers[2]={};
Me_UltrasonicSensor uSensors[8]={};
Me_LineFinder lineFinders[8] = {};
//Me_InfraredReceiver infraredReceivers[] = {};
Me_LegoMotor legoMotorDrivers[] = {};
Me_LegoUltrasonic legoUSensors[] = {};

int portMaps[10] = {0,0,0,0,0,0,0,0,0,0};
int checkDelay = 0;
int bluetoothPort = 3;
int bufferIndex;

unsigned char buffers[10] = {};
unsigned char closeBuffers[3] = {};
boolean isLock = false;

void setup()
{
  Me_BaseShield::begin();
  bufferIndex = 0;
  checkDelay = 0;
  baseShieldMotorDriver.begin();
  baseShieldMotorDriver.stopMotors();
  Serial.begin(9600);
  Serial.println("Application Start!");
}

void loop()
{
  if(checkBluetooth()){
    readBuffer();
  }
  SoftwareServo::refresh();
}
boolean checkBluetooth(){
  if(isLock){
    return true;
  }
  checkDelay++;
  if(checkDelay>20){
    checkDelay=0;
    bluetoothPort++;
    if(bluetoothPort>6){
       bluetoothPort=3; 
    }
    bluetooth_listen();
  }
  delay(10);
  if(bluetoothPort>0){
      readBuffer();
   } 
   return false;
}
void readBuffer(){
  unsigned char inDat;
  if(bluetooth_available()>0){
    inDat = bluetooth_read();     
    if(inDat==0xff){
      bufferIndex=0;
    }
    buffers[bufferIndex]=inDat&0xff; 
     bufferIndex++;
    closeBuffers[0] = closeBuffers[1];
    closeBuffers[1] = closeBuffers[2];
    closeBuffers[2] = inDat;
    if(closeBuffers[0]==0xD&&closeBuffers[1]==0xA&&closeBuffers[2]==0x2B){
      isLock = false;
      return;
    }
    if(inDat==0xfe){
      parseCommand(buffers); 
      return;
    }
    if(bufferIndex>10){
      bufferIndex = 0;
    }
  } 
}
void parseCommand(unsigned char buffer[]){
  int type = (buffer[1]&0xf0)>>4;//servo,motor,sensor...
  int device = buffer[1]&0xf;//set,write,read;
  int mode = buffer[2];
  int port = buffer[3];
  int value = (buffer[4]==1?1:-1)*(buffer[5]*100+buffer[6]);
  if(port==bluetoothPort-1&&type>0xf){
    Serial.println("return");
    return;
  }
  
  if(type<0xf){
     controlDevice(type,mode,device,port,value);
  }else{ 
     isLock = true;
     sendCommand(0xf,0,bluetoothPort,0);
  }
}
void sendCommand(int type,int device,int portnum,int value){
   unsigned char bytes[7];
    bytes[0]=0xff;
    bytes[1]=type&0xff;
    bytes[2]=device;
    bytes[3]=portnum;
    bytes[4]=0xff&(int)floor(value/100);
    bytes[5]=0xff&(value-bytes[4]*100);
    bytes[6]=0xfe; 
    
    for(int i=0;i<7;i++){
      bluetooth_write(bytes[i]);
    }
}
int bluetooth_connected(){
  return bluetooth.connected();
}
int bluetooth_available(){
  return bluetooth.available();
}
void bluetooth_listen(){
  bluetooth = Me_SoftBluetooth(bluetoothPort);
  bluetooth.begin(9600);
}
int bluetooth_read(){
  return bluetooth.read();
}
int bluetooth_write(char buf){
  int result = bluetooth.write(buf);
  delay(2);
  return result;
}
void controlDevice(int type,int mode,int device,int port,int value){
  if(type!=portMaps[port]){
      if(portMaps[port]==0x8){
        openMeMotor(portMaps[port],port,1,device,256);
      }
      if(portMaps[port]==0x2){
        openMotor(portMaps[port],port,1,device,256);
      }
      if(portMaps[port]==0x1){
          servoDrivers[port].detachAll();
      }
      if(portMaps[port]==0x6){ 
       legoMotorDrivers[port] = Me_LegoMotor(port+1);
       legoMotorDrivers[port].begin();
       legoMotorDrivers[port].MotorSetSpeed(Speed_Power_M1,Forward,0);
       legoMotorDrivers[port].MotorSetSpeed(Speed_Power_M2,Forward,0);
      }
  }
  switch(type){
    case 0x0:{
       portMaps[port]=0; 
    }
    break;
   case 0x1:{
     openServo(type,port,mode,device,value);
   }
    break; 
   case 0x2:{
     openMotor(type,port,mode,device,value);
   }
   break;
   case 0x3:{
     openUltraSensor(type,port,mode,device,value);
   }
   break;
   case 0x4:{
     openLineFinder(type,port,mode,device,value);
   }
   break;
   case 0x5:{
     openInfraredReceiver(type,port,mode,device,value);
   }
   break;
   case 0x6:{
     openLegoMotor(type,port,mode,device,value);
   }
   break;
   case 0x7:{
     openLegoUltraSensor(type,port,mode,device,value);
   }
   break; 
   case 0x8:{
     openMeMotor(type,port,mode,device,value);
   }
   break; 
   case 0x9:{
     openCustomCommand(type,port,mode,device,value);
   }
   break;
  }
  if(mode==0){
    delay(5);
    bluetooth_listen();
  }
}
void openMeMotor(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
    baseShieldMotorDriver.begin();
  }
  if(mode==1){
    if(abs(value-256)>5){
       if(port==8)baseShieldMotorDriver.runMotor1(value-256); 
       if(port==9)baseShieldMotorDriver.runMotor2(value-256); 
    }else{
       if(port==8)baseShieldMotorDriver.stopMotor1(); 
       if(port==9)baseShieldMotorDriver.stopMotor2(); 
    }
  }
}
void openServo(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
    servoDrivers[port] = Me_SoftServoDriver(port+1);
    if(!servoDrivers[port].servo1Attached()){
        servoDrivers[port].Servo1_begin();    
    }  
    if(!servoDrivers[port].servo2Attached()){
        servoDrivers[port].Servo2_begin();
    }  
  }
  if(mode==1){
    if(device==1){
      servoDrivers[port].writeServo1(value);
    }
    if(device==2){
      servoDrivers[port].writeServo2(value);
    }
  }
  if(mode==2){
    
  }
}
void openMotor(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
    motorDrivers[port] = Me_MotorDriver(port+1);
    motorDrivers[port].begin();
  }
  if(mode==1){
    if(abs(value-256)>5){
       motorDrivers[port].run(value-256); 
    }else{
       motorDrivers[port].stop();
    }
  }
}
void openUltraSensor(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
    uSensors[port] = Me_UltrasonicSensor(port+1);
    uSensors[port].begin();
  }
  if(mode==2){
    int dist = uSensors[port].distanceCm();
    delay(10);
    sendCommand(0x2,0,port,dist);
  }
}
void openLineFinder(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
    lineFinders[port] = Me_LineFinder(port+1);
    lineFinders[port].begin();
  }
  if(mode==2){
    int line = lineFinders[port].readSensors();
    delay(10);
    sendCommand(0x3,0,port,line);
  }
}
void openInfraredReceiver(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
//  infraredReceivers[port] = Me_InfraredReceiver(port+1);
//  infraredReceivers[port].begin();
  }
}
void openLegoMotor(int type,int port,int mode,int device,int value){
 
  if(portMaps[port]!=type){
    portMaps[port]=type;
  }
  if(mode==1){
    
    legoMotorDrivers[port] = Me_LegoMotor(port+1);
    legoMotorDrivers[port].begin();
    if(abs(value-90)>5){
      if(value>90){
        legoMotorDrivers[port].MotorSetSpeed(device==1?Speed_Power_M1:Speed_Power_M2,Forward,(value-90));
      }else{
        legoMotorDrivers[port].MotorSetSpeed(device==1?Speed_Power_M1:Speed_Power_M2,Backward,(90-value));
      }
    }else{
       legoMotorDrivers[port].MotorSetSpeed(device==1?Speed_Power_M1:Speed_Power_M2,Forward,0);
    }
  }
}
void openLegoUltraSensor(int type,int port,int mode,int device,int value){
  if(portMaps[port]!=type){
    portMaps[port]=type;
    legoUSensors[port] = Me_LegoUltrasonic(port+1);
    legoUSensors[port].begin();
  }
}
void openCustomCommand(int type,int port,int mode,int device,int value){
   Serial.println(port);
   Serial.println(value);
  //your custom command
}
