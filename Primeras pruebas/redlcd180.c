#include <wiringPiI2C.h>    // lcd & 180
#include <wiringPi.h>       // lcd & 180
#include <stdio.h>          // lcd & 180
#include <stdlib.h>         // lcd
#include <math.h>           // 180
#include "funciones.h"      // lcd & 180

#define BMP180_Address 0x77
#define LCD_Address    0x26

short AC1,AC2,AC3,B1,B2,MB,MC,MD;
unsigned short AC4,AC5,AC6;
int fd_LCD, fd_BMP;
float temp, altu, pres;
int i;
int t=1000;
int n=10
void load_calibration();

/////////////////////////////////////////////////////////////////

int main(int argc,char **argv){
    if (wiringPiSetup () == -1) exit (1);
    fd_LCD = wiringPiI2CSetup(LCD_Address);
    fd_BMP = wiringPiI2CSetup(BMP180_Address);

    lcd_init(fd_LCD); // setup LCD
    load_calibration();

    FILE *archivo;
    archivo=fopen("salida.txt","w");
    while(i<n){
        temp=read_temperature(fd_BMP);
        altu=read_altitude(fd_BMP);
        pres=read_pressure(fd_BMP);
    
        lcdLoc(LINE1,fd_LCD);
        typeln("Temperatura:");
        lcdLoc(LINE2,fd_LCD);
        typeFloat(temp,fd_LCD);
        printf("\nTemperature : %.2f C\n", temp);
        fprintf(archivo,"temperatura: %f",temp);
        delay(t);
        ClrLcd(fd_LCD);
    
        lcdLoc(LINE1,fd_LCD);
        typeln("Presion:");
        lcdLoc(LINE2,fd_LCD);
        typeFloat(pres,fd_LCD);
        printf("\nPresion: %.2f C\n", pres);
        fprintf(archivo,"presion: %f",pres);
        delay(t);
        ClrLcd(fd_LCD);
        i++;
    }
    fclose(archivo);
    ClrLcd();
    return 0;    
}

/////////////////////////////////////////////////////////////////

void load_calibration(){
    AC1 = I2C_readS16(BMP180_CAL_AC1);
    AC2 = I2C_readS16(BMP180_CAL_AC2);
    AC3 = I2C_readS16(BMP180_CAL_AC3);
    AC4 = I2C_readU16(BMP180_CAL_AC4);
    AC5 = I2C_readU16(BMP180_CAL_AC5);
    AC6 = I2C_readU16(BMP180_CAL_AC6);
    B1  = I2C_readS16(BMP180_CAL_B1);
    B2  = I2C_readS16(BMP180_CAL_B2);
    MB  = I2C_readS16(BMP180_CAL_MB);
    MC  = I2C_readS16(BMP180_CAL_MC);
    MD  = I2C_readS16(BMP180_CAL_MD);
}