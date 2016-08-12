/* 
 * File:   wash_interface.c
 * Author: Shane Ryan - sryan8@nd.edu
 * Purpose: Interface with a network of washers and dryers.  Act as a 
 * supplementary master in order to observe devices statuses and use silent
 * time on the serial line to inject commands.
 *
 * Created on April 29, 2016, 2:10 PM
 */

#include "xc.h"
#include "my_config.h"


#define IDLE 0
#define ACTIVE 1
#define EXIT_SUCCESS 0
#define DEBUG 0
#define INQUIRY 0
#define WASH 1
#define SEND_ALL 0

unsigned int machine_status[17] = {IDLE};
char machine = 1;
char mode = 0;
unsigned int status_test = 0x0511;          // 17 machines, 16 bits
                                            // 0 = idle, 1 = active
char *state_update[] = {
    "  OpenWash  ", "*=--------=*",
    "Created by: ", " Shane Ryan ",
    " ver. 1.0a  ", "  Welcome!  ",
    "Machine ", " E: In Use! ",
    "W: ", "D: ",
    "W = Washer  ", "D = Dryer   ",
    "'*' = Active", "' ' = Free  ",
    "Two-Button  ", "push4 choose",
    " PICk", "Sending...  "
};

/*************************** COMMAND SET  *************************************/
char master_inquiry[] = {0x02, 0x00, 0x01, 0x03, 0x00, 0x06};
    // add ID number to second byte and last byte, i.e. 0x01 and 0x07 for #1

char slave_idle[] = {0x02, 0x00, 0x01, 0x01, 0x03, 0x00, 0x07};
    // this is a universal response to the master, regardless of address

char slave_active[] = {0x02, 0x00, 0x01, 0x00, 0x03, 0x00,0x06};
    // this is a universal response to the master, regardless of address

char slave_ack[] = {0x02, 0x00, 0x06, 0x03, 0x00, 0x0B};
    // this is a universal response to the master, regardless of address

char master_wash[] =
    {0x02, 0x00, 0x02, 0x08, 0x00, 0x18, 0x00, 0xFA, 0x03, 0x01, 0x21};
    // add ID number to second byte and last byte, i.e. 0x01 and 0x22 for #1
/******************************************************************************/

void LCDSplashScreen(void);
void LCDStatusScreen(unsigned int *machine_status);
void LCDInstructions(void);
void Initialize(void);
void StatusTest(unsigned int test_value);
void MasterSend(char cmd, char machine);
void SelectWasher(char machine);
void LCDSending(void);

#include "UART.h"
#include "LCD_Control.h"
#include "Buttons.h"
#include "ISRs.h"


int main(void) {
    
    int i = 0;
    int j = 0;
    
    StatusTest(status_test);
    Initialize();
        
    if (SEND_ALL) {
        for (i=1;i<18;i++) {
            MasterSend(WASH, i);
            for (j=0;j<3000;j++);
        }
    }
    
    while(1) {
        // inquire and collect responses on uart
        // if there's a change in status_test, update screen
    }
    
    return (EXIT_SUCCESS);
}

void Initialize(void) {
    int i = 0;
    int j = 0;
    pin_setup();        // setup pins for buttons and PWM output
    timer_setup();      // config timer module for button interrupts   
    configPins();       // setup inputs / outputs, remap pins, etc.
    configUART1();      // config UART module
    LCDInit();          // initialize LCD screen over SPI and clear
    if (!DEBUG) {
        LCDSplashScreen();  // display startup screen
        for(i=0;i<15000;i++) {
            for(j=0;j<100;j++);
        }
        LCDInstructions();
        for(i=0;i<15000;i++) {
            for(j=0;j<150;j++);
        }   
    }
    LCDStatusScreen(machine_status);
}

void StatusTest(unsigned int test_value) {
    int i = 0;    
    for (i = 0; i < 17; i++) {
        if (0x01 & test_value) {
            machine_status[i] = 1;
        }
        test_value = test_value >> 1;
    }
}

void LCDSplashScreen(void) {
    LCDClear();
    LCDString(state_update[0]);
    LCDString(state_update[1]);
    LCDString(state_update[5]);
    LCDCarriageReturn();
    LCDString(state_update[3]);
    LCDString(state_update[4]);
}

void LCDInstructions(void) {
    int i = 0;
    LCDClear();
    for (i=10;i<16;i++) {
        LCDString(state_update[i]);
    }
}

void LCDStatusScreen(unsigned int *machine_status) {
    
    unsigned int i = 0;
    unsigned int j = 0;
    char num_buff[6];
    
    LCDClear();
        
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            num_buff[j] = '0';
        }
        itoa((i+1), num_buff);
        LCDCharacter('W');
        LCDCharacter(num_buff[1]);
        switch (machine_status[i]) {
            case IDLE:
                LCDCharacter(' ');
                break;
            case ACTIVE:
                LCDCharacter('*');
                break;
        }
        LCDCharacter(' ');
    }  
    
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            num_buff[j] = '0';
        }
        itoa((i+1), num_buff);
        LCDCharacter('D');
        LCDCharacter(num_buff[1]);
        switch (machine_status[i+10]) {
            case IDLE:
                LCDCharacter(' ');
                break;
            case ACTIVE:
                LCDCharacter('*');
                break;
        }
        LCDCharacter(' ');
    }
    LCDCharacter(' '); 
    LCDCharacter(' ');
    LCDCharacter(' ');
    LCDCharacter(' ');
}

void MasterSend(char cmd, char machine) {
    
    int i = 0;
    int j = 0;
    char generic_command[11];
    
    switch (cmd) {
        case INQUIRY:  
            for (i = 0; i < 6; i++) {
                generic_command[i] = master_inquiry[i];
            }

            generic_command[1] += machine;
            generic_command[5] += machine;
            
            for (i = 0; i < 6; i++) {
                outChar1(generic_command[i]);
            }
            break;
        case WASH:
            for (i = 0; i < 11; i++) {
                generic_command[i] = master_wash[i];
            }

            generic_command[1] += machine;
            generic_command[10] += machine;
            
            LCDSending();
            for (i = 0; i < 11; i++) {
                outChar1(generic_command[i]);
            }    
            for(i=0;i<15000;i++) {
                for(j=0;j<100;j++);
            }   
            break;
    }
        
    LCDStatusScreen(machine_status);
    
}

void SelectWasher(char machine) {
    
    unsigned int i = 0;
    unsigned int j = 0;
    char num_buff[6];
    
    for (i = 0; i < 17; i++) {
        machine_status[i] = 0;
    }
    
    machine_status[machine] = 1;
    
    LCDClear();
        
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            num_buff[j] = '0';
        }
        itoa((i+1), num_buff);
        LCDCharacter('W');
        LCDCharacter(num_buff[1]);
        switch (machine_status[i]) {
            case IDLE:
                LCDCharacter(' ');
                break;
            case ACTIVE:
                LCDCharacter('*');
                break;
        }
        LCDCharacter(' ');
    }  
    
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            num_buff[j] = '0';
        }
        itoa((i+1), num_buff);
        LCDCharacter('D');
        LCDCharacter(num_buff[1]);
        switch (machine_status[i+10]) {
            case IDLE:
                LCDCharacter(' ');
                break;
            case ACTIVE:
                LCDCharacter('*');
                break;
        }
        if (i != 6) {
            LCDCharacter(' ');
        }
    }
    
    LCDString(state_update[16]);
}

void LCDSending(void) {
    LCDClear();
    LCDCarriageReturn();
    LCDString(state_update[1]);
    LCDString(state_update[17]);
    LCDString(state_update[1]);
    LCDCarriageReturn();
    LCDCarriageReturn();
}