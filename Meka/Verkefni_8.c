/*
Verkefni 8
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

// ********** Main Byrjar **********
void main() {
    // ********** Uppsetning *********
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

    Lcd_Init();                      // LCD display initialization  --------LCD---------
    Lcd_Cmd(_LCD_CURSOR_OFF);        // LCD command (cursor off)  --------LCD---------
    Lcd_Cmd(_LCD_CLEAR);             // LCD command (clear LCD)  --------LCD---------

    // ********** Main Forrit *********
    LCD_Out(1, 1, "Skrefmotor val:");
    while (1) {
        LCD_Out(2, 1, "Stopp");
        PORTC = 0x00;
        if (PORTA.B0 == 1) {
            while (PORTA.B0 == 1) {
                LCD_Out(2, 1, "Hratt afram");
                PORTC = 0x08;
                Delay_ms(25);
                PORTC = 0x04;
                Delay_ms(25);
                PORTC = 0x02;
                Delay_ms(25);
                PORTC = 0x01;
                Delay_ms(25);
            }
        }
        if (PORTA.B1 == 1) {
            while (PORTA.B1) {
                LCD_Out(2, 1, "Haegt afram");
                PORTC = 0x08;
                Delay_ms(50);
                PORTC = 0x04;
                Delay_ms(50);
                PORTC = 0x02;
                Delay_ms(50);
                PORTC = 0x01;
                Delay_ms(50);
            }
        }
        if (PORTA.B2 == 1) {
            while (PORTA.B2) {
                LCD_Out(2, 1, "Hratt bakk");
                PORTC = 0x01;
                Delay_ms(50);
                PORTC = 0x02;
                Delay_ms(50);
                PORTC = 0x04;
                Delay_ms(50);
                PORTC = 0x08;
                Delay_ms(50);
            }
        }
        if (PORTA.B3 == 1) {
            while (PORTA.B3) {
                LCD_Out(2, 1, "Hratt bakk");
                PORTC = 0x01;
                Delay_ms(25);
                PORTC = 0x02;
                Delay_ms(25);
                PORTC = 0x04;
                Delay_ms(25);
                PORTC = 0x08;
                Delay_ms(25);

            }
        }
    } //While endar
}// Main endar