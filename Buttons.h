/*
 * File:   buttons.h
 * Author: Shane Ryan
 * Implement a two-button control system using interrupts and timers.
 * 
 * 
 * 
 * Created on April 4, 2016, 12:05 PM
 */


#define MAX_dc 0x1CC
// unscaled T value for 1000Hz signal:  0x3E7F

void pin_setup(void);
void timer_setup(void);

void pin_setup(void) {
        
    /*  Disable Analog Priority on RA0 and RA1  */
    ANSELAbits.ANSA0 = 0;
    ANSELAbits.ANSA1 = 0;
    
   /*  Set pins RA0 and RA1 to Inputs  */
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    
    /*  Enable Change Notification Interrupts on Inputs */
    IEC1bits.CNIE = 1;
    CNENAbits.CNIEA0 = 1;
    CNENAbits.CNIEA1 = 1;
    IPC4bits.CNIP = 5;
    
    /*  Internal Pullup Resistors on Inputs  */
    CNPUAbits.CNPUA0 = 1;
    CNPUAbits.CNPUA1 = 1;
}


void timer_setup(void) {
    
    /*  Turn on Timer2 module via
     *  Peripheral Module Disable Control Reg 1 */
    // PMD1bits.T2MD = 0;
    PMD1bits.T3MD = 0;
    // Chosen b/c only Timer2 and Timer3 can be time bases for OC mod
    
    /*  Configure Timer3 for delaying between button presses    */
    T3CONbits.TON = 0;
    T3CONbits.TGATE = 0;
    T3CONbits.TCKPS = 0b10; // pre-scaler set to 64 to keep PR3 16bits or less
    T3CONbits.TCS = 0;
    T3CONbits.TSIDL = 0;
    PR3 = MAX_dc * 24;
    TMR3 = 0x00;
    T3CONbits.TON = 1;
    IPC2bits.T3IP = 6;
    IEC0bits.T3IE = 0;


    /*  Turn on Output Comparison module 1 via
     * Peripheral Module Disable Control Reg 2  */
    PMD2bits.OC1MD = 0;
    
}