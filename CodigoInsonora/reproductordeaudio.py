# codigo utilizado para reproducir lo tomado por el microfono en tiempo real, esta fue la primer prueba con el microfono y su preamp
from machine import Pin, ADC, PWM
import utime

# Configura el pin GPIO para el micrófono (GP28).
MIC_PIN = ADC(Pin(28))

# Configura los pines GPIO para PWM (GP27 y GP26).
PWM_PIN1 = PWM(Pin(27))
PWM_PIN2 = PWM(Pin(26))

# Configura la frecuencia y el ciclo de trabajo del PWM.
PWM_FREQ = 50000
PWM_DUTY = 512  # Puedes ajustar el ciclo de trabajo según sea necesario.

# Inicializa los pines PWM para la reproducción de audio.
PWM_PIN1.freq(PWM_FREQ)
PWM_PIN1.duty_u16(PWM_DUTY)
PWM_PIN2.freq(PWM_FREQ)
PWM_PIN2.duty_u16(PWM_DUTY)

# Función para capturar audio y enviarlo a los pines PWM.
def capture_and_play_audio():
    while True:
        audio_sample = MIC_PIN.read_u16()  # Lee una muestra de audio del micrófono.
        PWM_PIN1.duty_u16(audio_sample)  # Envía la muestra de audio al primer PWM (GP27).
        PWM_PIN2.duty_u16(audio_sample)  # Envía la muestra de audio al segundo PWM (GP26).
        utime.sleep_us(1)  # Pequeña pausa para ajustar la velocidad de lectura.

# Inicia la captura y reproducción de audio en tiempo real.
try:
    capture_and_play_audio()
except KeyboardInterrupt:
    PWM_PIN1.duty_u16(0)  # Detiene la reproducción en GP27 al presionar Ctrl+C.
    PWM_PIN2.duty_u16(0)  # Detiene la reproducción en GP26 al presionar Ctrl+C.
