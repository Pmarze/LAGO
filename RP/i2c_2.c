/* @brief This is a simple application for testing IIC communication on a RedPitaya
* @Author Luka Golinar <luka.golinar@redpitaya.com>
*
* (c) Red Pitaya  http://www.redpitaya.com
*
* This part of code is written in C programming language.
* Please visit http://en.wikipedia.org/wiki/C_(programming_language)
* for more details on the language used herein.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <unistd.h>
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

int main(int argc, char *argv[])
{
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
    numeros(fd,0x00,0x00);
    sleep(5);

    clear_lcd(fd);
    abecedario(fd,0x32,0x00);
    abecedario(fd,0x64,0x00);
    sleep(5);

    clear_lcd(fd);

    page_data(fd, 0x64, 0x00);
    
    space(fd);
    L_M(fd);
    A_M(fd);
    G_M(fd);
    O_M(fd);
    space(fd);
    G_M(fd);
    T_M(fd);



    sleep(1);

    /* Release allocations */
    close(fd);
    //free(buffer);

    return 0;
}