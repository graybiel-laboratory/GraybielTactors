/*runs the haptic driver in direct feedback mode
effectvie range seems to be 0 to 170 power*/
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

int power=0;
void loop() {

  if (power <=170) {
    Serial.println(power);
    drv.setRealtimeValue(power);
    power+=10;
    delay(2000);
  } else {
    power=0;
  }
  
}
