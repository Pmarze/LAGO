#include "bmp180.h"
#include <unistd.h>
#include <stdio.h>

void digitos(int);
int tempera

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
			float t = bmp180_temperature(bmp);
			long p = bmp180_pressure(bmp);
			float alt = bmp180_altitude(bmp);
			printf("Temperature = %.1f, Pressure = %lu, Altitude= %.1f\n", t, p, alt);
			usleep(2 * 1000 * 1000);
		}
        tempera=(int)t;
        digitos(tempera);
		bmp180_close(bmp);
	}
	return 0;
}

void digitos(int num){
	while(num > 0) //do till num greater than  0
    {
        int mod = num % 10;  //split last digit from number
        printf("%d\n",mod); //print the digit. 
    
        num = num / 10;    //divide num by 10. num /= 10 also a valid one 
    
}