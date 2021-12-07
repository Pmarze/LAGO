//#include "bmp180.h"
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
//#include "font.h"
#include "functions.h"

int main(int argc, char **argv){
	
    fun_inic_disp();
	
	if(bmp != NULL){
		int i;
		fun_LAGO(fd,0x32,0x00);
		for(i = 0; i < 25; i++) {
			//fun_data(bmp, fd);
			fun_println("BACA");
			fun_clear_lcd(fd);
		}
	}
	
	fun_close_disp(bmp,fd);

	return 0;
}
