#include <htc.h>	// includar skr? me? uppl?singum um PIC kubbinn
#include "LCD.c"	// ?essi skr? ?arf a? vera ? s?mu m?ppu og projecti?
#include "LCD.h"    // ?essi skr? ?arf a? vera ? s?mu m?ppu og projecti?

#define _XTAL_FREQ 8000000	// skilgreini klukkut??ni => delay skipun virki r?tt

#pragma config FOSC = INTRC_NOCLKOUT  // Internal Osc RA6 og RA7 = I/O
#pragma config WDTE = OFF  // Disable Watchdog Timer.
#pragma config PWRTE = ON  // Enable Power Up Timer.
#pragma config MCLRE = ON  // Enable Master Clear.
#pragma config CP = OFF    // Disable Code Protect.
#pragma config BOREN = ON  // Enable Brown Out Reset.
#pragma config IESO = ON   // Enable Int-Ext Switchover.
#pragma config FCMEN = ON  // Enable Fail-safe Clk. Monitor.
#pragma config LVP = OFF   // Disable Low Voltage Program.
#pragma config DEBUG = OFF // Disable In-Circuit Debugger.
#pragma config BOR4V = BOR40V // Brown-out Reset Sel.

char *text;		// Textabreyta

void main()		// a?alforrit	
{				// a?alforrit byrjar
__CONFIG(FOSC_INTRC_NOCLKOUT &		// Interrnal Osc, RA6 og RA7 = I/O
	 	 WDTE_OFF &		// Disable Watchdog Timer.
		 PWRTE_ON &		// Enable Power Up Timer.
		 MCLRE_ON &		// Enable Master Clear = Reset
		 CP_OFF &		// Disable Code Protection
		 BOREN_ON &		// Enable BrownOut 
		 IESO_ON &		// Enable INT-EXT-Switchover
 		 FCMEN_ON &		// Enable Fail-safe CLK. Monitor
 		 LVP_OFF &		// Disable Low Voltage Programming
 		 DEBUG_OFF);	// Disable Debugging
__CONFIG(BOR4V_BOR40V); // BrownOut vi? 4V

// ===== uppsetning ? PIC =====
	OSCCON = 0x75;	// Stillir klukkut??ni og skilgreinir hva?a klukka er notu?
	ANSEL  = 0x00;      // Skilgreinir alla pinna sem digital
	ANSELH = 0x00;      // Skilgreinir alla pinna sem (stafr?na)
	CM1CON0 = CM1CON0 & 0x7F;  // Disable comparators
	CM2CON0 = CM2CON0 & 0x7F;  // Disable comparators
	INTCON = 0x00;      // Stillir interrupt bita

	PORTA = 0x00;       // Setur 0 ? alla pinna ? port A
	PORTB = 0x00;       // Setur 0 ? alla pinna ? port B
	PORTC = 0x00;       // Setur 0 ? alla pinna ? port C
	PORTD = 0x00;       // Setur 0 ? alla pinna ? port D
	PORTE = 0x00;       // Setur 0 ? alla pinna ? port E

	TRISA = 0x00;       // Skilgreinir alla pinna ? port A sem ?tganga
	TRISB = 0x00;       // Skilgreinir alla pinna ? port B sem ?tganga
	TRISC = 0x00;       // Skilgreinir alla pinna ? port C sem ?tganga
	TRISD = 0x00;       // Skilgreinir alla pinna ? port D sem ?tganga
	TRISE = 0x00;       // Skilgreinir alla pinna ? port E sem ?tganga

	lcd_init();				  // uppsetning fyrir LCD skj?


	while(1) {				  // endalaus while lykkja byrjar

//  ======  Nokkrar a?fer?ir vi? a? skrifa ? LCD skj?  ======	
        text = "Tskoli";      // Skilgreini skilabo?
        lcd_out(1,1,text);    // Skrifa skilabo?, fremst ? efri l?nu
        lcd_out(1,9,"STS303"); // skrifa skilabo?, ? d?lk-9 ? efri l?nu
        
        lcd_out(2,1,"Haust"); // Skrifa skilabo?, fremst ? ne?ri l?nu

        lcd_chr(2,7,2+48);    // Skrifa 2 me? ?v? a? breyta 2 ? ASCII, d?lk-7 ? ne?ri l?nu
        lcd_chr(2,8,0+48);    // Skrifa 0 me? ?v? a? breyta 0 ? ASCII, d?lk-8 ? ne?ri l?nu
        lcd_chr_cp(1+48);     // Skrifa 1 me? ?v? a? breyta 1 ? ASCII, cp = current position
        lcd_chr_cp(2+48);     // Skrifa 2 me? ?v? a? breyta 2 ? ASCII, cp = current position
	}			// while lykkja endar
}				// a?alforrit endar