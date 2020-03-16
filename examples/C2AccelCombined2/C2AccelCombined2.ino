/*Joseph Picard, Brandeis University; Ashton-Graybiel Spatial Orientation Lab

  Purpose: General purpose accelerometer/gyroscope to tactor effect controller.

  Email: jcpicard32@gmail.com

  Rights: Copyright (C) 2019 Joseph Picard
          License is GPL-3.0, included in License.txt of this project.

Circuit:
MPU6000 sensor attached to pins  10 - 13:
CSB: pin 10
MOSI: pin 11
MISO: pin 12
SCK: pin 13 2019/08/09*/

//includes the libraries of code necessary to make this one work
#include <SensorInterface.h>

//The object used to interfact with the class
SensorInterface sensorinterface;
int baseThreshold=1000;
int angleThreshold=0;
int yAxis=0;

#include "Wire.h"
#define MUX_Address 0x70 // TCA9548A Encoders address
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
char tmp_string[8];  // Temp string to convert numeric values to string before print to OLED display
int startIndex=0;
int endIndex=3;

//TODO: EXPLAIN WHAT METHOD DOES
void setup() {
   
    //sets up the class
    sensorinterface.begin();
     for (int i = startIndex; i < endIndex; i++) {
      initTactor(i);
    }

    Serial.begin(9600);
    delay(2000);
    Serial.println("yAccel\tyPos");

}

//TODO: EXPLAIN WHAT METHOD DOES
void loop() {
    yAxis=sensorinterface.getYAccelerometerCounts();
    //Prints raw values from the sensor to the monitor.
    Serial.print(yAxis);
    Serial.print("\t");
    if(yAxis>baseThreshold){
      Serial.println("LEFT"); 
      pulseLeftTactor(50);
      pulseRightTactor(0);
    }else if (yAxis<baseThreshold*-1){
      Serial.println("RIGHT"); 
      pulseLeftTactor(0);
      pulseRightTactor(50);
    }else{
      Serial.println("FLAT");  
      pulseLeftTactor(0);
      pulseRightTactor(0);
    }
    delay(100);
}

void pulseRightTactor(int power){
  //tactor 1 is left
  pulseTactor(1,power);
}

void pulseLeftTactor(int power){
  //tactor 2 is right
  pulseTactor(2,power);
}

void pulseTactor(int tactorNum,int power){
  tcaselect(tactorNum);
  drv.setRealtimeValue(power);
 
}

void initTactor(int tactNumber){
     tcaselect(tactNumber);   // Loop through each connected displays on the I2C buses  
     //do setup
     drv.begin();
     drv.useLRA(); 
     drv.setMode(DRV2605_MODE_REALTIME);
}

// Initialize I2C buses using TCA9548A I2C Multiplexer
void tcaselect(uint8_t i2c_bus) {
    if (i2c_bus > 7) return;
    Wire.beginTransmission(MUX_Address);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission(); 
}
