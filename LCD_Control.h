/*
 * File:   LCD_Control.h
 * Author: Shane Ryan - sryan8@nd.edu
 * 
 * Header file that can be used to manipulate a Nokia LCD 84 x 48 
 * display matrix to print out dynamic values and display current
 * user settings.  Pre-configured to function as a thermostat 
 * control display.
 *
 * Created on April 26, 2016, 9:52 PM
 * Completed on April 27, 2016, 1:27 AM
 */

typedef unsigned char LCDBYTE;

/* NOTE:  This header file utilizes SPI2:  pin 15 = SDO, pin 16 = SCK  ********/
/* I have pin 5 (RPI33) as SDI, however, you can remap this to any unused pin */
/***********************************/
/*   Functions available for use   */
/***********************************/

/*  All steps needed to configure the LCD are included in this bad boy  */
void LCDInit(void);

/*  Clear the entire screen and start printing at the top cell  */
void LCDClear(void);

/*  Sends a byte signaling data or command to screen, followed by one byte  */
void LCDWrite(LCDBYTE, LCDBYTE);

/*  Prints a char on screen starting with the next available cell   */
void LCDCharacter(char);

/*  Prints a string on screen starting with next available cell */
void LCDString(char *input);

/*  Prints 12 blanks, starting with current cell, useful to offset info */
void LCDCarriageReturn(void);

/*  My simple version of the itoa() function in stdlib, convert int to string */
void itoa(unsigned int value, char *buffer);

/*  And now.... */
/*----THE MOTHER FUNCTION-----*/
/*  Accepts three temperature values, and prints them on a fancy template   */
void LCDTemp(unsigned int temp, unsigned int high, unsigned int low, unsigned 
    char state);

/**********************************/


/* Need the following, which are usually included in main file:
#include "p24EP128GP202.h"
#include "my_config.h" */


// Pins for LCD Control Signals
#define LCD_SCE LATBbits.LATB10
#define LCD_SCE_PIN TRISBbits.TRISB10
#define LCD_RESET LATBbits.LATB11
#define LCD_RESET_PIN TRISBbits.TRISB11
#define LCD_DC LATBbits.LATB12
#define LCD_DC_PIN TRISBbits.TRISB12

// Pins for SPI2
#define USESPI2 
#define USESCK2 RPOR2bits.RP39R = 9; // RP39 is SCK2
#define USESDO2 RPOR2bits.RP38R = 8;  // RP38 is SDO2
#define USESDI2 RPINR22bits.SDI2R = 33; // RPI33 is SDI2

#define IN 1
#define OUT 0

#define LOW 0
#define HIGH 1

#define LCD_COMMAND     LOW
#define LCD_DATA        HIGH

char *phrases[] = {
    "Shane's Temp", "*=--------=*",
    "  Cooling   ", "  Heating   ",
    "Temp:   ", "Temp Range",
    "H:", "L:", "Hello World!",
    "Modify H / L"
};

static const LCDBYTE ASCII[][5] ={
    {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
    ,
    {0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
    ,
    {0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
    ,
    {0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
    ,
    {0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
    ,
    {0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
    ,
    {0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
    ,
    {0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
    ,
    {0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
    ,
    {0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
    ,
    {0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
    ,
    {0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
    ,
    {0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
    ,
    {0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
    ,
    {0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
    ,
    {0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
    ,
    {0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
    ,
    {0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
    ,
    {0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
    ,
    {0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
    ,
    {0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
    ,
    {0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
    ,
    {0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
    ,
    {0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
    ,
    {0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
    ,
    {0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
    ,
    {0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
    ,
    {0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
    ,
    {0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
    ,
    {0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
    ,
    {0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
    ,
    {0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
    ,
    {0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
    ,
    {0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
    ,
    {0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
    ,
    {0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
    ,
    {0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
    ,
    {0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
    ,
    {0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
    ,
    {0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
    ,
    {0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
    ,
    {0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
    ,
    {0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
    ,
    {0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
    ,
    {0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
    ,
    {0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
    ,
    {0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
    ,
    {0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
    ,
    {0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
    ,
    {0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
    ,
    {0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
    ,
    {0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
    ,
    {0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
    ,
    {0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
    ,
    {0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
    ,
    {0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
    ,
    {0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
    ,
    {0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
    ,
    {0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
    ,
    {0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
    ,
    {0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
    ,
    {0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
    ,
    {0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
    ,
    {0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
    ,
    {0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
    ,
    {0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
    ,
    {0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
    ,
    {0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
    ,
    {0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
    ,
    {0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
    ,
    {0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
    ,
    {0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
    ,
    {0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
    ,
    {0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
    ,
    {0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
    ,
    {0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
    ,
    {0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
    ,
    {0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
    ,
    {0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
    ,
    {0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
    ,
    {0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
    ,
    {0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
    ,
    {0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
    ,
    {0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
    ,
    {0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
    ,
    {0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
    ,
    {0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
    ,
    {0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
    ,
    {0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
    ,
    {0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
    ,
    {0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
    ,
    {0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
    ,
    {0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
    ,
    {0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
    ,
    {0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
    ,
    {0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};

void LCDWrite(LCDBYTE dc, LCDBYTE data) {
    LCD_SCE = LOW; // Select LCD panel
    LCD_DC = dc; // Indicate Data/Command signal

    SPI2BUF = data; // Put data in output buffer for SPI2
    while (!SPI2STATbits.SPIRBF) {
    } // wait for it to send

    Nop(); // A little extra wait time
    LCD_SCE = HIGH; // Deselect LCD panel

}

void LCDClear(void) {
    int index;
    for (index = 0; index < 84 * 6; index++) { // 84 columns, 48 / 8 rows
        LCDWrite(LCD_DATA, 0x00); // write blanks   // (due to chars taking 8)
    }
}

void LCDCarriageReturn(void) {
    int index;
    for (index = 0; index < 84; index++) {
        LCDWrite(LCD_DATA, 0x00);
    }
}

void LCDString(char *input) {
    while (*input) {
        LCDCharacter(*input);
        input++;
    }
}

void LCDUserScreen(unsigned char high_low, unsigned int high, unsigned int low) {
    char high_buff[6];
    char low_buff[6];

    itoa(high, high_buff);
    itoa(low, low_buff);

    LCDClear();
    LCDString(phrases[0]);
    LCDString(phrases[1]);
    LCDCarriageReturn();
    LCDString(phrases[9]);

    LCDCarriageReturn();
    LCDString(phrases[6]);

    if (high_low == 1) {
        LCDCharacter('*');
    }
    else {
        LCDCharacter(' ');
    }

    if (high <= 10) {
        LCDCharacter('0');
        LCDCharacter(high_buff[1]);
    } else {
        LCDCharacter(high_buff[0]);
        LCDCharacter(high_buff[1]);
    }

    LCDCharacter(' ');
    LCDString(phrases[7]);
    
    if (high_low == 2) {
        LCDCharacter('*');
    }
    else {
        LCDCharacter(' ');
    }

    if (low < 10) {
        LCDCharacter('0');
        LCDCharacter(low_buff[1]);
    } else {
        LCDCharacter(low_buff[0]);
        LCDCharacter(low_buff[1]);
    }

    LCDCharacter(' ');
}

void LCDTemp(unsigned int temp, unsigned int high, unsigned int low, unsigned
    char state) {

    char temp_buff[6];
    char high_buff[6];
    char low_buff[6];

    itoa(temp, temp_buff);
    itoa(high, high_buff);
    itoa(low, low_buff);

    LCDClear();
    LCDString(phrases[0]);
    LCDString(phrases[1]);
    
    switch (state) {
        case 0:
            LCDCarriageReturn();
            break;
        case 1:
            LCDString(phrases[3]);
           // my_puts(state_update[5]);
            break;
        case 2:
            LCDString(phrases[2]);
           // my_puts(state_update[4]);
            break;
    }


    LCDString(phrases[4]);

    if (temp <= 10) {
        LCDCharacter('0');
        LCDCharacter(temp_buff[1]);
    } else {
        LCDCharacter(temp_buff[0]);
        LCDCharacter(temp_buff[1]);
    }

    LCDCharacter(' ');
    LCDCharacter(' ');

    LCDCarriageReturn();
    LCDString(phrases[6]);
    LCDCharacter(' ');

    if (high <= 10) {
        LCDCharacter('0');
        LCDCharacter(high_buff[1]);
    } else {
        LCDCharacter(high_buff[0]);
        LCDCharacter(high_buff[1]);
    }

    LCDCharacter(' ');
    LCDString(phrases[7]);
    LCDCharacter(' ');

    if (low <= 10) {
        LCDCharacter('0');
        LCDCharacter(low_buff[1]);
    } else {
        LCDCharacter(low_buff[0]);
        LCDCharacter(low_buff[1]);
    }

    LCDCharacter(' ');
}

void itoa(unsigned int value, char *buffer) {

    int c = sizeof (buffer) - 1;
    buffer[c] = 0; // indicate end of char array wtih null

    do {
        buffer[c--] = (value % 10) + '0'; // modulus + ASCII 0 = char digit
        value = value / 10; // rest of the digits stem here
    } while (value);

}

void LCDCharacter(char character) {
    int index;
    LCDWrite(LCD_DATA, 0x00);
    for (index = 0; index < 5; index++) {
        LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
    }
    LCDWrite(LCD_DATA, 0x00);
}

void LCDInit(void) {
    LCD_SCE_PIN = OUT;
    LCD_RESET_PIN = OUT;
    LCD_DC_PIN = OUT;

    SPI1STATbits.SPIEN = 0; // explicitly disable SP1 to prevent interference
    USESCK2;
    USESDO2;
    USESDI2;

    SPI2CON1bits.MSTEN = 1; // make master
    SPI2CON1bits.PPRE = 0b11; // 1:1 primary prescale
    SPI2CON1bits.SPRE = 0b111; // 1:1 secondary prescale
    SPI2CON1bits.MODE16 = 0; // 8-bit transfer mode
    SPI2CON1bits.SMP = 0; // sample in middle
    SPI2CON1bits.CKE = 1; // Output on falling edge
    SPI2CON1bits.CKP = 0; // CLK idle state low
    SPI2STATbits.SPIEN = 1; // enable SPI2

    LCD_RESET = LOW;
    LCD_RESET = HIGH;

    LCDWrite(LCD_COMMAND, 0x21); // LCD Extended Commands
    LCDWrite(LCD_COMMAND, 0xBA); // Set LCD Vop (Contrast)
    LCDWrite(LCD_COMMAND, 0x04); // Set Temp coefficent. //0x04
    LCDWrite(LCD_COMMAND, 0x14); // LCD bias mode 1:48. //0x13
    LCDWrite(LCD_COMMAND, 0x20); // LCD Basic Commands
    LCDWrite(LCD_COMMAND, 0x0C); // LCD in normal mode.

    LCDClear();
}