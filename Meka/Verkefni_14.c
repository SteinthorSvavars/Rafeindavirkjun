/*
Verkefni: 14
Nafn: Steinþór Emil

PIC16F887
*/

// ********* Breytur **********
unsigned int temp_res;
char* text;
unsigned int char ch;

// LCD Module connections

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

// ********* Main byrjar ********
void main() {

    // ********** Uppsetning byrjar *********
	OSCCON = 0x71;
    ANSEL = 0x04;
    ANSELH = 0;
    C1ON_bit = 0;
    C2ON_bit = 0;
 
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
        
    TRISA = 0xFF; 
    TRISB = 0x00;
    TRISC = 0x0F;
    TRISD = 0x00;
    TRISE = 0x00;
        
	ADCON1 = 0x82;

	Lcd_Init();                     // Initialize LCD
    Lcd_Cmd(_LCD_CLEAR);            // Clear Display
    Lcd_Cmd(_LCD_CURSOR_OFF);       // Cursor off
	
	text = "10 bita A/D";
	Lcd_Out(1,1, text);
// ********** Uppsetning endar **********

// ********** Forrit byrjar **********    
    while(1) {
		temp_res = ADC_Read(2);		    // Lesum hitamælinn á AD inngangi 2
		PORTD = temp_res;		        // LSB fært á RD
		PORTC = temp_res >> 2;		    // 2 MSB færðir á RC6 og RC7	

		ch = temp_res / 1000; 		    // Extract thousands
		Lcd_Chr(2, 9, 48+ch);		    // Write result in ASCII format
		
		ch = (temp_res / 100) % 10;     // Extract hundreds
                Lcd_Chr_CP(48+ch);      // Write result in ASCII format
		
		ch = (temp_res / 10) % 10;	    // Extract tens
                Lcd_Chr_CP(48+ch);     	// Write result in ASCII format

		ch = temp_res % 10;     	    // Extract last digits
                Lcd_Chr_CP(48+ch);      // Write result in ASCII format

	}// ********** Forrit endar ***********
} // ********** Main endar **********

// ********** Undirforrit byrjar *********

// ********** Undirforrit endar **********
