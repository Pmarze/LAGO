  /**
    * @file functions.h
    * @version 1.1
    * @date 16/12/2021
    * @author Pablo M. Zeceña
    * @brief Library containing the necessary functions to make the SSD1306 LCD display and the BMP180 sensor work properly
    * This library is based on some functions of the lharnaldi/rp_bmp180 repository, created by L. Horacio Arnaldi "https://github.com/lharnaldi/rp_bmp180"    
    * @code
      int main(int argc, char **argv){
	      fun_inic_disp();
	      if(bmp != NULL){
          fun_page_data(fd, 0x00, 0x00);
          fun_println(fd, "Hello World");
          sleep(3);
          fun_clear_lcd(fd);
	      }
	      fun_close_disp(bmp,fd);
	      return 0;
      }
      // The LCD Show: 
      // Hello World
    * @endcode
  */

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

#define OLED96_ADDR     0x3c
#define PAGESIZE        32

int fd1;
void *bmp;

  /**
    * @brief Information about the location to set the pointer
    * @param fd Indicates the direction of the dispositive
    * @param page_a Indicates the page number (row) where the pointer is to be placed
    * @param column_a Indicates the column number where the pointer is to be placed
    */
void fun_page_data(int, int, int);
  /**
    * @brief Function to define in a single line the initial coordinates where the text is to be displayed. 
    * @param fd Indicates the direction of the dispositive
    */
void fun_initialize(int);
  /**
    * @brief Clears each point of the screen one by one, sending an empty bit.
    * @param fd Indicates the direction of the dispositive
    */
void fun_clear_lcd(int);
  /**
    * @brief Returns the function that represents on the display the number entered in the function
    * @param fd Indicates the direction of the dispositive
    * @param a Number to be displayed on the LCD screen
    */
void fun_lcd_num(int, int);
  /**
    * @brief Displays on the LCD screen, the text entered to the function between quotation marks.
    * @param fd Indicates the direction of the dispositive
    * @param arr Text to be displayed on the LCD
    */
void fun_println(int, char []);

  /**
    * @brief Separates a float number into individual int
    * @param fd Indicates the direction of the dispositive
    * @param num Number to be separated
    */
void fun_digits(int, int);
  /**
    * @brief Displays a welcome message at startup
    * @param fd Indicates the direction of the dispositive
    */
void fun_bienv(int);
  /**
    * @brief Obtains ambient temperature, pressure and altitude from the BMP180 sensor and displays these data on the LCD screen
    * @param bmp Indicates the address of the BMP180 sensor
    * @param fd Indicates the direction of the dispositive
    */
void fun_data(void *, int, int);
  /**
  * @brief Initializes all devices
  */
void fun_inic_disp();
  /**
    * @brief Close all devices
    * @param bmp Indicates the address of the BMP180 sensor
    * @param fd Indicates the direction of the dispositive
    */
void fun_close_disp(void *, int);
  /**
    * @brief Reads the entered character and writes it to the screen by sending the corresponding hexadecimal number sequence.
    * @param fd Indicates the address of the BMP180 sensor
    * @param C Arrangement containing the 26 letters of the alphabet or number and special characters in the form of 5 hexadecimal numbers that make up each character.
    * @param a Number that indicates the letter. i.e. A=0, B=1, C=2 ... 
    */
void fun_character(int, uint8_t [26][5], int);

#endif /*FUNCTIONS_H*/
