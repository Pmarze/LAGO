/*
*
* by Lewis Loflin www.bristolwatch.com lewis@bvu.net
* http://www.bristolwatch.com/rpi/i2clcd.htm
* Using wiringPi by Gordon Henderson
*
*
* Port over lcd_i2c.py to C and added improvements.
* Supports 16x2 and 20x4 screens.
* This was to learn now the I2C lcd displays operate.
* There is no warrenty of any kind use at your own risk.
*
*/

#include <wiringPiI2C.h>    // lcd & 180
#include <wiringPi.h>       // lcd & 180
#include <stdio.h>          // lcd & 180
#include <stdlib.h>         // lcd
#include <math.h>           // 180
#include "bmp180.h"         // 180

// Define some device parameters
#define I2C_ADDR   0x26 // I2C device address

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit
#define OSS BMP180_STANDARD     

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeln(const char *s);
void typeChar(char val);
int fd;  // seen by all subroutines
int i,t;  // variables para conteo de repetición y tiempo de delay


short AC1,AC2,AC3,B1,B2,MB,MC,MD;
unsigned short AC4,AC5,AC6;
int fd;


///////////////////////////////////////////////////////////////////////////////////////
int main()   {

  if (wiringPiSetup () == -1) exit (1);

  fd = wiringPiI2CSetup(I2C_ADDR);

  //printf("fd = %d ", fd);

  lcd_init(); // setup LCD

  char array1[] = "Hello world!";

  t=1000;
  while (i<3)   {

    lcdLoc(LINE1);
    typeln("Using wiringPi");
    lcdLoc(LINE2);
    typeln("Geany editor.");
    delay(t);
    ClrLcd();

    lcdLoc(LINE1);
    typeln("Texto 2");
    lcdLoc(LINE2);
    typeln("probando 1,2,3");
    delay(t);
    ClrLcd();
    i++;
  }
  
  ClrLcd();
  return 0;

}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// LCD /////////////////////////////////////////////////
// float to string
void typeFloat(float myFloat)   {
  char buffer[20];
  sprintf(buffer, "%4.2f",  myFloat);
  typeln(buffer);
}

// int to string
void typeInt(int i)   {
  char array1[20];
  sprintf(array1, "%d",  i);
  typeln(array1);
}

// clr lcd go home loc 0x80
void ClrLcd(void)   {
  lcd_byte(0x01, LCD_CMD);
  lcd_byte(0x02, LCD_CMD);
}

// go to location on LCD
void lcdLoc(int line)   {
  lcd_byte(line, LCD_CMD);
}

// out char to LCD at current position
void typeChar(char val)   {

  lcd_byte(val, LCD_CHR);
}


// this allows use of any size string
void typeln(const char *s)   {

  while ( *s ) lcd_byte(*(s++), LCD_CHR);

}

void lcd_byte(int bits, int mode)   {

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
  lcd_toggle_enable(bits_high);

  // Low bits
  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits)   {
  // Toggle enable pin on LCD display
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}


void lcd_init()   {
  // Initialise display
  lcd_byte(0x33, LCD_CMD); // Initialise
  lcd_byte(0x32, LCD_CMD); // Initialise
  lcd_byte(0x06, LCD_CMD); // Cursor move direction
  lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
  lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
  lcd_byte(0x01, LCD_CMD); // Clear display
  delayMicroseconds(500);
}
///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// 180 ////////////////////////////////////////////////
char I2C_readByte(int reg)
{
    return (char)wiringPiI2CReadReg8(fd,reg);
}

unsigned short I2C_readU16(int reg)
{
    int MSB,LSB;
    MSB = I2C_readByte(reg);
    LSB = I2C_readByte(reg + 1);
    int value = (MSB << 8) +LSB;
    return (unsigned short)value;
}

short I2C_readS16(int reg)
{
    int result;
    result = I2C_readU16(reg);
    if (result > 32767)result -= 65536;
    return (short)result;
}
void I2C_writeByte(int reg,int val)
{
    wiringPiI2CWriteReg8(fd,reg,val);
}

void load_calibration()
{
    AC1 = I2C_readS16(BMP180_CAL_AC1);
    AC2 = I2C_readS16(BMP180_CAL_AC2);
    AC3 = I2C_readS16(BMP180_CAL_AC3);
    AC4 = I2C_readU16(BMP180_CAL_AC4);
    AC5 = I2C_readU16(BMP180_CAL_AC5);
    AC6 = I2C_readU16(BMP180_CAL_AC6);
    B1  = I2C_readS16(BMP180_CAL_B1);
    B2  = I2C_readS16(BMP180_CAL_B2);
    MB  = I2C_readS16(BMP180_CAL_MB);
    MC  = I2C_readS16(BMP180_CAL_MC);
    MD  = I2C_readS16(BMP180_CAL_MD);
}
int read_raw_temp()
{
    int raw;
    I2C_writeByte(BMP180_CONTROL,BMP180_READTEMPCMD);
    delay(5);  //5ms;
    raw = I2C_readByte(BMP180_TEMPDATA) << 8;
    raw += I2C_readByte(BMP180_TEMPDATA+1);
    return raw;

}
int read_raw_pressure()
{
    int MSB,LSB,XLSB,raw;
    I2C_writeByte(BMP180_CONTROL,BMP180_READPRESSURECMD +(OSS << 6));
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
    MSB  = I2C_readByte(BMP180_PRESSUREDATA);
    LSB  = I2C_readByte(BMP180_PRESSUREDATA + 1);
    XLSB = I2C_readByte(BMP180_PRESSUREDATA + 2);
    raw = ((MSB << 16) + (LSB << 8) + XLSB) >> (8 - OSS);
    return raw;
}
float read_temperature()
{
    float T;
    int UT,X1,X2,B5;
    UT = read_raw_temp();
    X1 = ((UT - AC6)*AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    T = ((B5 + 8) >> 4) /10.0;
    return T;
}

int read_pressure()
{
    int P;
    int UT,UP,X1,X2,X3,B3,B5,B6;
    unsigned int B4;
    int B7;
    UT = read_raw_temp();
    UP = read_raw_pressure();

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
float read_altitude()
{
    float pressure,altitude;
    float sealevel_pa = 101325.0;
    pressure = (float)read_pressure();
    altitude = 44330.0 * (1.0 - pow(pressure / sealevel_pa,(1.0/5.255)));
    return altitude;
}
float read_sealevel_pressure()
{
    float altitude_m = 0.0;
    float pressure,p0;
    pressure =(float)read_pressure();
    p0 = pressure / pow(1.0 - altitude_m/44330.0,5.255);
    return p0;
}
///////////////////////////////////////////////////////////////////////////////////////