#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define OSS BMP180_STANDARD
#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit

///////////////////////////// Define BMP180 ////////////////////////////////////////////

//Operating Modes
#define BMP180_ULTRALOWPOWER    0
#define BMP180_STANDARD         1
#define BMP180_HIGHRES          2
#define BMP180_ULTRAHIGHRES     3

//BMP185 Registers
#define BMP180_CAL_AC1          0xAA  //Calibration data (16 bits)
#define BMP180_CAL_AC2          0xAC  //Calibration data (16 bits)
#define BMP180_CAL_AC3          0xAE  //Calibration data (16 bits)
#define BMP180_CAL_AC4          0xB0  //Calibration data (16 bits)
#define BMP180_CAL_AC5          0xB2  //Calibration data (16 bits)
#define BMP180_CAL_AC6          0xB4  //Calibration data (16 bits)
#define BMP180_CAL_B1           0xB6  //Calibration data (16 bits)
#define BMP180_CAL_B2           0xB8  //Calibration data (16 bits)
#define BMP180_CAL_MB           0xBA  //Calibration data (16 bits)
#define BMP180_CAL_MC           0xBC  //Calibration data (16 bits)
#define BMP180_CAL_MD           0xBE  //Calibration data (16 bits)
#define BMP180_CONTROL          0xF4
#define BMP180_TEMPDATA         0xF6
#define BMP180_PRESSUREDATA     0xF6

//Commands
#define BMP180_READTEMPCMD      0x2E
#define BMP180_READPRESSURECMD  0x34

short AC1,AC2,AC3,B1,B2,MB,MC,MD;
unsigned short AC4,AC5,AC6;


void typeFloat(float,int);
void typeInt(int,int);
void ClrLcd(int);
void lcdLoc(int,int);
void typeChar(char,int);
void typeln(const char *,int);
void lcd_byte(int,int,int);
void lcd_toggle_enable(int,int);
void lcd_init(int);
char I2C_readByte(int,int);
unsigned short I2C_readU16(int,int);
short I2C_readS16(int,int);
void I2C_writeByte(int,int,int);
void load_calibration(int);
int read_raw_temp(int);
int read_raw_pressure(int);
float read_temperature(int);
int read_pressure(int);
float read_altitude(int);
float read_sealevel_pressure(int);

///////////////////////////////// LCD /////////////////////////////////////////////////
// float to string
void typeFloat(float myFloat, int fd){
  char buffer[20];
  sprintf(buffer, "%4.2f",  myFloat);
  typeln(buffer,fd);
}
// int to string
void typeInt(int i, int fd){
  char array1[20];
  sprintf(array1, "%d",  i);
  typeln(array1, fd);
}

// clr lcd go home loc 0x80
void ClrLcd(int fd){
  lcd_byte(0x01, LCD_CMD, fd);    
  lcd_byte(0x02, LCD_CMD, fd);    
}

// go to location on LCD
void lcdLoc(int line, int fd){
  lcd_byte(line,LCD_CMD, fd);
}

// out char to LCD at current position
void typeChar(char val,int fd){

  lcd_byte(val, LCD_CHR, fd);
}

void typeln(const char *s, int fd){

  while ( *s ) lcd_byte(*(s++), LCD_CHR, fd);

}

void lcd_byte(int bits, int mode,int fd){

  //Send byte to data pins
  // bits = the data
  // mode = 1 for data, 0 for command
  int bits_high;
  int bits_low;
  // uses the two half byte writes to LCD
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

  // High bits
  wiringPiI2CReadReg8(fd, bits_high);
  lcd_toggle_enable(bits_high,fd);

  // Low bits
  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(bits_low,fd);
}

void lcd_toggle_enable(int bits, int fd){
  // Toggle enable pin on LCD display
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

void lcd_init(int fd){
  // Initialise display
  lcd_byte(0x33, LCD_CMD,fd); // Initialise
  lcd_byte(0x32, LCD_CMD,fd); // Initialise
  lcd_byte(0x06, LCD_CMD,fd); // Cursor move direction
  lcd_byte(0x0C, LCD_CMD,fd); // 0x0F On, Blink Off
  lcd_byte(0x28, LCD_CMD,fd); // Data length, number of lines, font size
  lcd_byte(0x01, LCD_CMD,fd); // Clear display
  delayMicroseconds(500);
}

//////////////////////////////// BMP 180 //////////////////////////////////////////////
char I2C_readByte(int reg, int fd){
    return (char)wiringPiI2CReadReg8(fd,reg);
}

unsigned short I2C_readU16(int reg, int fd){
    int MSB,LSB;
    MSB = I2C_readByte(reg, fd);
    LSB = I2C_readByte(reg + 1, fd);
    int value = (MSB << 8) +LSB;
    return (unsigned short)value;
}

short I2C_readS16(int reg,int fd){
    int result;
    result = I2C_readU16(reg,fd);
    if (result > 32767)result -= 65536;
    return (short)result;
}

void I2C_writeByte(int reg,int val,int fd){
    wiringPiI2CWriteReg8(fd,reg,val);
}

void load_calibration(int fd){
    AC1 = I2C_readS16(BMP180_CAL_AC1,fd);
    AC2 = I2C_readS16(BMP180_CAL_AC2,fd);
    AC3 = I2C_readS16(BMP180_CAL_AC3,fd);
    AC4 = I2C_readU16(BMP180_CAL_AC4,fd);
    AC5 = I2C_readU16(BMP180_CAL_AC5,fd);
    AC6 = I2C_readU16(BMP180_CAL_AC6,fd);
    B1  = I2C_readS16(BMP180_CAL_B1,fd);
    B2  = I2C_readS16(BMP180_CAL_B2,fd);
    MB  = I2C_readS16(BMP180_CAL_MB,fd);
    MC  = I2C_readS16(BMP180_CAL_MC,fd);
    MD  = I2C_readS16(BMP180_CAL_MD,fd);
}

int read_raw_temp(int fd){
    int raw;
    I2C_writeByte(BMP180_CONTROL,BMP180_READTEMPCMD, fd);
    delay(5);  //5ms;
    raw = I2C_readByte(BMP180_TEMPDATA, fd) << 8;
    raw += I2C_readByte(BMP180_TEMPDATA+1, fd);
    return raw;
}

int read_raw_pressure(int fd){
    int MSB,LSB,XLSB,raw;
    I2C_writeByte(BMP180_CONTROL,BMP180_READPRESSURECMD +(OSS << 6), fd);
    switch(OSS)
    {
        case BMP180_ULTRALOWPOWER:
            delay(5);break;
        case BMP180_HIGHRES:
            delay(14);break;
        case BMP180_ULTRAHIGHRES:
            delay(26);break;
        default :
            delay(8);
    }
    MSB  = I2C_readByte(BMP180_PRESSUREDATA, fd);
    LSB  = I2C_readByte(BMP180_PRESSUREDATA + 1, fd);
    XLSB = I2C_readByte(BMP180_PRESSUREDATA + 2, fd);
    raw = ((MSB << 16) + (LSB << 8) + XLSB) >> (8 - OSS);
    return raw;
}

float read_temperature(int fd){
    float T;
    int UT,X1,X2,B5;
    UT = read_raw_temp(fd);
    X1 = ((UT - AC6)*AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    T = ((B5 + 8) >> 4) /10.0;
    return T;
}

int read_pressure(int fd){
    int P;
    int UT,UP,X1,X2,X3,B3,B5,B6;
    unsigned int B4;
    int B7;
    UT = read_raw_temp(fd);
    UP = read_raw_pressure(fd);

    X1 = ((UT - AC6)*AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;

    //Pressure Calculations
    B6 = B5 - 4000;
    X1 = (B2 * (B6 * B6) >> 12) >> 11;
    X2 = (AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((AC1 * 4 + X3) << OSS) + 2) / 4;
    X1 = (AC3 * B6) >> 13;
    X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (AC4 * (X3 + 32768)) >> 15;
    B7 = (UP - B3) * (50000 >> OSS);
    if (B7 < 0x80000000){P = (B7 * 2) / B4;}
    else {P = (B7 / B4) * 2;}
    X1 = (P >> 8) * (P >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * P) >> 16;
    P = P + ((X1 + X2 + 3791) >> 4);
    return P;
}

float read_altitude(int fd){
    float pressure,altitude;
    float sealevel_pa = 101325.0;
    pressure = (float)read_pressure(fd);
    altitude = 44330.0 * (1.0 - pow(pressure / sealevel_pa,(1.0/5.255)));
    return altitude;
}

float read_sealevel_pressure(int fd){
    float altitude_m = 0.0;
    float pressure,p0;
    pressure =(float)read_pressure(fd);
    p0 = pressure / pow(1.0 - altitude_m/44330.0,5.255);
    return p0;
}

///////////////////////////////////////////////////////////////////////////////////////
