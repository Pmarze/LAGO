/* @brief This is a simple application for testing IIC communication on a RedPitaya
* @Author Luka Golinar <luka.golinar@redpitaya.com>
*
* (c) Red Pitaya  http://www.redpitaya.com
*
* This part of code is written in C programming language.
* Please visit http://en.wikipedia.org/wiki/C_(programming_language)
* for more details on the language used herein.
*/


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

//#define I2C_SLAVE_FORCE                0x0706
//#define I2C_SLAVE                              0x0703    /* Change slave address            */
//#define I2C_FUNCS                              0x0705    /* Get the adapter functionality */
//#define I2C_RDWR                               0x0707    /* Combined R/W transfer (one stop only)*/


//#define OLED96_ADDR                    0x78
//#define OLED96_ADDR                    0x7a
#define OLED96_ADDR                    0x3c


/*
* Page size of the EEPROM. This depends on the type of the EEPROM available
* on board.
*/
#define PAGESIZE                   32
/* eeprom size on a redpitaya */
//#define EEPROMSIZE                 64*1024/8

////////////////////////////////////////////////////////////////////////////////
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

#define INIT_STATUS         0xFF

////////////////////////////////////////////////////////////////////////////////

/* Inline functions definition */
static int iic_read(char *buffer, int offset, int size);
static int iic_write(char *data, int offset, int size);

/*
* File descriptors
*/
int fd;

int main(int argc, char *argv[])
{
    int status;

    /* Read buffer to hold the data */
    //char *buffer = (char *)malloc(EEPROMSIZE * sizeof(char));

    //char data[] = "THIS IS A TEST MESSAGE FOR THE I2C PROTOCOL COMMUNICATION WITH A EEPROM. IT WAS WRITTEN FOR A
    //REDPITAYA MEASURMENT TOOL.";
    //size_t size = strlen(data);

    /* Sample offset inside an eeprom */
    //int offset = 0x100;

    /*
    * Open the device.
    */
    fd = open("/dev/i2c-0", O_RDWR);

    if(fd < 0)
    {
        printf("Cannot open the IIC device\n");
        return 1;
    }

    status = ioctl(fd, I2C_SLAVE, OLED96_ADDR);
    if(status < 0)
    {
        printf("Unable to set the OLED96 address\n");
        return -1;
    }
    char buf[10];
    buf[0] = SET_OSC_FREQ;
    buf[1] = DISPLAY_OFF;
    if ( i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_OFF) < 0 )
    {
        printf("Unable to send commands\n");
        printf("errno: %i %s\n",errno,strerror(errno));
        return -1;
    }
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
    i2c_smbus_write_byte_data(fd, 0x00, 0x02);
    i2c_smbus_write_byte_data(fd, 0x00, SET_CONTRAST);
    i2c_smbus_write_byte_data(fd, 0x00, 0x8f);
    i2c_smbus_write_byte_data(fd, 0x00, SET_PRECHARGE);
    i2c_smbus_write_byte_data(fd, 0x00, 0xf1);
    i2c_smbus_write_byte_data(fd, 0x00, 0xd8);
    i2c_smbus_write_byte_data(fd, 0x00, SET_START_LINE);
    i2c_smbus_write_byte_data(fd, 0x00, SET_ENTIRE_ON);
    i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_NORMAL);
    i2c_smbus_write_byte_data(fd, 0x00, DEACT_SCROLL);
    i2c_smbus_write_byte_data(fd, 0x00, DISPLAY_ON);


    i2c_smbus_write_byte_data(fd, 0x00, SET_PAGE_ADDR);
    i2c_smbus_write_byte_data(fd, 0x00, 0x00);
    i2c_smbus_write_byte_data(fd, 0x00, INIT_STATUS);
    i2c_smbus_write_byte_data(fd, 0x00, SET_COLUMN_ADDR);
    i2c_smbus_write_byte_data(fd, 0x00, 0x00);
    i2c_smbus_write_byte_data(fd, 0x00, 0x7f);



    for( int i = 0; i< 512; i++){
        i2c_smbus_write_byte_data(fd, 0x40, 0x00);
    }

    sleep(1);

    i2c_smbus_write_byte_data(fd, 0x00, 0x22);
    i2c_smbus_write_byte_data(fd, 0x00, 0x00);
    i2c_smbus_write_byte_data(fd, 0x00, 0xff);
    i2c_smbus_write_byte_data(fd, 0x00, 0x21);
    i2c_smbus_write_byte_data(fd, 0x00, 0x00);
    i2c_smbus_write_byte_data(fd, 0x00, 0x7f);


    for( int i = 0; i< 32; i++){
        i2c_smbus_write_byte_data(fd, 0x40, 0x0f);
    }

    sleep(1);

    for( int i = 0; i< 32; i++){
        i2c_smbus_write_byte_data(fd, 0x40, 0x00);
    }

    sleep(1);

    for( int i = 0; i< 32; i++){
        i2c_smbus_write_byte_data(fd, 0x40, 0xf0);
    }

    /* Write to redpitaya eeprom */
    //status = iic_write((char *)data, offset, size);
    //if(status){
    //    fprintf(stderr, "Cannot Write to EEPROM\n");
    //    close(fd);
    //    return -1;
    //}

    /* Read from redpitaya eeprom */
    //status = iic_read(buffer, EEPROM_ADDR, EEPROMSIZE);
    //if (status)
    //{
    //    printf("Cannot Read from EEPROM \n");
    //    close(fd);
    //    return 1;
    //}

    //printf("eerprom test successfull.\n");

    sleep(1);

    /* Release allocations */
    close(fd);
    //free(buffer);

    return 0;
}

/* Read the data from the EEPROM.
*
*  @param    read buffer -- input buffer for data storage
*  @param    off set     -- eeprom memory space offset
*  @param    size        -- size of read data
*  @return   iicRead status
*
*  @note     None. */


static int iic_read(char *buffer, int offset, int size)
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


static int iic_write(char *data, int offset, int size){

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