/*
 * File:   buttons.h
 * Author: Shane Ryan
 * Separate Interrupt Service Routines to deal with button presses.
 * 
 * 
 * Created on April 4, 2016, 12:05 PM
 */

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {

    TMR3 = 0x00;
    IEC0bits.T3IE = 1;
    IEC1bits.CNIE = 0;
    IFS1bits.CNIF = 0;

}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void) {

    if (!PORTAbits.RA0 && !PORTAbits.RA1) {
        if (!mode) {
            SelectWasher(machine);
            mode = 1;
        }
        else if (mode) {
            MasterSend(WASH, (machine+1));
            mode = 0;
        }
    }

    else if (!PORTAbits.RA0 && mode) {
        if (machine < 16) {
            machine++;
        }
        SelectWasher(machine);
    }
    else if (!PORTAbits.RA1 && mode) {
        if (machine > 0) {
            machine--;
        }
        SelectWasher(machine);
    }

    /*  Don't clear flag if a single button is held (allows fast scrolling */
    if (!PORTAbits.RA0 && !PORTAbits.RA1) {
        IFS1bits.CNIF = 0;
    }
    else if (!PORTAbits.RA0 || !PORTAbits.RA1) {
        IFS1bits.CNIF = 1;
    }

    else {
        IFS1bits.CNIF = 0;
    }

    IFS0bits.T3IF = 0;
    IEC1bits.CNIE = 1;
    IEC0bits.T3IE = 0;

}