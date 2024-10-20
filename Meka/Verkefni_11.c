/*
Verkefni: 11
Nafn: Steinþór Emil

PIC16F887
*/

// ********* Breytur **********


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
    
    Lcd_Init();                      // LCD display initialization  --------LCD---------
    Lcd_Cmd(_LCD_CURSOR_OFF);        // LCD command (cursor off)  --------LCD---------
    Lcd_Cmd(_LCD_CLEAR);
    
    // ********** Forrit byrjar **********

    while (1) {
        Lcd_Out
    }

    // ********** Forrit endar ***********
} // ********** Main endar **********

// ********** Undirforrit byrjar *********

// ********** Undirforrit endar **********