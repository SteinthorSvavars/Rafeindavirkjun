// Forrit fyrir PIC16F887 ? MPLAB IDE - HITECHC
// s?niforrit sem s?nir skipun fyrir seinkun og 
// til a? skrifa ? einn ?tgang er t.d. nota? RC0 = 1; 
// H?r setji? ?i? nafni? ykkar
// og uppl?singar um forriti?
// fyrir hva?a PIC forriti? er skrifa?
// og a?rar nau?synlegar uppl?singar um forriti?


#include <htc.h>

#define _XTAL_FREQ 8000000

__CONFIG(FOSC_INTRC_NOCLKOUT&		// Interrnal Osc RA6 og RA7 = I/O
	WDTE_OFF&		// Disable Watchdog Timer.
	PWRTE_ON&		// Enable Power Up Timer.
	MCLRE_ON&
	CP_OFF&
	BOREN_ON&
	IESO_ON&
	FCMEN_ON&
	LVP_OFF&
	DEBUG_OFF);
__CONFIG(BOR4V_BOR40V);
unsigned int counter;
int teljari;
void main()
{
	// ===== uppsetning ? PIC =====
	OSCCON = 0x75;
	ANSEL = 0x00;
	ANSELH = 0x00;
	INTCON = 0x00;

	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;

	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0x00;



	// ===== forriti? byrjar =====
	counter = 1000;
	while (1) {
		// H?r er skrifa? ? alla ?tganga ? einu
		PORTA = 0xFF;
		vdelay_ms(counter);
		PORTA = 0x00;
		vdelay_ms(counter);
		if (teljari == 1) {
			counter = counter - 1;
			if (counter == 200) {
				teljari = 0;
			}
		}
		if (teljari == 0) {
			counter = counter - 1;
			if (counter == 1000) {
				teljari = 1;
			}
		}





	}
}