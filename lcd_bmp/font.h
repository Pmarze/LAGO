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

uint8_t* colon[5]    = {0x00,0x00,0x36,0x36,0x00};
uint8_t* asterisk[5] = {0x14,0x08,0x3E,0x08,0x14};
uint8_t* equal[5]    = {0x00,0x14,0x14,0x14,0x14};
uint8_t* dot[5]      = {0X00,0x00,0x60,0x60,0x00};
uint8_t* space[5]    = {0x00,0x00,0x00,0x00,0x00};

uint8_t* A_M[5] = {0x7E,0x11,0x11,0x11,0x7E};
uint8_t* B_M[5] = {0x7F,0x49,0x49,0x49,0x36};
uint8_t* C_M[5] = {0x3E,0x41,0x41,0x41,0x22};
uint8_t* D_M[5] = {0x7F,0x41,0x22,0x22,0x1C};
uint8_t* E_M[5] = {0x7F,0x49,0x49,0x49,0x41};
uint8_t* F_M[5] = {0x7F,0x09,0x09,0x09,0x01};
uint8_t* G_M[5] = {0x3E,0x41,0x49,0x49,0x7A};
uint8_t* H_M[5] = {0x7F,0x08,0x08,0x08,0x7F};
uint8_t* I_M[5] = {0x00,0x41,0x7F,0x41,0x00};
uint8_t* J_M[5] = {0x20,0x40,0x41,0x3F,0x01};
uint8_t* K_M[5] = {0x7F,0x08,0x14,0x22,0x41};
uint8_t* L_M[5] = {0x7F,0x40,0x40,0x40,0x40};
uint8_t* M_M[5] = {0x7F,0x02,0x0C,0x02,0x7F};
uint8_t* N_M[5] = {0x7F,0x04,0x08,0x10,0x7F};
uint8_t* O_M[5] = {0x3E,0x41,0x41,0x41,0x3E};
uint8_t* P_M[5] = {0x7F,0x09,0x09,0x09,0x06};
uint8_t* Q_M[5] = {0x3E,0x41,0x51,0x21,0x5E};
uint8_t* R_M[5] = {0x7F,0x09,0x19,0x29,0x46};
uint8_t* S_M[5] = {0x46,0x49,0x49,0x49,0x31};
uint8_t* T_M[5] = {0x01,0x01,0x7F,0x01,0x01};
uint8_t* U_M[5] = {0x3F,0x40,0x40,0x40,0x3F};
uint8_t* V_M[5] = {0x1F,0x20,0x40,0x20,0x1F};
uint8_t* W_M[5] = {0x3F,0x40,0x38,0x40,0x3F};
uint8_t* X_M[5] = {0x63,0x14,0x08,0x14,0x63};
uint8_t* Y_M[5] = {0x07,0x08,0x70,0x08,0x07};
uint8_t* Z_M[5] = {0x61,0x51,0x49,0x45,0x43};

uint8_t* N_0[5] = {0x3E,0x51,0x49,0x45,0x3E};
uint8_t* N_1[5] = {0x00,0x42,0x7F,0x40,0x00};
uint8_t* N_2[5] = {0x42,0x61,0x51,0x49,0x46};
uint8_t* N_3[5] = {0x21,0x41,0x45,0x4B,0x31};
uint8_t* N_4[5] = {0x18,0x14,0x12,0x7F,0x10};
uint8_t* N_5[5] = {0x27,0x45,0x45,0x45,0x39};
uint8_t* N_6[5] = {0x3C,0x4A,0x49,0x49,0x30};
uint8_t* N_7[5] = {0x01,0x71,0x09,0x05,0x03};
uint8_t* N_8[5] = {0x36,0x49,0x49,0x49,0x36};
uint8_t* N_9[5] = {0x06,0x49,0x49,0x29,0x1E};

uint8_t* a_MI[5] = {0x20,0x54,0x54,0x54,0x78};
uint8_t* b_MI[5] = {0x7F,0x48,0x44,0x44,0x38};
uint8_t* c_MI[5] = {0x38,0x44,0x44,0x44,0x20};
uint8_t* d_MI[5] = {0x38,0x44,0x44,0x48,0x7F};
uint8_t* e_MI[5] = {0x38,0x54,0x54,0x54,0x18};
uint8_t* f_MI[5] = {0x08,0x7E,0x09,0x01,0x02};
uint8_t* g_MI[5] = {0x0C,0x52,0x52,0x52,0x3E};
uint8_t* h_MI[5] = {0x7F,0x08,0x04,0x04,0x78};
uint8_t* i_MI[5] = {0x00,0x44,0x7D,0x40,0x00};
uint8_t* j_MI[5] = {0x20,0x40,0x44,0x3D,0x00};
uint8_t* k_MI[5] = {0x7F,0x10,0x28,0x44,0x00};
uint8_t* l_MI[5] = {0x00,0x41,0x7F,0x40,0x00};
uint8_t* n_MI[5] = {0x7C,0x08,0x04,0x04,0x78};
uint8_t* o_MI[5] = {0x38,0x44,0x44,0x44,0x38};
uint8_t* p_MI[5] = {0x7C,0x14,0x14,0x14,0x08};
uint8_t* q_MI[5] = {0x08,0x14,0x14,0x14,0x7C};
uint8_t* r_MI[5] = {0x7C,0x08,0x04,0x04,0x08};
uint8_t* s_MI[5] = {0x48,0x54,0x54,0x54,0x20};
uint8_t* t_MI[5] = {0x04,0x3F,0x44,0x40,0x20};
uint8_t* u_MI[5] = {0x3C,0x40,0x40,0x20,0x7C};
uint8_t* v_MI[5] = {0x1C,0x20,0x40,0x20,0x1C};
uint8_t* w_MI[5] = {0x3C,0x40,0x30,0x40,0x3C};
uint8_t* x_MI[5] = {0x44,0x28,0x10,0x28,0x44};
uint8_t* y_MI[5] = {0x0C,0x50,0x50,0x50,0x3C};
uint8_t* z_MI[5] = {0x44,0x64,0x54,0x4C,0x44};

////////////////////////////////////////////////////////////////////////////////

void character(int fd, uint8_t** C[]){
	for(int i=0 ; i<4; i++){
        i2c_smbus_write_byte_data(fd, SET_START_LINE, C[i]);
    }
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00); 
}

#endif /* FONT_H_ */