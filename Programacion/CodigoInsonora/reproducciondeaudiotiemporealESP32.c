#include <Arduino.h>
#include "esp32-hal-dac.h"

const int micPin = 35;  // Pin del micrófono
const int speakerPin1 = 25;  // Salida DAC1
const int speakerPin2 = 26;  // Salida DAC2

void setup() {
  // Inicializa las salidas DAC
  dacWrite(speakerPin1, 0);
  dacWrite(speakerPin2, 0);
}

void loop() {
  int micValue = analogRead(micPin); // Lee el valor del micrófono (0-4095)
  
  // Ajusta micValue según sea necesario
  
  // Envía micValue a las salidas DAC
  dacWrite(speakerPin1, micValue);
  dacWrite(speakerPin2, micValue);
}

