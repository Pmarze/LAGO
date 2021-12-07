#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

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
//#include "font.h"

#define OLED96_ADDR     0x3c
#define PAGESIZE        32

int fd;
void *bmp;

void fun_page_data(int, int, int);
void fun_initialize(int);
void fun_clear_lcd(int);
void fun_lcd_num(int, int);

void fun_abecedario(int, int, int);
void fun_numeros(int, int, int);
void fun_digits(int, int, int, int ,int);
void fun_Text_alt(int, int, int);
void fun_Text_Pres(int, int, int);
void fun_Text_temp(int, int, int);
void fun_LAGO(int, int, int);
void fun_data(void *, int);
void fun_inic_disp();
void fun_close_disp(void *, int);

#endif /*FUNCTIONS_H*/
