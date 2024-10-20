/*
Verkefni: 12
Nafn: Steinþór Emil

PIC16F887
*/

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
  
    Lcd_Init();                     // Initialize LCD
    Lcd_Cmd(_LCD_CLEAR);            // Clear Display
    Lcd_Cmd(_LCD_CURSOR_OFF);       // Cursor off

    // ********** Forrit byrjar **********

    while (1) {
        Lcd_out(1, 1, "Skrefmotor");
        Lcd_out(2, 1, "0 deg      ");      
        if (PORTD.B0 == 1) {
            PORTB.B0 = 1;
            Delay_us(1100);
            PORTB.B0 = 0;
            Delay_us(18900);
            Lcd_out(2, 1, "-80 deg");
        }
        if (PORTD.B1 == 1) {
            PORTB.B0 = 1;
            Delay_us(1200);
            PORTB.B0 = 0;
            Delay_us(18800);
            Lcd_out(2, 1, "-60 deg");
        }
        if (PORTD.B2 == 1) {
            PORTB.B0 = 1;
            Delay_us(1300);
            PORTB.B0 = 0;
            Delay_us(18700);
            Lcd_out(2, 1, "-40 deg");
        }
        if (PORTD.B3 == 1) {
            PORTB.B0 = 1;
            Delay_us(1400);
            PORTB.B0 = 0;
            Delay_us(18600);
            Lcd_out(2, 1, "-20 deg");
        }
        if (PORTD.B4 == 1) {
            PORTB.B0 = 1;
            Delay_us(1600);
            PORTB.B0 = 0;
            Delay_us(18400);
            Lcd_out(2, 1, "20 deg");
        }
        if (PORTD.B5 == 1) {
            PORTB.B0 = 1;
            Delay_us(1700);
            PORTB.B0 = 0;
            Delay_us(18300);
            Lcd_out(2, 1, "40 deg");
        }
        if (PORTD.B6 == 1) {
            PORTB.B0 = 1;
            Delay_us(1800);
            PORTB.B0 = 0;
            Delay_us(18200);
            Lcd_out(2, 1, "60 deg");
        }
        if (PORTD.B7 == 1) {
            PORTB.B0 = 1;
            Delay_us(1900);
            PORTB.B0 = 0;
            Delay_us(18100);
            Lcd_out(2, 1, "80 deg");
        }
    }// ********** Forrit endar ***********
} // ********** Main endar **********
// ********** Undirforrit byrjar *********

// ********** Undirforrit endar **********
