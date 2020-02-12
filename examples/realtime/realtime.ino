#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
    
  // Set Real-Time Playback mode
  drv.setMode(DRV2605_MODE_REALTIME);
}

uint8_t rtp_index = 0;
//array is composed of 8 bit drive values and times to wait
uint8_t rtpOld[] = {
  0x30, 1, 0x32, 1, 
  0x34, 1, 0x36, 1, 
  0x38, 1, 0x3A, 1,
  0x00, 1,
  0x40, 2, 0x00, 1, 
  0x40, 2, 0x00, 1, 
  0x40, 2, 0x00, 1
};

//array is composed of 8 bit drive values and times to wait
uint8_t rtp[] = {
  0, 1, 10, 1, 
  20, 1, 30, 1, 
  40, 1, 0x3A, 1,
  0x00, 1,
  0x40, 2, 0x00, 1, 
  0x40, 2, 0x00, 1, 
  0x40, 2, 0x00, 1
};

void loop() {

  if (rtp_index < sizeof(rtp)/sizeof(rtp[0])) {
    Serial.println(rtp[rtp_index]);
    drv.setRealtimeValue(rtp[rtp_index]);
    rtp_index++;
    delay(rtp[rtp_index]*2000);
    rtp_index++;
  } else {
    drv.setRealtimeValue(0x00);
    delay(1000);
    rtp_index = 0;
  }
  
}
