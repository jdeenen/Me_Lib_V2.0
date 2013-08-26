

#include <Me_SoftI2cMaster.h>
#include <iSoftwareSerial.h>
#include <Me_BaseShield.h>
#include <Me_SoftBluetooth.h>

Me_SoftBluetooth bluetooth;

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
  Serial.begin(9600);
  Serial.println("Application Start!");
}

void loop()
{
  if(checkBluetooth()){
    readBuffer();
  }
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
  int type = (buffer[1]&0xf0)>>4;//output,input,analog,pwm...
  int mode = buffer[2];//set,write,read;
  int pin = buffer[3];//pin
  int value = (buffer[4]==1?1:-1)*(buffer[5]*100+buffer[6]);
  if(pin==bluetoothPort-1&&type>0xf){
    Serial.println("return");
    return;
  }
  
  if(type<0xf){
     controlPin(type,mode,pin,value);
  }else{ 
     Serial.println("finish");
     isLock = true;
     sendCommand(0xf,bluetoothPort,0);
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
void controlPin(int type,int mode,int pin,int value){
  /*
  type:0 output 1 input 2 analogWrite 3 analogRead  4 PWM
  mode:0 set 1 write 2 read
  pin:0-255
  value:0-25500
  */
  Serial.println("---------------------");
  Serial.println(pin);
  Serial.println(type);
  Serial.println(mode);
  Serial.println(value);
  switch(type){
    case 0x0:{
      if(mode==0){
        pinMode(pin,OUTPUT);
      }else if(mode==1){
        digitalWrite(pin,value>0?HIGH:LOW);
      }else if(mode==2){
      }
    }
    break;
   case 0x1:{
     if(mode==0){
        pinMode(pin,INPUT);
      }else if(mode==1){
      }else if(mode==2){
       sendCommand(type,pin,digitalRead(pin)); 
      }
   }
    break; 
   case 0x2:{
     if(mode==0){
        pinMode(pin,OUTPUT);
      }else if(mode==1){
        analogWrite(pin,value);
      }else if(mode==2){
      }
   }
   break;
   case 0x3:{
     if(mode==0){
        pinMode(pin,INPUT);
      }else if(mode==1){
      }else if(mode==2){
       sendCommand(type,pin,analogRead(pin)); 
      }
   }
   break;
   case 0x4:{
     if(mode==0){
        pinMode(pin,OUTPUT);
      }else if(mode==1){
        analogWrite(pin,value);
      }else if(mode==2){
      }
   }
   break;
  }
  if(mode==0){
    delay(5);
    bluetooth_listen();
  }
}

void sendCommand(int type,int pin,int value){
   unsigned char bytes[7];
    bytes[0]=0xff;
    bytes[1]=type&0xff;
    bytes[2]=0;
    bytes[3]=pin;
    bytes[4]=0xff&(int)floor(value/100);
    bytes[5]=0xff&(value-bytes[4]*100);
    bytes[6]=0xfe; 
    
    for(int i=0;i<7;i++){
      bluetooth_write(bytes[i]);
    }
}
