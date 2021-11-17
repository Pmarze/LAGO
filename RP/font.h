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
void E_M(int);
void F_M(int);

void space(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
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
