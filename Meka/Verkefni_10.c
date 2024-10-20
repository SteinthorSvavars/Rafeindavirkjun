/*
Verkefni: 10
Nafn: Steinþór Emil

PIC16F887
*/

// ********* Breytur **********


// ********* Main byrjar ********
void main() {
    // ********** Uppsetning byrjar *********
    ANSEL = 0;            // Skilgreini Analog innganga sem digital
    ANSELH = 0;            // Skilgreini Analog innganga sem digital
    C1ON_bit = 0;          // Comparator ger?ur ?virkur
    C2ON_bit = 0;          // Comparator ger?ur ?virkur

    PORTA = 0x00;          // Allir ?tgangar ? PORTA eru lo
    PORTB = 0x00;          // Allir ?tgangar ? PORTB eru lo
    PORTC = 0x00;          // Allir ?tgangar ? PORTC eru lo
    PORTD = 0x00;          // Allir ?tgangar ? PORTD eru lo
    PORTE = 0x00;          // Allir ?tgangar ? PORTE eru lo

    TRISA = 0x00;          // Set alla pinna ? PORTA sem ?tganga
    TRISB = 0x00;          // Set alla pinna ? PORTB sem ?tganga
    TRISC = 0x0F;          // Set alla pinna ? PORTC sem ?tganga
    TRISD = 0x00;          // Set alla pinna ? PORTD sem ?tganga
    TRISE = 0x00;          // Set alla pinna ? PORTE sem ?tganga
    // ********** Uppsetning endar **********
    
    // ********** Forrit byrjar **********
    while (1) {
        if (PORTC.B3 == 1) {
            PORTC.B4 = 1;
            PORTC.B7 = 1;
            while(PORTC.B1 = 0) {}
            PORTC.B4 = 0;
            PORTC.B7 = 0;
        }
        if (PORTC.B2 == 1) {
            PORTC.B5 = 1;
            PORTC.B6 = 1;
            while (PORTC.B0 = 0) {}
            PORTC.B5 = 0;
            PORTC.B6 = 0;
        }
    }// ********** Forrit endar ***********
} // ********** Main endar **********

// ********** Undirforrit byrjar *********

// ********** Undirforrit endar **********