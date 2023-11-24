# Este es el codigo usado para generar un tono desfasado 180 grados en una raspberry pico utilizando la salida pwm
import machine
import time

freq = 20
duty = 512  # Duty cycle (ajusta según sea necesario)

# PWM sin invertir en GP26
pwm26 = machine.PWM(machine.Pin(26))
pwm26.freq(freq)
pwm26.duty_u16(duty)

# PWM invertido en GP27
pwm27 = machine.PWM(machine.Pin(27), invert=True)
pwm27.freq(freq)
pwm27.duty_u16(duty)

# Espera durante 5 segundos (ajusta la duración según tus necesidades)
time.sleep(10)

# Detén la generación de tono apagando los pines PWM
pwm26.deinit()
pwm27.deinit()
