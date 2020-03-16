/*Demonstares use of multiplexer using c2 tactor 
 * and inidviual control of c2 tactors
 * example code from https://www.youtube.com/watch?v=XWQsqPQOW-U
 * The multiplexer must be used with another component, it cannot
 * be demonstrated alone
 Jacob Smith Brandeis University*/
 
#include "Wire.h"
#define MUX_Address 0x70 // TCA9548A Encoders address
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
char tmp_string[8];  // Temp string to convert numeric values to string before print to OLED display
int startIndex=0;
int endIndex=3;

int tactorPower;
int MAX_POWER=120;

void setup(){
	 for (int i = startIndex; i < endIndex; i++) {
      initTactor(i);
    }
    Serial.begin(9600);
    delay(2000);
    tactorPower=0;
}


void loop(){
    Serial.println(tactorPower);
    pulseRightTactor(tactorPower);
    pulseLeftTactor(tactorPower);
    if(tactorPower>=MAX_POWER){
      tactorPower=0;
    }else{
       tactorPower+=30;
    }
   
	  delay(500);
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
