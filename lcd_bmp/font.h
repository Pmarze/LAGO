  /**
    * @file font.h
    * @version 1.0
    * @date 16/12/2021
    * @author Pablo M. Zeceña
    * @brief Library to display characters into the LCD and operational parameters of the SSD1306. 
    * Each character to be displayed on the screen is declared individually as a function. 
    * This library is based on some functions of the SSD1306/lib/font.c repository, created by Marian Hrinko "https://github.com/Matiasus/SSD1306"
    * @code
      // Each character must be written using hexadecimal numbers 
      // sent one by one as shown in the example below
      void DEMO(int fd){
          i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
          i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
          i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
          i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
          i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);  
          i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
      }
    * @endcode    
    *
    * @code 
      int main(int argc, char **argv){
	    fun_inic_disp();
	    if(bmp != NULL){
          H_M(fd);
          e_MI(fd);
          l_MI(fd);
          l_MI(fd);
          o_MI(fd);
          space(fd);
          W_M(fd);
          o_MI(fd);
          r_MI(fd);
          l_MI(fd);
          d_MI(fd);
	    }
	    fun_close_disp(bmp,fd);

	    return 0;
      }
      // The LCD Show: 
      // Hello World
    * @endcode  
    */
#ifndef FONT_H_
#define FONT_H_

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

#define PAGESIZE        32

////////////////////////////////////////////////////////////////////////////////
// Command definition

#define SET_MUX_RATIO       0xA8
  /**
    * @brief Display offset
    */
#define SET_DISP_OFFSET     0xD3
#define DISPLAY_ON          0xAF
#define DISPLAY_OFF         0xAE
  /**
    * @brief Entire display on
    */
#define SET_ENTIRE_ON       0xA4
  /**
    * @brief Display ignore RAM
    */
#define DISPLAY_IGN_RAM     0xA5
  /**
    * @brief Display normal
    */
#define DISPLAY_NORMAL      0xA6
  /**
    * @brief Display inverse
    */
#define DISPLAY_INVERSE     0xA7
  /**
    * @brief Desactivate scroll
    */
#define DEACT_SCROLL        0x2E
#define ACTIVE_SCROLL       0x2F
  /**
    * @brief Set display start line
    */  
#define SET_START_LINE      0x40
  /**
    * @brief Set memory address
    */
#define MEMORY_ADDR_MODE    0x20
  /**
    * @brief  Set column addres
    */
#define SET_COLUMN_ADDR     0x21
  /**
    * @brief Set page address
    */
#define SET_PAGE_ADDR       0x22
  /**
    * @brief Set segment remap (column address 0 is mapped to SEG0 (RESET))
    */
#define SET_SEG_REMAP       0xA0
  /**
    * @brief Set segment remap (column address 127 is mapped to SEG0)
    */
#define SET_SEG_REMAP_OP    0xA1  
  /**
    * @brief Set COM output scan direction (normal mode (RESET) Scan from COM0 to COM[N-1])
    */
#define COM_SCAN_DIR        0xC0
  /**
    * @brief Set COM output scan direction (remapped mode. Scan from COM[N-1] to COM0)
    */
#define COM_SCAN_DIR_OP     0xC8
  /**
    * @brief Set COM pins Hardware configuration
    */
#define SET_COM_PIN_CFG     0xDA
  /**
    * @brief Set constrast control
    */ 
#define SET_CONTRAST        0x81
#define SET_OSC_FREQ        0xD5
  /**
    * @brief Charge pump setting
    */
#define SET_CHAR_REG        0x8D
  /**
    * @brief Set pre-charge Period
    */
#define SET_PRECHARGE       0xD9
  /**
    * @brief Set VcomH deselect level
    */
#define SET_VCOM_DESEL      0xDB

#define INIT_STATUS         0xFF

////////////////////////////////////////////////////////////////////////////////

void colon(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x36);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x36);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);   
}

void asterisk(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
}

void equal(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void dot(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x60);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x60);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void space(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void A_M(int fd){
    int i;
    uint8_t number[6] = {0x7E,0x11,0x11,0x11,0x7E,0x00};
	for(i=0 ; i<5; i++){
        i2c_smbus_write_byte_data(fd, SET_START_LINE, number[i]);
    }      
}

void B_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x36);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void C_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void D_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1C); 
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);   
}

void E_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7f);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);    
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void F_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7f);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void G_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
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
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
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
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void K_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x22);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void L_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
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
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x10);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void O_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
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
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void Q_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x51);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x21);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x5E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void R_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x19);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x29);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x46);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void S_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x46);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x31);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void T_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void U_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void V_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
}

void W_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3F);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void X_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x63);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x63);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void Y_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x07);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x70);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x07); 
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);   
}

void Z_M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x61);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x51);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x43);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);    
}

void N_0(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x51);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_1(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x42);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_2(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x42);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x61);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x51);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x46);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_3(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x21);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x4b);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x31);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_4(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x18);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x12);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x10);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_5(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x27);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x39);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_6(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x4A);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x30);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_7(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x71);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x05);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x03);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_8(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x36);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x36);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void N_9(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x06);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x49);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x29);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1E);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void a_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x78);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void b_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x48);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void c_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void d_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x48);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void e_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x18);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void f_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7E);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x09);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x01);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x02);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void g_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x0C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x52);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x52);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x52);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3E);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void h_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x78);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void i_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7D);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void j_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3D);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void k_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x10);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x28);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void l_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x41);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void m_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x18);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x78);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void n_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x78);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void o_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x38);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void p_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void q_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x14);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7c);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void r_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x08);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void s_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x48);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void t_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x04);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3F);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void u_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x7C);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void v_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x20);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x1C);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void w_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x30);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x40);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3C);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void x_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x28);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x10);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x28);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void y_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x0C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x50);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x50);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x50);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x3C);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

void z_MI(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x64);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x54);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x4C);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x44);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}

#endif /* FONT_H_ */