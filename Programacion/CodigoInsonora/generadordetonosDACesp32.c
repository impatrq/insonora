// este es el primer codigo utilizado para generar tonos con el dac de la esp32 
#include <driver/dac.h>
void setup() {
  // Inicializa el DAC
  dac_output_enable(DAC_CHANNEL_1); // Utiliza DAC1 en el pin GPIO 25 (por defecto)
}
void loop() {
  int frequency = 1000;  // Frecuencia en Hz
  int amplitude = 127;   // Amplitud del DAC (de 0 a 255)

  for (int i = 0; i < 360; i++) {
    float angle = (i * 3.14159265 / 180.0);  // Convierte el ángulo a radianes
    int value = (int)(amplitude * sin(angle));  // Calcula el valor de la señal senoidal

    // Escribe el valor en el DAC
    dac_output_voltage(DAC_CHANNEL_1, value);

    delayMicroseconds(1000000 / frequency);  // Espera para mantener la frecuencia
  }
}