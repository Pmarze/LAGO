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

void digitos(int, int);
int tempera;
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
	
	if(bmp != NULL){
		int i;
		for(i = 0; i < 10; i++) {
			t = bmp180_temperature(bmp);
			p = bmp180_pressure(bmp);
			alt = bmp180_altitude(bmp);
			printf("Temperature = %.1f, Pressure = %lu, Altitude= %.1f\n", t, p, alt);
			usleep(2 * 1000 * 1000);
            tempera=(int)t;
            digitos(fd, tempera);
		}
	bmp180_close(bmp);
	}
	close(fd);
	return 0;
}

void digitos(int fd, int num){
	num=num*10;
	page_data(fd, 0x00, 0x00);
	while(num > 0) //do till num greater than  0
    {
        int mod = num % 10;  //split last digit from number
        printf("%d\n",mod); //print the digit. 
		lcd_num(fd, num);
        num = num / 10;    //divide num by 10. num /= 10 also a valid one 
    
    }
	clear_lcd(fd);
}

