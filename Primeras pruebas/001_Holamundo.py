# Comandos de ejecucion
# python 001_Holamundo.py

import RPi.GPIO as gp		# libreria para utilizar los pines de raspberry pi
import time					# Libreria para las pausas
gp.setmode(gp.BCM)			# Elegir tipo de numeracion BCM o BOARD
pin=4						# pin del LED en formato BCM
t=0.125						# delay en segundos

gp.setup(pin,gp.OUT)		# Fijar el pin como salida

for i in range(0,10):		# Ciclo para encender y apagar el LED
	gp.output(pin,gp.HIGH)
	time.sleep(t)			# Tiempo de espera t segundos
	gp.output(pin,gp.LOW)
	time.sleep(t)
gp.cleanup()				# Se limpia la conexion utilizada

gp.setwarnings(False)		# Evitar mensajes de error en la terminal