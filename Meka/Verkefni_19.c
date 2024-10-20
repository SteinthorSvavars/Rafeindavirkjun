/*
Verkefni: 18
Nafn: Steinþór Emil

PIC16F887
*/

int var;
int temp;
int t_a;
int t_b;
int t_c;
int t_d;
int cnt;

unsigned int adc_res;

void main()               // A�alforrit
{                         // A�alforrit byrjar
    OSCCON = 0x71;             // Stillir innri klukkuna � 8MHz
    ANSEL = 0;            // Skilgreini Analog innganga sem digital
    ANSELH = 0;            // Skilgreini Analog innganga sem digital
    C1ON_bit = 0;          // Comparator ger�ur �virkur
    C2ON_bit = 0;          // Comparator ger�ur �virkur

    PORTA = 0x00;          // Allir �tgangar � PORTA eru lo
    PORTB = 0x00;          // Allir �tgangar � PORTB eru lo
    PORTC = 0x00;          // Allir �tgangar � PORTC eru lo
    PORTD = 0x00;          // Allir �tgangar � PORTD eru lo
    PORTE = 0x00;          // Allir �tgangar � PORTE eru lo

    TRISA = 0x00;          // Set alla pinna � PORTA sem �tganga
    TRISB = 0x00;          // Set alla pinna � PORTB sem �tganga
    TRISC = 0x00;          // Set alla pinna � PORTC sem �tganga
    TRISD = 0x00;          // Set alla pinna � PORTD sem �tganga
    TRISE = 0x00;          // Set alla pinna � PORTE sem �tganga

    ADCON1 = 0x82;

    // ************* Forrit byrjar *************

    while (1)
    {
        adc_res = ADC_Read(0); // Lesum inn á AN0
        delay = adc_res;

        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;

        var = 0x01;            // Upphafsstillt gildi
        cnt = 0;               // Teljari n�llstilltur
        while (cnt <= 7) {
            PORTA = var;     // Setjum upphafsstillt gildi inn � PORTA
            temp = var;     // vistum var sem backup
            var = temp + temp;  // N�sta gildi er n�verandi gildi sinnum 2
            cnt++;       
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }
        PORTA = 0x00;   // Núllstilla PORTA
        cnt = 0;
        var = 0x80;     
        while (cnt <= 7) {
            PORTB = var;
            temp = var / 2;
            var = temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }
        PORTB = 0x00;
        var = 0x01;
        cnt = 0;
        while (cnt <= 7) {
            PORTC = var;
            temp = var;
            var = temp + temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
      
        }
        PORTC = 0x00;
        cnt = 0;
        var = 0x80;
        while (cnt <= 7) {
            PORTD = var;
            temp = var / 2;
            var = temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }
        PORTD = 0x00;
        PORTC = 0x01;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTC = 0x00;
        PORTB = 0x01;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTB = 0x00;
        var = 0x01;
        cnt = 0;
        while (cnt <= 7) {
            PORTA = var;
            temp = var;
            var = temp + temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }
        PORTA = 0x00;
        PORTB = 0x80;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTB = 0x00;
        PORTC = 0x80;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTC = 0x00;
        cnt = 0;
        var = 0x80;
        while (cnt <= 7) {
            PORTD = var;
            temp = var / 2;
            var = temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }
        PORTD = 0x00;

        PORTC = 0x01;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTC = 0x00;
        PORTB = 0x01;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTB = 0x00;
        cnt = 0;
        var = 0x01;                 // 0000 0001
        while (cnt <= 7) {
            PORTA = var;
            PORTB = var;
            PORTC = var;
            PORTD = var;
            temp = var + var;
            var = temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }
        cnt = 0;
        var = 0x80;              
        while (cnt <= 7) {
            PORTA = var;
            PORTB = var;
            PORTC = var;
            PORTD = var;
            temp = var / 2;
            var = temp;
            cnt++;
            vdelay_ms(1030 - delay); // Breytileg seinkun
        }

        PORTD = 0x00;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTC = 0x00;
        vdelay_ms(1030 - delay); // Breytileg seinkun
        PORTB = 0x00;
    } // ********** Forrit lokar *********

} // ********** Main lokar **********