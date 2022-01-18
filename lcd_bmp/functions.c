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
			dot(fd);
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
    bmp180_close(bmp);
    close(fd);
}

void fun_data(void *bmp, int fd){
	float t;
	long p;
	float alt;
    int tempera;
    int altu;

	t = bmp180_temperature(bmp);
	p = bmp180_pressure(bmp);
	alt = bmp180_altitude(bmp);
	printf("Temperature = %.1f, Pressure = %lu, Altitude= %.1f\n", t, p, alt);
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

	sleep(2);

	fun_clear_lcd(fd);
	fun_page_data( fd, 0x00, 0x00);
	fun_println(fd, "Presion = ");
	fun_digits(fd, p);
	fun_println(fd, " Pa");

	sleep(2);
	fun_clear_lcd(fd);
}

void fun_inic_disp(){
	int status;
	char *i2c_device = "/dev/i2c-0";
    int address = 0x77;

	fd = open("/dev/i2c-0", O_RDWR);
	if(fd < 0)
    {
        printf("Cannot open the IIC device\n");
    }

    status = ioctl(fd, I2C_SLAVE, OLED96_ADDR);
    if(status < 0)
    {
        printf("Unable to set the OLED96 address\n");
    }
    if ( i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_OFF) < 0 )
    {
        printf("Unable to send commands\n");
        printf("errno: %i %s\n",errno,strerror(errno));
    }
	fun_initialize(fd);
	fun_clear_lcd(fd);
	
	bmp = bmp180_init(address, i2c_device);
	
	bmp180_eprom_t eprom;
	bmp180_dump_eprom(bmp, &eprom);
	bmp180_set_oss(bmp, 1);
}

void fun_lcd_num(int fd, int a){
	if(a==1){character(fd,N_1[5]);}
	if(a==2){character(fd,N_2[5]);}
	if(a==3){character(fd,N_3[5]);}
	if(a==4){character(fd,N_4[5]);}
	if(a==5){character(fd,N_5[5]);}
	if(a==6){character(fd,N_6[5]);}
	if(a==7){character(fd,N_7[5]);}
	if(a==8){character(fd,N_8[5]);}
	if(a==9){character(fd,N_9[5]);}
	if(a==0){character(fd,N_0[5]);}
}

void fun_println(int fd, char arr[]){
	int i;
	for(i=0 ; i<strlen(arr); i++){
		if(arr[i]==abecedary_upper[0]){character(fd,A_M[5]);}
		if(arr[i]==abecedary_upper[1]){character(fd,B_M[5]);}
		if(arr[i]==abecedary_upper[2]){character(fd,C_M[5]);}
		if(arr[i]==abecedary_upper[3]){character(fd,D_M[5]);}
		if(arr[i]==abecedary_upper[4]){character(fd,E_M[5]);}
		if(arr[i]==abecedary_upper[5]){character(fd,F_M[5]);}
		if(arr[i]==abecedary_upper[6]){character(fd,G_M[5]);}
		if(arr[i]==abecedary_upper[7]){character(fd,H_M[5]);}
		if(arr[i]==abecedary_upper[8]){character(fd,I_M[5]);}
		if(arr[i]==abecedary_upper[9]){character(fd,J_M[5]);}
		if(arr[i]==abecedary_upper[10]){character(fd,K_M[5]);}
		if(arr[i]==abecedary_upper[11]){character(fd,L_M[5]);}
		if(arr[i]==abecedary_upper[12]){character(fd,M_M[5]);}
		if(arr[i]==abecedary_upper[13]){character(fd,N_M[5]);}
		if(arr[i]==abecedary_upper[14]){character(fd,O_M[5]);}
		if(arr[i]==abecedary_upper[15]){character(fd,P_M[5]);}
		if(arr[i]==abecedary_upper[16]){character(fd,Q_M[5]);}
		if(arr[i]==abecedary_upper[17]){character(fd,R_M[5]);}
		if(arr[i]==abecedary_upper[18]){character(fd,S_M[5]);}
		if(arr[i]==abecedary_upper[19]){character(fd,T_M[5]);}
		if(arr[i]==abecedary_upper[20]){character(fd,U_M[5]);}
		if(arr[i]==abecedary_upper[21]){character(fd,V_M[5]);}
		if(arr[i]==abecedary_upper[22]){character(fd,W_M[5]);}
		if(arr[i]==abecedary_upper[23]){character(fd,X_M[5]);}
		if(arr[i]==abecedary_upper[24]){character(fd,Y_M[5]);}
		if(arr[i]==abecedary_upper[25]){character(fd,Z_M[5]);}
		if(arr[i]==abecedary_lower[0]){character(fd,a_MI[5]);}
		if(arr[i]==abecedary_lower[1]){character(fd,b_MI[5]);}
		if(arr[i]==abecedary_lower[2]){character(fd,c_MI[5]);}
		if(arr[i]==abecedary_lower[3]){character(fd,d_MI[5]);}
		if(arr[i]==abecedary_lower[4]){character(fd,e_MI[5]);}
		if(arr[i]==abecedary_lower[5]){character(fd,f_MI[5]);}
		if(arr[i]==abecedary_lower[6]){character(fd,g_MI[5]);}
		if(arr[i]==abecedary_lower[7]){character(fd,h_MI[5]);}
		if(arr[i]==abecedary_lower[8]){character(fd,i_MI[5]);}
		if(arr[i]==abecedary_lower[9]){character(fd,j_MI[5]);}
		if(arr[i]==abecedary_lower[10]){character(fd,k_MI[5]);}
		if(arr[i]==abecedary_lower[11]){character(fd,l_MI[5]);}
		if(arr[i]==abecedary_lower[12]){character(fd,m_MI[5]);}
		if(arr[i]==abecedary_lower[13]){character(fd,n_MI[5]);}
		if(arr[i]==abecedary_lower[14]){character(fd,o_MI[5]);}
		if(arr[i]==abecedary_lower[15]){character(fd,p_MI[5]);}
		if(arr[i]==abecedary_lower[16]){character(fd,q_MI[5]);}
		if(arr[i]==abecedary_lower[17]){character(fd,r_MI[5]);}
		if(arr[i]==abecedary_lower[18]){character(fd,s_MI[5]);}
		if(arr[i]==abecedary_lower[19]){character(fd,t_MI[5]);}
		if(arr[i]==abecedary_lower[20]){character(fd,u_MI[5]);}
		if(arr[i]==abecedary_lower[21]){character(fd,v_MI[5]);}
		if(arr[i]==abecedary_lower[22]){character(fd,w_MI[5]);}
		if(arr[i]==abecedary_lower[23]){character(fd,x_MI[5]);}
		if(arr[i]==abecedary_lower[24]){character(fd,y_MI[5]);}
		if(arr[i]==abecedary_lower[25]){character(fd,z_MI[5]);}
		if(arr[i]==special_signs[0]){character(fd,space[5]);}
		if(arr[i]==special_signs[1]){character(fd,colon[5]);}
		if(arr[i]==special_signs[2]){character(fd,asterisk[5]);}
		if(arr[i]==special_signs[3]){character(fd,equal[5]);}
		if(arr[i]==special_signs[4]){character(fd,dot[5]);}
	}
}