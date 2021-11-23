#include "bmp180.h"
#include <unistd.h>
#include <stdio.h>

void digitos(int);
int tempera;
float t;
long p;
float alt;

int main(int argc, char **argv){
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
            digitos(tempera);
		}
	bmp180_close(bmp);
	}
	return 0;
}

void digitos_1(int, fd, int num){
	num=num*10;
	while(num > 0) //do till num greater than  0
    {
        int mod = num % 10;  //split last digit from number
        printf("%d\n",mod); //print the digit. 
		page_data(fd, 0x00, 0x00);
		lcd_num(num);
        num = num / 10;    //divide num by 10. num /= 10 also a valid one 
    
    }
}

void lcd_num(int a){
	if(a==1){
		N_1(fd);
	}
	if(a==2){
		N_2(fd);
	}
	if(a==3){
		N_3(fd);
	}
	if(a==4){
		N_4(fd);
	}
	if(a==5){
		N_5(fd);
	}
	if(a==6){
		N_6(fd);
	}
	if(a==7){
		N_7(fd);
	}
	if(a==8){
		N_8(fd);
	}
	if(a==9){
		N_8(fd);
	}
	if(a==0){
		N_0(fd);
	}	
}