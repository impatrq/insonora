#include "FFT.h"  // incluye la biblioteca
#include "FFT_signal.h"
#include "DacESP32.h"


DacESP32 dac1(DAC_CHANNEL_1),
         dac2(DAC_CHANNEL_2);
const int MICROPHONE_ADC_PIN = 35;  // Cambia esto al número de pin donde está conectado tu micrófono
const int BUTTON_PIN = 2;
const int BUTTON2_PIN = 4;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  Serial.begin(115200);  // Inicializa la comunicación serial


  fft_config_t *real_fft_plan = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);

}


void loop() {
  for (int k = 0; k < FFT_N; k++) {
    // Leer una muestra del micrófono y almacenarla en fft_signal
    fft_signal[k] = (float)analogRead(MICROPHONE_ADC_PIN);
  }
  bool buttonState = digitalRead(BUTTON_PIN);
  bool buttonState2 = digitalRead(BUTTON2_PIN);

  // Reinicia las variables antes de calcular los valores en cada ciclo
  float max_magnitude = 0;
  float fundamental_freq = 0;

  for (int k = 0; k < FFT_N; k++) {
    // Leer una muestra del micrófono y almacenarla en fft_input
    fft_input[k] = fft_signal[k];
  }

  // Realizar la FFT y calcular las frecuencias y amplitudes
  fft_config_t *real_fft_plan = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);

  // Ejecutar la transformada
  fft_execute(real_fft_plan);

  // Calcular las frecuencias y amplitudes
  for (int k = 1; k < real_fft_plan->size / 2; k++) {
    float mag = sqrt(pow(real_fft_plan->output[2 * k], 2) + pow(real_fft_plan->output[2 * k + 1], 2)) / 1;
    float freq = k * 1.0 / TOTAL_TIME;

        if (mag > max_magnitude) {
        max_magnitude = mag;
        fundamental_freq = freq;
    }

  }
      if (buttonState == HIGH) {
    dac2.outputCW(fundamental_freq, DAC_CW_SCALE_1, DAC_CW_PHASE_180);
  } else {
    dac_output_disable(DAC_CHANNEL_2);
  }
     if (buttonState2 == HIGH){
      dac1.outputCW(fundamental_freq, DAC_CW_SCALE_1, DAC_CW_PHASE_180);
      
     } else {
      dac_output_disable(DAC_CHANNEL_1);
     }
  // Imprimir los resultados
  Serial.print("Frecuencia Fundamental: ");
  Serial.print(fundamental_freq);
  Serial.println(" Hz");

 // Serial.print(buttonState);

  //Serial.print("Amplitud Máxima: ");
  //Serial.print(max_magnitude);
  //Serial.println(" g");
 

  // Liberar la memoria
  fft_destroy(real_fft_plan);

  // Esperar 1 segundo antes de continuar
  //delay(100);  // Delay de 1 segundo
}