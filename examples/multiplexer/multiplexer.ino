/*Demonstares use of multiplexer using c2 tactor
 * example code from https://www.youtube.com/watch?v=XWQsqPQOW-U
 * The multiplexer must be used with another component, it cannot
 * be demonstrated alone
 Jacob Smith Brandeis University*/
 
#include "Wire.h"
#define MUX_Address 0x70 // TCA9548A Encoders address
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
char tmp_string[8];  // Temp string to convert numeric values to string before print to OLED display

// Initialize I2C buses using TCA9548A I2C Multiplexer
void tcaselect(uint8_t i2c_bus) {
    if (i2c_bus > 7) return;
    Wire.beginTransmission(MUX_Address);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission(); 
}

void setup(){
	  initComponent(); // Initialize the displays 
}

// Initialize the displays 
void initComponent(){
    for (int i = 0; i < 7; i++) {
      tcaselect(i);   // Loop through each connected displays on the I2C buses  
  		//do setup
      drv.begin();
      drv.useLRA(); 
      drv.setMode(DRV2605_MODE_REALTIME);
       drv.setRealtimeValue(50);
    }
}


void loop(){
    for (int i = 0; i < 7; i++) {
       tcaselect(i);
  	   drv.setRealtimeValue(50);
    }
	  delay(500);
}
