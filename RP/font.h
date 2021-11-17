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

#define SET_START_LINE      0x40  // Set display start line

void space(int);
void A_M(int);
void B_M(int);
void C_M(int);
void D_M(int);
void E_M(int);
void F_M(int);
void G_M(int);
void H_M(int);
void I_M(int);
void J_M(int);
void K_M(int);
void L_M(int);
void M_M(int);
void N_M(int);
void O_M(int);
void P_M(int);
void T_M(int);

void space(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void A_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x11);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x11);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void B_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x36);    
}

void C_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);    
}

void D_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1C);    
}

void E_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7f);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);    
}

void F_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7f);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
}

void G_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7A);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void H_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);    
}

void I_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void J_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);    
}

void K_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);    
}

void L_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void M_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x02);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x0C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x02);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);    
}

void N_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x10);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);    
}

void O_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void P_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x06);    
}

void T_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
    space(fd);
}

/*
void _M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);    
}
*/