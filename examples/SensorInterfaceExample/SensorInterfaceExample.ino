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

//TODO: EXPLAIN WHAT METHOD DOES
void setup() {
    //sets up the class
    sensorinterface.begin();
    Serial.begin(9600);
    Serial.println("xAccel\tyAccel\tzAccel\txGyro\tyGyro\tzGyro");

}

//TODO: EXPLAIN WHAT METHOD DOES
void loop() {
    //Prints raw values from the sensor to the monitor.
    //NOTE: In it's current state, temperature is not set up to work properly. More work must be done for that data to be useable.
    Serial.print(sensorinterface.getXAccelerometerCounts());
    Serial.print("\t");
    Serial.print(sensorinterface.getYAccelerometerCounts());
    Serial.print("\t");
    Serial.print(sensorinterface.getZAccelerometerCounts());
    Serial.print("\t");
    Serial.print(sensorinterface.getXGyroCounts());
    Serial.print("\t");
    Serial.print(sensorinterface.getYGyroCounts());
    Serial.print("\t");
    Serial.println(sensorinterface.getZGyroCounts());
    delay(500);

}
