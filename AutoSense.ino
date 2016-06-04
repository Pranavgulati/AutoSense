#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <RF24BLE.h>
#include "printf.h"
#define PIN_CE  9 // chip enable
#define PIN_CS  10   // chip select (for SPI)
// The MAC address of the beacon
//anything goes but should be constant over time
#define MY_MAC_0  'B'
#define MY_MAC_1  'A'
#define MY_MAC_2  'A'
#define MY_MAC_3  'A'
#define MY_MAC_4  'A'
#define MY_MAC_5  'B'
#define ANDROID    0x42
#define IPHONE    0x40

#define ACCZ_PIN A0
#define MAX_SAMPLES 10
#define SWEET 0
#define OKAYY 1
#define BUMPY 2
#define GD_ROLLERCOASTER 3 //GD = GOD DAMN 
#define CAR_NO "DLxxAA8569"
//MAX_SAMPLES samples per measurement 
uint8_t accZ[MAX_SAMPLES]={};
//a maximum of 4 total data bytes can be sent along with
//this Car_no length therfore we have 3 more bytes that can be sent
uint8_t RIDE=0;
RF24 radio(PIN_CE, PIN_CS);
RF24BLE BLE(radio);

void getSamples(){
  for(byte i=0;i<MAX_SAMPLES;i++){
      accZ[i]=analogRead(ACCZ_PIN);
      delay(1);//makes sure each reading is roughly 1ms apart
      }
  }
void howsDaRide(){
  //used to check accelerometer's zaxis values and
  //assign relevant ride characteristics
  getSamples();
  int diff=0;
  
  for(byte i=0;i+1<MAX_SAMPLES;i++){
      //find maximum difference here 
      if(abs(accZ[i+1]-accZ[i])>diff){diff=abs(accZ[i+1]-accZ[i]);}
      }
      if(diff<=20){
          RIDE =SWEET;
          }
      else if(diff>20&&diff<=40){
          RIDE =OKAYY;
          }
      else if(diff>40&&diff<=150){
          RIDE =BUMPY;
          }
      else if(diff>150){
          RIDE =GD_ROLLERCOASTER;
          }
    
  }
void setup() {
  Serial.begin(115200);
  SPI.begin();
  radio.begin();
  printf_begin();
  BLE.begin();
}
void loop() {
  howsDaRide();
   for (uint8_t channel = 0; channel < 1; channel++){  // Channel hopping do not alter
    BLE.setPhone(ANDROID);
    BLE.setMAC(MY_MAC_0, MY_MAC_1, MY_MAC_2, MY_MAC_3, MY_MAC_4, MY_MAC_5);
    BLE.setName(CAR_NO);
    BLE.setData(&RIDE, sizeof(RIDE));
    BLE.sendADV(channel);
    delay(1);    // Broadcasting interval
 //   radio.printDetails();
 BLE.printPacket();
  }
  
  delay(50);

}
