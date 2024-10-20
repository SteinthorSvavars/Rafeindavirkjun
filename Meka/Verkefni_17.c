/*
Verkefni: 17
Nafn: Steinþór Emil

PIC16F887
*/

// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

// Breytur
unsigned int adc_res; // Gildi úr ADC
void forward(unsigned int acd_res);
void backward(unsigned int adc_res);

// ********* Main byrjar ********
void main() {
	// ********** Uppsetning byrjar *********
	OSCCON = 0x71;
	ANSEL = 0;            // Skilgreini Analog innganga sem digital
	ANSELH = 0;            // Skilgreini Analog innganga sem digital
	C1ON_bit = 0;          // Comparator ger?ur ?virkur
	C2ON_bit = 0;          // Comparator ger?ur ?virkur

	PORTA = 0x00;          // Allir ?tgangar ? PORTA eru lo
	PORTB = 0x00;          // Allir ?tgangar ? PORTB eru lo
	PORTC = 0x00;          // Allir ?tgangar ? PORTC eru lo
	PORTD = 0x00;          // Allir ?tgangar ? PORTD eru lo
	PORTE = 0x00;          // Allir ?tgangar ? PORTE eru lo

	TRISA = 0xFF;          // Set alla pinna ? PORTA sem innganga
	TRISB = 0x00;          // Set alla pinna ? PORTB sem ?tganga
	TRISC = 0x07;          // Set fyrstu 4 pinna PORTC sem útganga, rest sem inngangar
	TRISD = 0x00;          // Set alla pinna ? PORTD sem ?tganga
	TRISE = 0x00;          // Set alla pinna ? PORTE sem ?tganga
	ADCON1 = 0x82;         // A/D Spennuviðmið er Vcc
	// ********** Uppsetning endar **********

	Lcd_Init();                      // LCD display initialization  --------LCD---------
	Lcd_Cmd(_LCD_CURSOR_OFF);        // LCD command (cursor off)  --------LCD---------
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Out(1, 1, "Steppermotor :)");
	// Forrit byrjar

	while (1) {
		acd_res = ADC_Read(2); // Notum analog inngang 2 fyrir þetta

		if (adc_res >= 550 && adc_res <= 450) { // Stopp
			PORTC = 0x00;
			Lcd_out(2, 1, "Stop");
		}
		else if (adc_res >= 600) { // Áfram
			forward();
			Lcd_out(2, 1, "Afram");
		}
		else if (adc_res <= 400) { // Bakka 
			backward();
			Lcd_out(2, 1, "Bakka");
		}

	}
	void forward(unsigned int adc_res) {
		PORTC = 0x09;
		vdelay(floor(30 - adc_res / 50));
		PORTC = 0x03;
		vdelay(floor(30 - adc_res / 50));
		PORTC = 0x06;
		vdelay(floor(30 - adc_res / 50));
		PORTC = 0x0C;
		vdelay(floor(30 - adc_res / 50));
	}

	void backward(unsigned int adc_res) {
		PORTC = 0x0C;
		vdelay(floor(adc_res / 50 + 10));
		PORTC = 0x06;
		vdelay(floor(adc_res / 50 + 10));
		PORTC = 0x03;
		vdelay(floor(adc_res / 50 + 10));
		PORTC = 0x09;
		vdelay(floor(adc_res / 50 + 10));
	}
} // ********** Main endar **********