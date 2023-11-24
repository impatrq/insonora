
#include "DacESP32.h"

DacESP32 dac1(DAC_CHANNEL_1),
         dac2(DAC_CHANNEL_2);

void setup() {
  dac1.outputCW(400);                // 2kHz sinus signal on pin 25
  dac2.outputCW(400);   // steady voltage level of 1.3V on pin 26
  //dac2.outputVoltage((uint8_t)100); // same as above but with 8-bit argument, range 0...255
                                      // (Vout = 100/255 * 3.3V = ~1.3V)
}
void loop(){
  
}