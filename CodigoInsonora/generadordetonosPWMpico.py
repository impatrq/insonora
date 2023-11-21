# Este es el primer codigo usado para generar tonos en los 2 canales distintos, para testear que funcionaba el pwm-audio en la pico 
import machine
import utime

# Configura el pin PWM para la salida de audio
pwm_pin = machine.Pin(0)  # Puedes ajustar el número de pin según tu conexión
pwm = machine.PWM(pwm_pin)
pwm.freq(440)  # Frecuencia del tono en Hz (440 Hz es la nota A4)

# Duración del tono en segundos
duracion = 2  # 2 segundos

# Genera el tono durante la duración especificada
pwm.duty_u16(32768)  # Ajusta la amplitud del tono
utime.sleep(duracion)
pwm.duty_u16(0)  # Detiene el tono apagando el PWM

# Puedes ajustar la frecuencia y la duración según tus necesidades
