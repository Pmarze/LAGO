#!/usr/bin/python
#--------------------------------------
#    ___  ___  _ ____          
#   / _ \/ _ \(_) __/__  __ __ 
#  / , _/ ___/ /\ \/ _ \/ // / 
# /_/|_/_/  /_/___/ .__/\_, /  
#                /_/   /___/   
#
#           bmp180.py
#  Read data from a digital pressure sensor.
#
# Author : Matt Hawkins
# Date   : 17/02/2017
#
# http://www.raspberrypi-spy.co.uk/

# Modified by Amit Rana, kitflix.com for educational purpose
# Date : 13/07/2019
# Modificado por Pablo Martinez, https://github.com/Pmarze
# Fecha: 10/08/2021
#--------------------------------------

# Comandos de ejecucion
# python 003_BMP180.py
# Raspberry trae instalado por defecto la lybera smbus en caso de no traerlo utilizar el siguiente comando:
# sudo apt-get install python-smbus

import smbus
import time
from ctypes import c_short
 
DEVICE = 0x77 # Direccion predeterminada de I2C

#bus = smbus.SMBus(0)   # Rev 1 Pi utiliza Bus=0
bus = smbus.SMBus(1)    # Rev 2 Pi utiliza Bus=1 
 
def convertToString(data):
    # Funcion para convertir codigo binario a string
    return str((data[1] + (256 * data[0])) / 1.2)

def getShort(data, index):
    # Devuelve los dos bytes de data como un valor de 16-bits con signo
    return c_short((data[index] << 8) + data[index + 1]).value

def getUshort(data, index):
    # Devuelve los dos bytes de data como un valor de 16-bits sin signo
    return (data[index] << 8) + data[index + 1]

def readBmp180Id(addr=DEVICE):
    # ID de registro de direccion del chip
    REG_ID     = 0xD0
    (chip_id, chip_version) = bus.read_i2c_block_data(addr, REG_ID, 2)
    return (chip_id, chip_version) 

def readBmp180(addr=0x77):
    # Direcciones de registro
    REG_CALIB  = 0xAA
    REG_MEAS   = 0xF4
    REG_MSB    = 0xF6
    REG_LSB    = 0xF7
    # Direccion del registro de control
    CRV_TEMP   = 0x2E
    CRV_PRES   = 0x34   
    # Configuracion de Oversample
    OVERSAMPLE = 3    # 0 - 3
  
    # Leer datos de calibracion
    # Leer datos de calibracion desde la EEPROM
    cal = bus.read_i2c_block_data(addr, REG_CALIB, 22)  #Lee un bloque de datos de bytes en  un registro
    #(direccion del i2c, inicia el registro, longitud de bloque) 

    # Convertir datos de bytes en valores de palabra

    AC1 = getShort(cal, 0)
    AC2 = getShort(cal, 2)
    AC3 = getShort(cal, 4)
    AC4 = getUshort(cal, 6)
    AC5 = getUshort(cal, 8)
    AC6 = getUshort(cal, 10)
    B1  = getShort(cal, 12)
    B2  = getShort(cal, 14)
    MB  = getShort(cal, 16)
    MC  = getShort(cal, 18)
    MD  = getShort(cal, 20)
  
    # Leer valores de temperatura
    bus.write_byte_data(addr, REG_MEAS, CRV_TEMP)
    time.sleep(0.005)
    (msb, lsb) = bus.read_i2c_block_data(addr, REG_MSB, 2)
    UT = (msb << 8) + lsb

    # Leer valores de presion
    bus.write_byte_data(addr, REG_MEAS, CRV_PRES + (OVERSAMPLE << 6))   # Escribe un byte en un registro dado
    #(direccion de i2c,Registro a escribir,Valor de byte a transmitir)
    time.sleep(0.04)
    (msb, lsb, xsb) = bus.read_i2c_block_data(addr, REG_MSB, 3)
    UP = ((msb << 16) + (lsb << 8) + xsb) >> (8 - OVERSAMPLE)

    # Refinar el valor de la temperatura
    X1 = ((UT - AC6) * AC5) >> 15
    X2 = (MC << 11) / (X1 + MD)
    B5 = X1 + X2
    temperature = int(B5 + 8) >> 4
    temperature = temperature / 10.0

    # Refinar el valor de la presion
    B6  = B5 - 4000
    B62 = int(B6 * B6) >> 12
    X1  = (B2 * B62) >> 11
    X2  = int(AC2 * B6) >> 11
    X3  = X1 + X2
    B3  = (((AC1 * 4 + X3) << OVERSAMPLE) + 2) >> 2

    X1 = int(AC3 * B6) >> 13
    X2 = (B1 * B62) >> 16
    X3 = ((X1 + X2) + 2) >> 2
    B4 = (AC4 * (X3 + 32768)) >> 15
    B7 = (UP - B3) * (50000 >> OVERSAMPLE)

    P = (B7 * 2) / B4

    X1 = (int(P) >> 8) * (int(P) >> 8)
    X1 = (X1 * 3038) >> 16
    X2 = int(-7357 * P) >> 16
    pressure = int(P + ((X1 + X2 + 3791) >> 4))
    #pressure = float(pressure / 100.0)
    
    
    altitude = 44330.0 * (1.0 - pow(pressure / 101325.0, (1.0/5.255)))
    altitude = round(altitude,2)

    return (temperature,pressure,altitude)

tem,pre,alt=readBmp180()

print("Temperatura:",tem)
print("Presion:",pre)
print("Altitud:",alt)