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
#include "functions.h"
#include "bmp180.h"
#include "pa.h"

char abecedary_lower[]="abcdefghijklmnopqrstuvwxyz";
char abecedary_upper[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char special_signs[]=" :*=.";

void fun_page_data(int fd, int page_a, int column_a){
    i2c_smbus_write_byte_data(fd, 0x00, SET_PAGE_ADDR);
    i2c_smbus_write_byte_data(fd, 0x00, page_a);
    i2c_smbus_write_byte_data(fd, 0x00, INIT_STATUS);
    i2c_smbus_write_byte_data(fd, 0x00, SET_COLUMN_ADDR);
    i2c_smbus_write_byte_data(fd, 0x00, column_a);
    i2c_smbus_write_byte_data(fd, 0x00, 0x7f);
}

void fun_initialize(int fd){
    i2c_smbus_write_byte_data(fd, 0x00, SET_OSC_FREQ);      
    i2c_smbus_write_byte_data(fd, 0x00, 0x80);
    i2c_smbus_write_byte_data(fd, 0x00, SET_MUX_RATIO);
    i2c_smbus_write_byte_data(fd, 0x00, 0x1f);
    i2c_smbus_write_byte_data(fd, 0x00, SET_DISP_OFFSET);
    i2c_smbus_write_byte_data(fd, 0x00, 0x00);
    i2c_smbus_write_byte_data(fd, 0x00, SET_START_LINE | 0x0 );
    i2c_smbus_write_byte_data(fd, 0x00, SET_CHAR_REG);
    i2c_smbus_write_byte_data(fd, 0x00, 0x14);
    i2c_smbus_write_byte_data(fd, 0x00, MEMORY_ADDR_MODE);
    i2c_smbus_write_byte_data(fd, 0x00, 0x00);
    i2c_smbus_write_byte_data(fd, 0x00, SET_SEG_REMAP | 0x1 );
    i2c_smbus_write_byte_data(fd, 0x00, COM_SCAN_DIR_OP);
    i2c_smbus_write_byte_data(fd, 0x00, SET_COM_PIN_CFG);
    i2c_smbus_write_byte_data(fd, 0x00, 0x02); // x12 **
    i2c_smbus_write_byte_data(fd, 0x00, SET_CONTRAST);
    i2c_smbus_write_byte_data(fd, 0x00, 0x7f);
    i2c_smbus_write_byte_data(fd, 0x00, SET_PRECHARGE);
    i2c_smbus_write_byte_data(fd, 0x00, 0xc2); //xc2
    i2c_smbus_write_byte_data(fd, 0x00, 0xd8);
    i2c_smbus_write_byte_data(fd, 0x00, SET_START_LINE);
    i2c_smbus_write_byte_data(fd, 0x00, SET_ENTIRE_ON);
    i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_NORMAL);
    i2c_smbus_write_byte_data(fd, 0x00, DEACT_SCROLL);
    i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_ON);
}


void fun_clear_lcd(int fd){
    fun_page_data(fd, 0x00, 0x00);
    for( int i = 0; i< 512; i++){
    i2c_smbus_write_byte_data(fd, 0x40, 0x00);
    }
}

void fun_digits(int fd, int num){
	int lista[10];
	int j=0;
	int i;
	while(num > 0){
        int mod = num % 10;
		lista[j]=mod;
        num = num / 10;
    	j++;
    }
	for(i=j-1;i>=0;i--){
		if(i==0){
			fun_character(fd, numbers, 14);		// dot
			fun_lcd_num(fd, lista[i]);
		}
		fun_lcd_num(fd, lista[i]);
	}
}

void fun_bienv(int fd){
    fun_page_data(fd, 0x00, 0x00);
    fun_println(fd, "Bienvenidos");
	fun_page_data(fd, 0x32, 0x00);
	fun_println(fd, "LAGO GT");
    sleep(3);
    fun_clear_lcd(fd);
}


void fun_close_disp(void *bmp, int fd){
	fun_clear_lcd(fd);
    bmp180_close(bmp);
    close(fd);
}

void fun_data(void *bmp, int fd, int siesta, pa_data_file_t *data_file){
	float t;
	long p;
	float alt;
    int tempera;
    int altu;

	t = bmp180_temperature(bmp);
	p = bmp180_pressure(bmp);
	alt = bmp180_altitude(bmp);
	// printf("Temperature = %.1f, Pressure = %lu, Altitude= %.1f\n", t, p, alt);
	fputs("Temperature = %.1f, Pressure = %lu, Altitude= %.1f\n", t, p, alt, data_file->Output_BMP);
	t=t*10;
	alt=alt*10;
	altu=(int)alt;
	tempera=(int)t;
	p=p*10;
	fun_page_data( fd, 0x00, 0x00);
	fun_println(fd, "Temperatura = ");
	fun_digits(fd, tempera);
	fun_println(fd, " C");

	fun_page_data( fd, 0x32, 0x00);
	fun_println(fd, "Altura = ");
	fun_digits(fd, altu);
	fun_println(fd, " m");

	sleep(siesta);

	fun_clear_lcd(fd);
	fun_page_data( fd, 0x00, 0x00);
	fun_println(fd, "Presion = ");
	fun_digits(fd, p);
	fun_println(fd, " Pa");

	sleep(siesta);
	fun_clear_lcd(fd);
}

void fun_inic_disp(){
	int status;
	char *i2c_device = "/dev/i2c-0";
    int address = 0x77;

	fd1 = open("/dev/i2c-0", O_RDWR);
	if(fd1 < 0)
    {
        printf("Cannot open the IIC device\n");
    }

    status = ioctl(fd1, I2C_SLAVE, OLED96_ADDR);
    if(status < 0)
    {
        printf("Unable to set the OLED96 address\n");
    }
    if ( i2c_smbus_write_byte_data(fd1, 0x00, DISPLAY_OFF) < 0 )
    {
        printf("Unable to send commands\n");
        printf("errno: %i %s\n",errno,strerror(errno));
    }
	fun_initialize(fd1);
	fun_clear_lcd(fd1);
	fun_bienv(fd1);
	sleep(2);
	fun_clear_lcd(fd1);
	bmp = bmp180_init(address, i2c_device);
	
	bmp180_eprom_t eprom;
	bmp180_dump_eprom(bmp, &eprom);
	bmp180_set_oss(bmp, 1);
}

void fun_lcd_num(int fd, int a){
	if(a==0){fun_character(fd, numbers, 0);}
	if(a==1){fun_character(fd, numbers, 1);}
	if(a==2){fun_character(fd, numbers, 2);}
	if(a==3){fun_character(fd, numbers, 3);}
	if(a==4){fun_character(fd, numbers, 4);}
	if(a==5){fun_character(fd, numbers, 5);}
	if(a==6){fun_character(fd, numbers, 6);}
	if(a==7){fun_character(fd, numbers, 7);}
	if(a==8){fun_character(fd, numbers, 8);}
	if(a==9){fun_character(fd, numbers, 9);}
	
}

void fun_println(int fd, char arr[]){
	int i;
	for(i=0 ; i<strlen(arr); i++){
		if(arr[i]==abecedary_upper[0]){fun_character(fd, capital, 0);}
		if(arr[i]==abecedary_upper[1]){fun_character(fd, capital, 1);}
		if(arr[i]==abecedary_upper[2]){fun_character(fd, capital, 2);}
		if(arr[i]==abecedary_upper[3]){fun_character(fd, capital, 3);}
		if(arr[i]==abecedary_upper[4]){fun_character(fd, capital, 4);}
		if(arr[i]==abecedary_upper[5]){fun_character(fd, capital, 5);}
		if(arr[i]==abecedary_upper[6]){fun_character(fd, capital, 6);}
		if(arr[i]==abecedary_upper[7]){fun_character(fd, capital, 7);}
		if(arr[i]==abecedary_upper[8]){fun_character(fd, capital, 8);}
		if(arr[i]==abecedary_upper[9]){fun_character(fd, capital, 9);}
		if(arr[i]==abecedary_upper[10]){fun_character(fd, capital, 10);}
		if(arr[i]==abecedary_upper[11]){fun_character(fd, capital, 11);}
		if(arr[i]==abecedary_upper[12]){fun_character(fd, capital, 12);}
		if(arr[i]==abecedary_upper[13]){fun_character(fd, capital, 13);}
		if(arr[i]==abecedary_upper[14]){fun_character(fd, capital, 14);}
		if(arr[i]==abecedary_upper[15]){fun_character(fd, capital, 15);}
		if(arr[i]==abecedary_upper[16]){fun_character(fd, capital, 16);}
		if(arr[i]==abecedary_upper[17]){fun_character(fd, capital, 17);}
		if(arr[i]==abecedary_upper[18]){fun_character(fd, capital, 18);}
		if(arr[i]==abecedary_upper[19]){fun_character(fd, capital, 19);}
		if(arr[i]==abecedary_upper[20]){fun_character(fd, capital, 20);}
		if(arr[i]==abecedary_upper[21]){fun_character(fd, capital, 21);}
		if(arr[i]==abecedary_upper[22]){fun_character(fd, capital, 22);}
		if(arr[i]==abecedary_upper[23]){fun_character(fd, capital, 23);}
		if(arr[i]==abecedary_upper[24]){fun_character(fd, capital, 24);}
		if(arr[i]==abecedary_upper[25]){fun_character(fd, capital, 25);}
		if(arr[i]==abecedary_lower[0]){fun_character(fd, lowercase, 0);}
		if(arr[i]==abecedary_lower[1]){fun_character(fd, lowercase, 1);}
		if(arr[i]==abecedary_lower[2]){fun_character(fd, lowercase, 2);}
		if(arr[i]==abecedary_lower[3]){fun_character(fd, lowercase, 3);}
		if(arr[i]==abecedary_lower[4]){fun_character(fd, lowercase, 4);}
		if(arr[i]==abecedary_lower[5]){fun_character(fd, lowercase, 5);}
		if(arr[i]==abecedary_lower[6]){fun_character(fd, lowercase, 6);}
		if(arr[i]==abecedary_lower[7]){fun_character(fd, lowercase, 7);}
		if(arr[i]==abecedary_lower[8]){fun_character(fd, lowercase, 8);}
		if(arr[i]==abecedary_lower[9]){fun_character(fd, lowercase, 9);}
		if(arr[i]==abecedary_lower[10]){fun_character(fd, lowercase, 10);}
		if(arr[i]==abecedary_lower[11]){fun_character(fd, lowercase, 11);}
		if(arr[i]==abecedary_lower[12]){fun_character(fd, lowercase, 12);}
		if(arr[i]==abecedary_lower[13]){fun_character(fd, lowercase, 13);}
		if(arr[i]==abecedary_lower[14]){fun_character(fd, lowercase, 14);}
		if(arr[i]==abecedary_lower[15]){fun_character(fd, lowercase, 15);}
		if(arr[i]==abecedary_lower[16]){fun_character(fd, lowercase, 16);}
		if(arr[i]==abecedary_lower[17]){fun_character(fd, lowercase, 17);}
		if(arr[i]==abecedary_lower[18]){fun_character(fd, lowercase, 18);}
		if(arr[i]==abecedary_lower[19]){fun_character(fd, lowercase, 19);}
		if(arr[i]==abecedary_lower[20]){fun_character(fd, lowercase, 20);}
		if(arr[i]==abecedary_lower[21]){fun_character(fd, lowercase, 21);}
		if(arr[i]==abecedary_lower[22]){fun_character(fd, lowercase, 22);}
		if(arr[i]==abecedary_lower[23]){fun_character(fd, lowercase, 23);}
		if(arr[i]==abecedary_lower[24]){fun_character(fd, lowercase, 24);}
		if(arr[i]==abecedary_lower[25]){fun_character(fd, lowercase, 25);}
		if(arr[i]==special_signs[0]){fun_character(fd, numbers, 10);}
		if(arr[i]==special_signs[1]){fun_character(fd, numbers, 11);}
		if(arr[i]==special_signs[2]){fun_character(fd, numbers, 12);}
		if(arr[i]==special_signs[3]){fun_character(fd, numbers, 13);}
		if(arr[i]==special_signs[4]){fun_character(fd, numbers, 14);}
	}
}

void fun_character(int fd, uint8_t C[26][5], int a){
	int i;
    for(i=0 ; i<5; i++){
        i2c_smbus_write_byte_data(fd, SET_START_LINE, C[a][i]);
    }
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00); 
}