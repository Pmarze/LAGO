#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SUCCESS     0
#define ERROR       1
#define ADDRES      0x3C

// Command definition
#define SET_MUX_RATIO       0xA8
#define SET_DISP_OFFSET     0xD3  // display offset
#define DISPLAY_ON          0xAF
#define DISPLAY_OFF         0xAE   // micropi SET_DISP
#define SET_ENTIRE_ON       0xA4  // entire display on
#define DISPLAY_IGN_RAM     0xA5  // display ingnore RAM
#define DISPLAY_NORMAL      0xA6  // display normal micropi SET_NORM_INV
#define DISPLAY_INVERSE     0xA7  // display inverse
#define DEACT_SCROLL        0x2E  // desactivate scroll 
#define ACTIVE_SCROLL       0x2F  
#define SET_START_LINE      0x40  // Set display start line
#define MEMORY_ADDR_MODE    0x20  // Set memory address micropi SET_MEM_ADDR
#define SET_COLUMN_ADDR     0x21  // set column addres
#define SET_PAGE_ADDR       0x22  // set page address
#define SET_SEG_REMAP       0xA0  // set segment remap (column address 0 is mapped to SEG0 (RESET))
#define SET_SEG_REMAP_OP    0xA1  // set segment remap (column address 127 is mapped to SEG0)
#define COM_SCAN_DIR        0xC0  // Set COM output scan direction (normal mode (RESET) Scan from COM0 to COM[N –1]) micropi SET_COM_OUT_DIR
#define COM_SCAN_DIR_OP     0xC8  // Set COM output scan direction (remapped mode. Scan from COM[N-1] to COM0)
#define SET_COM_PIN_CFG     0xDA  // Set COM pins Hardware configuration 
#define SET_CONTRAST        0x81  // Set contrast control
#define SET_OSC_FREQ        0xD5  // micropi SET_DISP_CLK_DIV
#define SET_CHAR_REG        0x8D  // Charge pump setting micropi SET_CHARGE_PUMP
#define SET_PRECHARGE       0xD9  // Set pre-charge Period
#define SET_VCOM_DESEL      0xDB  // Set VcomH deselect level micropi SET_VCOM_DESEL

// Clear color
#define CLEAR_COLOR         0x00

//  Init status
#define INIT_STATUS         0xFF

// AREA definition
#define START_PAGE_ADDR     0
#define END_PAGE_ADDR       7
#define START_COLUMN_ADDR   0
#define END_COLUMN_ADDR     127

#define CACHE_SIZE_MEM      (1 + END_PAGE_ADDR) * (1 + END_COLUMN_ADDR)

#define MAX_X               END_COLUMN_ADDR
#define MAX_Y               (END_PAGE_ADDR+1)*8

const uint8_t INIT_SSD1306[]={
  // number of initializers
    18,
    0, DISPLAY_OFF,
    1, SET_MUX_RATIO, 0x3F,
  // -----------------------------------
  // 0x00 - Horizontal Addressing Mode
  // 0x01 - Vertical Addressing Mode
  // 0x02 - Page Addressing Mode (RESET)
    1, MEMORY_ADDR_MODE, 0X00,
    2, SET_COLUMN_ADDR, START_PAGE_ADDR, END_PAGE_ADDR,
    0, SET_PAGE_ADDR, START_PAGE_ADDR, END_PAGE_ADDR,
    0, SET_START_LINE,
    1, SET_DISP_OFFSET, 0x00,
    0, SET_SEG_REMAP_OP,
    0, COM_SCAN_DIR_OP,
    1, SET_COM_PIN_CFG, 0x12,
    1, SET_CONTRAST, 0X7F,
    0, SET_ENTIRE_ON,
    0, DISPLAY_NORMAL,
    1, SET_OSC_FREQ, 0x80,
    1, SET_PRECHARGE, 0xC2,
    1, SET_VCOM_DESEL, 0x20,
    1, SET_CHAR_REG, 0x14,
    0, DISPLAY_ON
};

static char cacheMemLCD[CACHE_SIZE_MEM];

void main(){
  printf("hola mundo xd\n");
}