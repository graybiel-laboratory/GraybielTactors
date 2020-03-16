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
//TODO: EXPLAIN WHAT METHOD DOES
void setup() {
    //sets up the class
    sensorinterface.begin();
    Serial.begin(9600);
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
    }else if (yAxis<baseThreshold*-1){
      Serial.println("RIGHT"); 
    }else{
      Serial.println("FLAT");  
    }
    delay(500);

}
