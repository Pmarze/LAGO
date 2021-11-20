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
#define SET_DISP_OFFSET     0xD3  // display offset
#define DISPLAY_ON          0xAF
#define DISPLAY_OFF         0xAE  // micropi SET_DISP
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

#define INIT_STATUS         0xFF

////////////////////////////////////////////////////////////////////////////////


void page_data(int, int, int);
void initialize(int);
void abecedario(int, int, int);
void numeros(int, int, int);
void clear_lcd(int);

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
void Q_M(int);
void R_M(int);
void S_M(int);
void T_M(int);
void U_M(int);
void V_M(int);
void W_M(int);
void X_M(int);
void Y_M(int);
void Z_M(int);

void N_0(int);
void N_1(int);
void N_2(int);
void N_3(int);
void N_4(int);
void N_5(int);
void N_6(int);
void N_7(int);
void N_8(int);
void N_9(int);

////////////////////////////////////////////////////////////////////////////////

void page_data(int fd, int page_a, int column_a){
    i2c_smbus_write_byte_data(fd, 0x00, SET_PAGE_ADDR);
    i2c_smbus_write_byte_data(fd, 0x00, page_a);
    i2c_smbus_write_byte_data(fd, 0x00, INIT_STATUS);
    i2c_smbus_write_byte_data(fd, 0x00, SET_COLUMN_ADDR);
    i2c_smbus_write_byte_data(fd, 0x00, column_a);
    i2c_smbus_write_byte_data(fd, 0x00, 0x7f);
}

void initialize(int fd){
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

void numeros(int fd, int page, int column){
    page_data(fd, page, column);
    N_1(fd);
    N_2(fd);
    N_3(fd);
    N_4(fd);
    N_5(fd);
    N_6(fd);
    N_7(fd);
    N_8(fd);
    N_9(fd);
    N_0(fd);
}

void abecedario(int fd, int page, int column){
    page_data(fd, page, column);
    A_M(fd);
    B_M(fd);
    C_M(fd);
    D_M(fd);
    E_M(fd);
    F_M(fd);
    G_M(fd);
    H_M(fd);
    I_M(fd);
    J_M(fd);
    K_M(fd);
    L_M(fd);
    M_M(fd);
    N_M(fd);
    O_M(fd);
    P_M(fd);
    V_M(fd);
    W_M(fd);
    X_M(fd);
    Y_M(fd);
    Z_M(fd);
}

void clear_lcd(int fd){
    page_data(fd, 0x00, 0x00);
    for( int i = 0; i< 512; i++){
    i2c_smbus_write_byte_data(fd, 0x40, 0x00);
    }
}

////////////////////////////////////////////////////////////////////////////////

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
    space(fd);
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
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x45);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x39);  
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
/*
void _M(int fd){
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x);  
    i2c_smbus_write_byte_data(fd, SET_START_LINE, 0x00);  
}
*/


///////////////////////////////////////////////////////////////////////
static int iic_write(char *data, int offset, int size, int fd){

    /* variable declaration */
    int bytes_written;
    int write_bytes;
    int index;

    /* Check for limits */
    if(size > PAGESIZE){
        write_bytes = PAGESIZE;
    }else{
        write_bytes = size;
    }

    /* Number of needed loops to send all the data.
    * Limit data size per transmission is PAGESIZE */
    int loop = 0;

    while(size > 0){

        /* buffer size is PAGESIZE per transmission */
        uint8_t write_buffer[32 + 2];

        /*
        * Load the offset address inside EEPROM where data need to be written.
        * Supported for BigEndian and LittleEndian CPU's
        */
        write_buffer[0] = (uint8_t)(offset >> 8);
        write_buffer[1] = (uint8_t)(offset);

        for(index = 0; index < PAGESIZE; index++){
            write_buffer[index + 2] = data[index + (PAGESIZE * loop)];
        }

        /* Write the bytes onto the bus */
        bytes_written = write(fd, write_buffer, write_bytes + 2);
        /* Wait till the EEPROM internally completes the write cycle */
        sleep(2);

        if(bytes_written != write_bytes+2){
            fprintf(stderr, "Failed to write to EEPROM\n");
            return -1;
        }

        /* written bytes minus the offset addres of two */
        size -= bytes_written - 2;
        /* Increment offset */
        offset += PAGESIZE;

        /* Check for limits for the new message */
        if(size > PAGESIZE){
            write_bytes = PAGESIZE;
        }else{
            write_bytes = size;
        }

        loop++;
    }

    printf("\nWrite EEPROM Succesful\n");

    return 0;
}

static int iic_read(char *buffer, int offset, int size, int fd)
{
    ssize_t bytes_written;
    ssize_t bytes_read;
    uint8_t write_buffer[2];

    /*
    * Load the offset address inside EEPROM where data need to be written.
    * Supported for BigEndian and LittleEndian CPU's
    */
    write_buffer[0] = (uint8_t)(offset >> 8);
    write_buffer[1] = (uint8_t)(offset);

    /* Write the bytes onto the bus */
    bytes_written = write(fd, write_buffer, 2);
    if(bytes_written < 0){
        fprintf(stderr, "EEPROM write address error.\n");
        return -1;
    }

    /*
    * Read the bytes.
    */
    printf ("Performing Read operation.\n");

    /* Read bytes from the bus */
    bytes_read = read(fd, buffer, size);
    if(bytes_read < 0){
        fprintf(stderr, "EEPROM read error.\n");
        return -1;
    }

    printf("Read EEPROM Succesful\n");

    return 0;
}