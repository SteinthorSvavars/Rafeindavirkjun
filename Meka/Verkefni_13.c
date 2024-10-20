/*
Verkefni: 13
Nafn: Steinþór Emil

PIC16F887
*/

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

    TRISA = 0xFF;          // Set alla pinna ? PORTA sem ?tganga
    TRISB = 0x00;          // Set alla pinna ? PORTB sem ?tganga
    TRISC = 0x00;          // Set alla pinna ? PORTC sem ?tganga
    TRISD = 0x00;          // Set alla pinna ? PORTD sem ?tganga
    TRISE = 0x00;          // Set alla pinna ? PORTE sem ?tganga
    // ********** Uppsetning endar **********
 
    // ********** Forrit byrjar **********

	while(1) {
		if(PORTA.RA0 == 1)
			PORTA = 0xFF;
		if(PORTB.RB1 == 1)
			PORTB = 0xFF;
		if(PORTC.RC2 == 1)
			PORTC = 0xFF;
		if(PORTD.RD3 == 1)
			PORTD = 0xFF;		
	}// ********** Forrit endar ***********
} // ********** Main endar **********

// ********** Undirforrit byrjar *********

// ********** Undirforrit endar **********	
