import RPi.GPIO as gp       # librería para utilizar los pines de raspberry pi
import time                 # Librería para las pausas
pin=4                       # pin del LED
t=0.125                     # delay
gp.setwarnings(False)       
gp.setmode(gp.BCM)          # Elegir tipo de numeracion BCM o BOARD
gp.setup(pin,gp.OUT)        # Fijar el pin como salida
for i in range(0,10):       # Ciclo para encender y apagar el LED
	gp.output(pin,gp.HIGH)
	time.sleep(t)           # Tiempo de espera t segundos
	gp.output(pin,gp.LOW)
	time.sleep(t)
gp.cleanup()                # Se limpia la conexión utilizada