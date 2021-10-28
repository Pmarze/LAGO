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
int n=10;

/////////////////////////////////////////////////////////////////

int main(int argc,char **argv){
    if (wiringPiSetup () == -1) exit (1);
    fd_LCD = wiringPiI2CSetup(LCD_Address);
    fd_BMP = wiringPiI2CSetup(BMP180_Address);

    lcd_init(fd_LCD); // setup LCD
    load_calibration(fd_BMP);

    FILE *archivo;
    archivo=fopen("salida.txt","w");
    fprintf(archivo,"inicio de programa\n");
    while(i<n){
        temp=read_temperature(fd_BMP);
        altu=read_altitude(fd_BMP);
        pres=read_pressure(fd_BMP);
    
        fprintf(archivo,"iteracion %d \n",i);
        
        lcdLoc(LINE1,fd_LCD);
        typeln("Temperatura:",fd_LCD);
        lcdLoc(LINE2,fd_LCD);
        typeFloat(temp,fd_LCD);
        printf("\nTemperature : %.2f C\n", temp);
        fprintf(archivo,"temperatura: %f \n",temp);
        delay(t);
        ClrLcd(fd_LCD);
    
        lcdLoc(LINE1,fd_LCD);
        typeln("Presion:",fd_LCD);
        lcdLoc(LINE2,fd_LCD);
        typeFloat(pres,fd_LCD);
        printf("\nPresion: %.2f C\n", pres);
        fprintf(archivo,"presion: %f \n",pres);
        delay(t);
        ClrLcd(fd_LCD);
        i++;
    }
    fclose(archivo);
    ClrLcd(fd_LCD);
    return 0;    

}

/////////////////////////////////////////////////////////////////
