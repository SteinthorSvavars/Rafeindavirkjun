/*
Verkefni: 18
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
unsigned int load_cell_res; // Gildi þannemans úr ADC

// ********* Main byrjar ********
void main() {
    // ********** Uppsetning byrjar *********
    OSCCON = 0x71;		// 8 MHz
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
    ADCON1 = 0x81;	   // A/D Spennuviðmið er Vcc	
    // ********** Uppsetning endar **********

    Lcd_Init();                      // LCD display initialization  --------LCD---------
    Lcd_Cmd(_LCD_CURSOR_OFF);        // LCD command (cursor off)  --------LCD---------
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "Kronuteljari :)");
    // ********** Forrit byrjar **********

    while (1) {
        load_cell_res = ADC_Read(2) // Lesið analog inngangi 2
            PORTD = load_cell_res;
        PORTC = load_cell_res >> 2; 

        if (load_cell_res <= 30)
            Lcd_Out(2, 1, "Engar kronur    ");
        else if (load_cell_res >= 31 && load_cell_res <= 40)
            Lcd_Out(2, 1, "10Kr a voginni  ");
        else if (load_cell_res >= 41 && load_cell_res <= 75)
            Lcd_Out(2, 1, "20Kr a voginni  ");
        else if (load_cell_res >= 76 && load_cell_res <= 100)
            Lcd_Out(2, 1, "30Kr a voginni  ");
        Delay_ms(150);
    } // ********** Forrit Endar **********
} // ********** Main Endar **********