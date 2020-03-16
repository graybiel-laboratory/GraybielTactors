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

//this should work on all boards, so there is no preprocessor directive here

//includes the libraries of code necessary to make this one work
#include <SensorInterface.h>

//Creates a new SensorInterface object
SensorInterface::SensorInterface() {
}

//Initializes the class, can't always be done at same time as constructor
void SensorInterface::begin() {

    //pins used for the connection with the sensor
    chipSelectPin = 10;
    //the other you need are controlled by the SPI library):
    //dataReadyPin = 6;
	
	pinMode(chipSelectPin, OUTPUT);
    digitalWrite(chipSelectPin, HIGH);
	MPU6000_Init();
}

//TODO: EXPLAIN WHAT METHOD DOES
int SensorInterface::getXAccelerometerCounts(void) {
    int tempData_HI,tempData_LO;
    //Read the  data
    tempData_HI = readRegister(ACCEL_XOUT_H);
    tempData_LO = readRegister(ACCEL_XOUT_L );
    return ((tempData_HI << 8)+ tempData_LO) ;

}

//TODO: EXPLAIN WHAT METHOD DOES
int SensorInterface::getYAccelerometerCounts(void) {
    int tempData_HI,tempData_LO;
    tempData_HI = readRegister(ACCEL_YOUT_H);
    tempData_LO = readRegister(ACCEL_YOUT_L );
    return ((tempData_HI << 8) + tempData_LO);

}

//TODO: EXPLAIN WHAT METHOD DOES
int SensorInterface::getZAccelerometerCounts(void) {
    int tempData_HI,tempData_LO;
    tempData_HI = readRegister(ACCEL_ZOUT_H );
    tempData_LO = readRegister(ACCEL_ZOUT_L );
    return ((tempData_HI << 8) + tempData_LO);

}

//TODO: EXPLAIN WHAT METHOD DOES
int SensorInterface::getXGyroCounts(void) {
    int tempData_HI,tempData_LO;
    tempData_HI = readRegister(GYRO_XOUT_H );
    tempData_LO = readRegister(GYRO_XOUT_L );
    return ((tempData_HI << 8) + tempData_LO);

}

//TODO: EXPLAIN WHAT METHOD DOES
int SensorInterface::getYGyroCounts(void) {
    int tempData_HI,tempData_LO;
    tempData_HI = readRegister(GYRO_YOUT_H);
    tempData_LO = readRegister(GYRO_YOUT_L );
    return ((tempData_HI << 8) + tempData_LO);

}

//TODO: EXPLAIN WHAT METHOD DOES
int SensorInterface::getZGyroCounts(void) {
    int tempData_HI,tempData_LO;
    tempData_HI = readRegister(GYRO_ZOUT_H);
    tempData_LO = readRegister(GYRO_ZOUT_L);
    return ((tempData_HI << 8) + tempData_LO);

}
unsigned int SensorInterface::getTemperature(void){
  int tempData_HI,tempData_LO;

  tempData_HI = readRegister(TEMP_OUT_H + READ_FLAG);
  tempData_LO = readRegister(TEMP_OUT_L + READ_FLAG);

  return ((tempData_HI << 8) + tempData_LO);
}

// MPU6000 Initialization and configuration
void SensorInterface::MPU6000_Init(void) {
    // MPU6000 chip select setup
    // pinMode(MPU6000_CHIP_SELECT_PIN, OUTPUT);
    // writeRegister(MPU6000_CHIP_SELECT_PIN, HIGH);
    // SPI initialization
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);      // SPI at 1Mhz (on 16Mhz clock)
    delay(10);
    // Chip reset
    writeRegister(MPUREG_PWR_MGMT_1, BIT_H_RESET);
    delay(100);
    // Wake up device and select GyroZ clock (better performance)
    writeRegister(MPUREG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ);
    delay(1);
    // Disable I2C bus (recommended on datasheet)
    writeRegister(MPUREG_USER_CTRL, BIT_I2C_IF_DIS);
    delay(1);
    // SAMPLE RATE
    //MPU6000_SPI_write(MPUREG_SMPLRT_DIV,0x04);     // Sample rate = 200Hz    Fsample= 1Khz/(4+1) = 200Hz
    writeRegister(MPUREG_SMPLRT_DIV,19);     // Sample rate = 50Hz    Fsample= 1Khz/(19+1) = 50Hz
    delay(1);
    // FS & DLPF   FS=2000º/s, DLPF = 20Hz (low pass filter)
    writeRegister(MPUREG_CONFIG, BITS_DLPF_CFG_20HZ);
    delay(1);
    writeRegister(MPUREG_GYRO_CONFIG,BITS_FS_2000DPS);  // Gyro scale 2000º/s
    delay(1);
    writeRegister(MPUREG_ACCEL_CONFIG,0x08);            // Accel scale 4g (4096LSB/g)
    delay(1);
    // INT CFG => Interrupt on Data Ready
    //writeRegister(MPUREG_INT_ENABLE,BIT_RAW_RDY_EN);         // INT: Raw data ready
    //delay(1);
    //writeRegister(MPUREG_INT_PIN_CFG,BIT_INT_ANYRD_2CLEAR);  // INT: Clear on any read
    //delay(1);
    // Oscillator set
    writeRegister(MPUREG_PWR_MGMT_1,MPU_CLK_SEL_PLLGYROZ);
    delay(1);
    // MPU_INT is connected to INT 0. Enable interrupt on INT0
    // attachInterrupt(0,MPU6000_data_int,RISING);

}


//Read from or write to register
unsigned int SensorInterface::readRegister(byte thisRegister) {
    unsigned int result = 0;   // result to return
    byte addr = thisRegister + 0x80;
    // Serial.print(thisRegister, BIN);
    // byte dataToSend = thisRegister ;
    //Serial.println(thisRegister, BIN);
    // take the chip select low to select the device:
    digitalWrite(chipSelectPin, LOW);
    // send the device the register you want to read:
    SPI.transfer(addr);
    // send a value of 0 to read the first byte returned:
    result = SPI.transfer(0x00);
    // take the chip select high to de-select:
    digitalWrite(chipSelectPin, HIGH);
    // return the result:
    return(result);

}

//Sends a write command
void SensorInterface::writeRegister(byte thisRegister, byte thisValue) {
    thisRegister = thisRegister ;
    // now combine the register address and the command into one byte:
    byte dataToSend = thisRegister;
    // take the chip select low to select the device:
    digitalWrite(chipSelectPin, LOW);
    SPI.transfer(dataToSend); //Send register location
    SPI.transfer(thisValue);  //Send value to record into register
    // take the chip select high to de-select:
    digitalWrite(chipSelectPin, HIGH);

}
