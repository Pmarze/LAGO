#include "bmp180.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include "font.h"

#define OLED96_ADDR     0x3c

#define PAGESIZE        32
/* eeprom size on a redpitaya */

static int iic_read(char *buffer, int offset, int size, int fd);
static int iic_write(char *data, int offset, int size, int fd);

/*
* File descriptors
*/
int fd;

void digitos(int, int, int, int);
void Text_temp(int, int, int);
void Text_alt(int, int, int);
void Text_Pres(int, int, int);
int tempera;
int altu;
int pres;
float t;
long p;
float alt;

int main(int argc, char **argv){
	int status;
    fd = open("/dev/i2c-0", O_RDWR);

    if(fd < 0)
    {
        printf("Cannot open the IIC device\n");
        return 1;
    }

    status = ioctl(fd, I2C_SLAVE, OLED96_ADDR);
    if(status < 0)
    {
        printf("Unable to set the OLED96 address\n");
        return -1;
    }
    char buf[10];
    buf[0] = SET_OSC_FREQ;
    buf[1] = DISPLAY_OFF;
    if ( i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_OFF) < 0 )
    {
        printf("Unable to send commands\n");
        printf("errno: %i %s\n",errno,strerror(errno));
        return -1;
    }
	initialize(fd);
    
    clear_lcd(fd);

	char *i2c_device = "/dev/i2c-0";
	int address = 0x77;
	
	void *bmp = bmp180_init(address, i2c_device);
	
	bmp180_eprom_t eprom;
	bmp180_dump_eprom(bmp, &eprom);
	
	
	bmp180_set_oss(bmp, 1);
	
	abecedario(fd,0x32,0x00);
	sleep(3);
	clear_lcd(fd);

	if(bmp != NULL){
		int i;
		for(i = 0; i < 10; i++) {
			t = bmp180_temperature(bmp);
			p = bmp180_pressure(bmp);
			alt = bmp180_altitude(bmp);
			printf("Temperature = %.1f, Pressure = %lu, Altitude= %.1f\n", t, p, alt);
			usleep(2 * 1000 * 1000);
			t=t*10;
			alt=alt*10;
			altu=(int)alt;
            tempera=(int)t;
            Text_temp(fd, 0x00, 0x00);
			digitos(fd, 0x00, 0x32, tempera);
			Text_alt(fd, 0x32, 0x00);
			digitos(fd, 0x32, 0x32, altu);
			sleep(2);
			clear_lcd(fd);
			Text_Pres(fd, 0x00, 0x00);
			digitos(fd, 0x32, 0x00, p);
			sleep(2);
			clear_lcd(fd);
		}
	bmp180_close(bmp);
	}
	close(fd);
	return 0;
}

void digitos(int fd,int page, int column, int num){
	int lista[10];
	int j=0;
	int i;
	page_data(fd, page, column);
	while(num > 0) //do till num greater than  0
    {
        int mod = num % 10;  //split last digit from number
        //printf("%d\n",mod); //print the digit. 
		lista[j]=mod;
        num = num / 10;    //divide num by 10. num /= 10 also a valid one 
    	j++;
    }
	for(i=j-1;i>=0;i--){
		if(i==0){
			dot(fd);
			lcd_num(fd, lista[i]);
		}
		lcd_num(fd, lista[i]);
	}
}

void Text_temp(int fd,int page, int column){
	page_data(fd, page, column);
	T_M(fd);
	E_M(fd);
	M_M(fd);
	P_M(fd);
	equal(fd);
}

void Text_alt(int fd,int page, int column){
	page_data(fd, page, column);
	A_M(fd);
	L_M(fd);
	T_M(fd);
	U_M(fd);
	R_M(fd);
	A_M(fd);
	equal(fd);
}

void Text_Pres(int fd,int page, int column){
	page_data(fd, page, column);
	P_M(fd);
	R_M(fd);
	E_M(fd);
	S_M(fd);
	I_M(fd);
	O_M(fd);
	N_M(fd);
	equal(fd);
}