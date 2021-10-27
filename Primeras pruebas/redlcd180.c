#include <wiringPiI2C.h>    // lcd & 180
#include <wiringPi.h>       // lcd & 180
#include <stdio.h>          // lcd & 180
#include <stdlib.h>         // lcd
#include <math.h>           // 180
#include "funciones.h"      // lcd & 180

#define BMP180_Address 0x77
#define LCD_Address    0x26

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