/*
 * File:   UART.h
 * Author: Shane Ryan - sryan8@nd.edu
 * Purpose:  Header file to configure and start UART module.
 *
 * Created on April 28, 2016, 12:25 AM
 */

#define BAUDRATE 9600
#define FCY 7370000/2

void configPins(void);
void configUART1(void);
void outChar1(unsigned char c);
void my_puts(char *str);

void my_puts(char *str) {
    while (*str) {
        outChar1(*str);
        str++;
    }
}

void configPins(void) {
    RPINR18bits.U1RXR = 20;     // map UART1 RX to remappable pin RP20 (pin 12)
    RPOR1bits.RP36R = 1;        // map UART1 TX to remappable pin RP36 (pin 11)          
}

void outChar1(unsigned char c){
    while(U1STAbits.UTXBF);     // wait for transmit buffer to be empty
    U1TXREG = c;                // write character to transmit register
}

void configUART1(void) {
    /*  Calculate the Baud Rate generator value     */
    int brg = (FCY/BAUDRATE/4)-1;
    U1MODEbits.BRGH = 1;        // High speed mode
    U1BRG = brg;                // store the value in the register
    
    U1MODEbits.PDSEL = 0;       // 8 bit data, no parity
    U1MODEbits.STSEL = 0;       // 1 stop bit
    
    U1MODEbits.UEN = 0b00;      // UxTX and UxRX pins are enabled and used;
                                // also, no flow control pins
    U1MODEbits.UARTEN = 1;      // enable UART RX/TX
    U1STAbits.UTXEN = 1;        //Enable the transmitter
 
}