#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <RF24BLE.h>
#include "printf.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
    
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
uint8_t gyrZ[MAX_SAMPLES]={};
//a maximum of 4 total data bytes can be sent along with
//this Car_no length therfore we have 3 more bytes that can be sent
uint8_t ride=0;
MPU6050 accelgyro;
//calibration values to remove the gravity component
RF24 radio(PIN_CE, PIN_CS);
RF24BLE BLE(radio);

void getSamples(){
    int16_t ax, ay, az;
  int16_t gx, gy, gz;
  for(byte i=0;i<MAX_SAMPLES;i++){
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      accZ[i]=ax/10;
      Serial.println(accZ[i]);
      gyrZ[i]=gx/10;
      delay(1);//makes sure each reading is roughly 1ms apart
      }
  }
void howsDaRide(){

   //used to check accelerometer's zaxis values and
  //assign relevant ride characteristics
  getSamples();
  int16_t diff=0;
  
  for(byte i=0;i+1<MAX_SAMPLES;i++){
      //find maximum difference here 
      if(abs(accZ[i+1]-accZ[i])>diff){diff=abs(accZ[i+1]-accZ[i]);}
      }
      
      if(diff<=40){
          ride =SWEET;
          }
      else if(diff>40&&diff<=100){
          ride =OKAYY;
          }
      else if(diff>100&&diff<=200){
          ride =BUMPY;
          }
      else if(diff>200){
          ride =GD_ROLLERCOASTER;
          }
    
  }
void setup() {
  Serial.begin(115200);
  SPI.begin();
  radio.begin();
  printf_begin();
  BLE.begin();
  Wire.begin();
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "Accelerometer connection successful" : "Accelerometer connection failed");
}
void loop() {
  howsDaRide();
   for (uint8_t channel = 0; channel < 3; channel++){  // Channel hopping do not alter
    BLE.setPhone(ANDROID);
    BLE.setMAC(MY_MAC_0, MY_MAC_1, MY_MAC_2, MY_MAC_3, MY_MAC_4, MY_MAC_5);
    BLE.setName(CAR_NO);
    BLE.setData(&ride, sizeof(ride));
    BLE.sendADV(channel);
    delay(1);    // Broadcasting interval
  }
 delay(50);

}
