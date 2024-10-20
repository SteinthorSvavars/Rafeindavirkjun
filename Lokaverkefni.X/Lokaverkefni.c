/* 
 * File:   Lokaverkefni.c
 * Author: stein
 *
 * Created on 27 November 2023, 13:33
 */

#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include "LCD.c"
#include <htc.h>
#include <xc.h>

#define _XTAL_FREQ 8000000	// skilgreini klukkut??ni => delay skipun virki r?tt
// PORTA
#define PrtA_Utg0 RA0
#define PrtA_Utg1 RA1
#define PrtA_Utg2 RA2
#define PrtA_Utg3 RA3
#define PrtA_Utg4 RA4
#define PrtA_Utg5 RA5
#define PrtA_Utg6 RA6
#define PrtA_Utg7 RA7
// PORTB
#define PrtB_Utg0 RB0
#define PrtB_Utg1 RB1
#define PrtB_Utg2 RB2
#define PrtB_Utg3 RB3
#define PrtB_Utg4 RB4
#define PrtB_Utg5 RB5
#define PrtB_Utg6 RB6
#define PrtB_Utg7 RB7
// PORTC
#define PrtC_Utg0 RC0
#define PrtC_Utg1 RC1
#define PrtC_Utg2 RC2
#define PrtC_Utg3 RC3
#define PrtC_Utg4 RC4
#define PrtC_Utg5 RC5
#define PrtC_Utg6 RC6
#define PrtC_Utg7 RC7
//PORTD
/*
#define PrtD_Utg0 RD0
#define PrtD_Utg1 RD1
#define PrtD_Utg2 RD2
#define PrtD_Utg3 RD3
#define PrtD_Utg4 RD4
#define PrtD_Utg5 RD5
#define PrtD_Utg6 RD6
#define PrtD_Utg7 RD7
*/
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

/*
 * 
 */
/****** Segulteljari ******/
int DebounceA = 0; int DebounceB = 0; int interrupt_ms = 0;
int segull; int scan = 0;
int flicker1 = 0; int flickerA1 = 0; int flicker2 = 0; int flickerA2 = 0; 
int flickerspeed = 100; int flickermax = 70; int teljari;
/****** ******/
/****** Kubbar ******/
int kubbur1 = 0; int kubbur2 = 0; int kubbur3 = 0; int kubbur4 = 0;
/****** ******/
/****** Auto ******/
int run = 0; int pallur = 0; int keyra = 0; int veljari = 0;
/****** ******/
/***** Manual *****/
int ManualRun = 0;
/***** Mötun og ýtur ******/
int tala = 0; int yta = 0; int bakka = 0;
int teljari = 0; 
/****** ******/
int reset() // endur setur matarabeltið og ýturnar
{
    lcd_out(1,1, "Reseting");
    if(RA0 == 0){
        do{
            RC0 = 1;
        }while(RA0 == 0);
        RC0 = 0;
    }
    if(RA2 == 0){
        do{
            RC3 = 1;
        }while(RA2 == 0);
        RC3 = 0;
    }
    if(RA4 == 0){
        do{
            RC5 = 1;
        }while(RA4 == 0);
        RC5 = 0;
    }
    lcd_out(1,1, "                ");
}

int KeyPad(void) // tekur inn input frá 4x4 keypad
{
    PORTD = 0x00;
    int tala = -1;
    int input;
    int press = 0;
    PORTD = 0x01;
    __delay_ms(5);
    input = PORTD;  // segir a? input s? sama og hva?a takki s? ?tt ? ? PORTD
    if(input == 0x11 || input == 0x21 || input == 0x41 || input == 0x81){
        switch(input){
            case 0x11: tala = 1; press++; break;     // RD4    
            case 0x21: tala = 4; press++; break;     // RD5
            case 0x41: tala = 7; press++; break;     // RD6
            case 0x81: tala = 14; press++; break;    // RD7
        }
    }
    __delay_ms(5);
    PORTD = 0x02;   //R?? RD1
    __delay_ms(5);
    input = PORTD;  //segir a? input s? sama og hva?a takki s? ?tt ? ? PORTD
    if(input == 0x12 || input == 0x22 || input == 0x42 || input == 0x82){
        switch(input){
            case 0x12: tala = 2; press++; break;     // RD4
            case 0x22: tala = 5; press++; break;     // RD5
            case 0x42: tala = 8; press++; break;     // RD6
            case 0x82: tala = 0; press++; break;    // RD7
        }
    }
    __delay_ms(5); 
    PORTD = 0x04;   //R?? RD2
    __delay_ms(5); 
    input = PORTD;  //segir a? input s? sama og hva?a takki s? ?tt ? ? PORTD
    if(input == 0x14 || input == 0x24 || input == 0x44 || input == 0x84){
        switch(input){
            case 0x14: tala = 3; press++; break;     // RD4
            case 0x24: tala = 6; press++; break;     // RD5
            case 0x44: tala = 9; press++; break;     // RD6
            case 0x84: tala = 15; press++; break;    // RD7
        }
    }
    __delay_ms(5);       
    PORTD = 0x08;   //R?? RD3
    __delay_ms(5);
    input = PORTD;  //segir a? input s? sama og hva?a takki s? ?tt ? ? PORTD
    if(input == 0x18 || input == 0x28 || input == 0x48 || input == 0x88){
        switch(input){ 
            case 0x18: tala = 10; press++; break;    // RD4
            case 0x28: tala = 11; press++; break;    // RD5
            case 0x48: tala = 12; press++; break;    // RD6
            case 0x88: tala = 13; press++; break;    // RD7 
        }
    }
    __delay_ms(5);
    if((press == 0) && (tala == -1)){
        return tala;
    }
    return tala;
}

void Val(void) // velur hvert hvaða kubbar fara hvert
{
    __delay_ms(350);
    int num = -1;
    lcd_out(2,1, "                ");
    while(num == -1){
        lcd_out(1,1, "Velja 1,2 eda 3");
        lcd_out(2,1, "Kassi 1:");
        num = KeyPad();
        if(num <= 0 && num >= 4){
            num  = -1;
            __delay_ms(500);
        }
        if(num >= 1 && num <= 3){
            kubbur1 = num;
            __delay_ms(15);
        }
    }
    lcd_chr_cp(num+48);
    __delay_ms(15);
    num = -1;
    __delay_ms(350);
    lcd_out(2,1, "                ");
    while(num == -1){
        lcd_out(1,1, "Velja 1,2 eda 3");
        lcd_out(2,1, "Kassi 2:"); 
        num = KeyPad();
        if(num <= 0 && num >= 4){
            num  = -1;
            __delay_ms(500);
        }
        if(num >= 1 && num <= 3){
            kubbur2 = num;
            __delay_ms(15);
        }
    }
    lcd_chr_cp(num+48);
    __delay_ms(15);
    num = -1;
    __delay_ms(350);
    lcd_out(2,1, "                ");
    while(num == -1){
        lcd_out(1,1, "Velja 1,2 eda 3");
        lcd_out(2,1, "Kassi 3:");
        num = KeyPad();
        if(num <= 0 && num >= 4){
            num  = -1;
            __delay_ms(500);
        }
        if(num >= 1 && num <= 3){
            kubbur3 = num;
            __delay_ms(15);
        }
    }
    lcd_chr_cp(num+48);
    __delay_ms(15);
    num = -1;
    __delay_ms(350);
    lcd_out(2,1, "                ");     
    while(num == -1){
        lcd_out(1,1, "Velja 1,2 eda 3");
        lcd_out(2,1, "Kassi 4:");
        num = KeyPad();
        if(num <= 0 || num >= 4){
            num  = -1;
            __delay_ms(500);
        }
        if(num >= 1 && num <= 3){
            kubbur4 = num;
            __delay_ms(15);
        }
    }
    lcd_chr_cp(num+48);
    __delay_ms(15);
    num = -1;
    __delay_ms(350);
    lcd_out(1,1, "                ");
    lcd_out(2,1, "                ");
    __delay_ms(150);
}

void A(void) //Auto
{
    if(run == 0){
        //reset();
        segull = 0;
        teljari = 0;
        run = 1;
        Val();
    }
    __delay_ms(350);
    if(RA7 == 1){
        lcd_out(1,1, "                ");
        lcd_out(1,2, "                ");
        do{
            lcd_out(1,1, "Vantar kubb");
        }while(RA7 == 1);
        lcd_out(1,1, "                ");
    }
    do{
        int num = -1;
        do{
            num = KeyPad();
            lcd_out(1,1, "A til ad byrja");
            lcd_out(2,1, "0 til ad haetta");
        }while(num == -1);
        if(num == 0){
            run = 0;
        }
        else if(num == 10){
            num = -1;
            if(RA7 == 1){
                lcd_out(1,1, "                ");
                lcd_out(1,2, "                ");
                do{
                    lcd_out(1,1, "Vantar kubb");
                }while(RA7 == 1);
                lcd_out(1,1, "                ");
                __delay_ms(350);
            }
            RC0 = 1;
            RC1 = 1;
            lcd_out(1,1, "                ");
            lcd_out(2,1, "                ");
            lcd_out(1,1, "Keyrir...");
            pallur = 0;
            __delay_ms(200);
            lcd_out(2,1, "Kassi:");
            do{     // Telur fyrri segla
                if (scan == 1) {      // Ef scanning ferlið er í gangi þá teljum við teljaraS upp
                    interrupt_ms++;
                }
                if (RB6 == 1) {          // Ef að segull fer á skynjara eitt þá fer talningar ferllið í gang eða heldur áfram. 
                    scan = 1;   // Scanning fær gildið 1 og scanning ferlið byrjar eða heldur áfram
                    flicker1++;
                    flickerA1++;
                    if (DebounceA == 0 && flicker1 >= flickerspeed) {     // Debounce
                        DebounceA = 1;
                        segull++;
                        flicker1 = 0;
                        flickerA1 = 0;
                    }
                }
                else if (RB6 == 0 && flickerA1 >= flickerspeed) {
                    DebounceA = 0;  // Endursetjum flag1
                    flicker1 = 0;
                    flickerA1 = 0;
                }
                if (RB7 == 1) {          // Ef að segull fer á skynjara tvö þá fer talningar ferllið í gang eða heldur áfram. 
                    scan = 1;   // Scanning fær gildið 1 og scanning ferlið byrjar eða heldur áfram
                    flicker2++;
                    flickerA2++;
                    if (DebounceB == 0 && flicker2 >= flickerspeed) {     // Debounce
                        DebounceB = 1;
                        segull++;
                        flicker2 = 0;
                        flickerA2 = 0;
                    }
                }
                else if (RB7 == 0 && flickerA2 >= flickerspeed) {
                    DebounceB = 0;  // Endursetjum flag1
                    flicker2 = 0;
                    flickerA2 = 0;
                }
            }while(RA0 != 1);
            RC0 = 0;
            do{     // Telur seinni segla
                if (scan == 1) {      // Ef scanning ferlið er í gangi þá teljum við teljaraS upp
                    interrupt_ms++;
                }
                if (RB6 == 1) {          // Ef að segull fer á skynjara eitt þá fer talningar ferllið í gang eða heldur áfram. 
                    scan = 1;   // Scanning fær gildið 1 og scanning ferlið byrjar eða heldur áfram
                    flicker1++;
                    flickerA1++;
                    if (DebounceA == 0 && flicker1 >= flickerspeed) {     // Debounce
                        DebounceA = 1;
                        segull++;
                        flicker1 = 0;
                        flickerA1 = 0;
                    }
                }
                else if (RB6 == 0 && flickerA1 >= flickerspeed) {
                    DebounceA = 0;  // Endursetjum flag1
                    flicker1 = 0;
                    flickerA1 = 0;
                }
                if (RB7 == 1) {          // Ef að segull fer á skynjara tvö þá fer talningar ferllið í gang eða heldur áfram. 
                    scan = 1;   // Scanning fær gildið 1 og scanning ferlið byrjar eða heldur áfram
                    flicker2++;
                    flickerA2++;
                    if (DebounceB == 0 && flicker2 >= flickerspeed) {     // Debounce
                        DebounceB = 1;
                        segull++;
                        flicker2 = 0;
                        flickerA2 = 0;
                    }
                }
                else if (RB7 == 0 && flickerA2 >= flickerspeed) {
                    DebounceB = 0;  // Endursetjum DebounceB
                    flicker2 = 0;
                    flickerA2 = 0;
                }
                if (interrupt_ms >= flickermax || segull >= 4) {
                    teljari = 1;
                }
            }while(teljari == 0);
            lcd_chr(2,7, segull+48);
            lcd_out(1,1, "                ");
            lcd_out(1,1, "Pallur:");
            if(segull == 1){
                pallur = kubbur1;
            }
            else if(segull == 2){
                pallur = kubbur2;
            }
            else if(segull == 3){
                pallur = kubbur3;
            }
            else if(segull == 4){
                pallur = kubbur4;
            } 
            lcd_chr(1,8, pallur+48);
            /**** Kassi fer á pall 1 ****/
            if(pallur == 1){
                do{ // Stoppar ef kubbur er hja ytu 1
                    RC1 = 1;
                }while(RA5 == 0);
                if(RA5 == 1){ // Ef kubbur er við ytu 2 þa fer hun ut
                    RC1 = 0;
                    __delay_ms(100);
                }
                if(RA5 == 1){
                    do{ // ytir ut þangað til að RA1 er HI
                        RC2 = 1; 
                    }while(RA1 == 0);
                    RC2 = 0;
                    __delay_ms(150);
                }
                if(RA1 == 1){
                    do{ // Dregur ytu 2 inn þangað til að RA4 fer í HI
                        RC3 = 1;
                    }while(RA2 == 0);
                    RC3 = 0;
                    __delay_ms(150);
                    teljari = 0;
                    segull = 0;
                    scan = 0;
                    pallur = 0;
                    lcd_out(1,1, "                 ");
                }   
            }
            /**** Kassi fer á pall 2 ****/
            else if(pallur == 2){
                do{ // Stoppar ef kubbur er hja ytu 2
                    RC1 = 1;
                }while(RA6 == 0);
                
                if(RA6 == 1){ // Ef kubbur er við ytu 2 þa fer hun ut
                    RC1 = 0;
                    __delay_ms(100);
                }
                if(RA6 == 1){
                    do{ // ytir ut þangað til að RA3 er HI
                        RC4 = 1; 
                    }while(RA3 == 0);
                    RC4 = 0;
                    __delay_ms(150);
                }
                if(RA3 == 1){
                    do{ // Dregur ytu 2 inn þangað til að RA4 fer í HI
                        RC5 = 1;
                    }while(RA4 == 0);
                    RC5 = 0;
                    __delay_ms(150);
                    teljari = 0;
                    segull = 0;
                    scan = 0;
                    pallur = 0;
                    lcd_out(1,1, "                 ");
                }
                
            }
            /**** Kassi fer á pall 3 ****/
            if(pallur == 3){
                while(RE0 == 0){
                    RC1 = 1;
                }
                if(RE0 == 1){
                    RC1 = 0;
                    lcd_out(1,1, "                ");
                    lcd_out(2,1, "                ");
                }
                do{
                    lcd_out(1,1, "Vinsmalegast");
                    lcd_out(2,1, "Pall 3");
                }while(RE0 == 1);
                __delay_ms(150);
                teljari = 0;
                segull = 0;
                scan = 0;
                pallur = 0;
                lcd_out(1,1, "                 ");
                lcd_out(2,1, "                 ");
            }
        }
    }while(run == 1);
}

void B(void) //Manual
{   
    ManualRun = 1;
    do{
        int num;
        num = KeyPad();
        if(num == -1){ // Ekkert í gangi
            lcd_out(1,1, "Allt er stopp   ");
            lcd_out(2,1, "0 til ad stoppa ");
            PORTC = 0;
        }
        else if(num == 1) { // Matarafæriband
            lcd_out(1,1, "Matari          ");
            lcd_out(2,1, "Faeriband       ");
            RC0 = 1;
        }
        else if(num == 2){ // Stórafæriband
            lcd_out(1,1, "Flokkari        ");
            lcd_out(2,1, "Faeriband       ");
            RC1 = 1;
        }
        else if(num == 3){ // ýta 1 fer út
            lcd_out(1,1, "yta 1 ut        ");
            lcd_out(2,1, "                ");
            RC2 = 1;
        }
        else if(num == 4){ // ýta 1 fer heim
            lcd_out(1,1, "yta 1 heim      ");
            lcd_out(2,1, "                ");
            RC3 = 1;
        }
        else if(num == 5){ // ýta 2 fer út
            lcd_out(1,1, "yta 2 ut        ");
            lcd_out(2,1, "                ");
            RC4 = 1;
        }
        else if(num == 6){ // ýta 2 fer heim
            lcd_out(1,1, "yta 2 heim      ");
            lcd_out(2,1, "                ");
            RC5 = 1;
        }
        else if(num == 0){ // manual hættir
            lcd_out(1,1, "Manual          ");
            lcd_out(2,1, "Haetta           ");
            __delay_ms(350);
            ManualRun = 0;
            reset();
            __delay_ms(150);
        }
    }while(ManualRun == 1);
}

void main() 
{
/***** uppsetning a PIC *****/
	OSCCON = 0x75;	// Stillir klukkut??ni og skilgreinir hva?a klukka er notu?
	ANSEL  = 0x00;      // Skilgreinir alla pinna sem digital
	ANSELH = 0x00;      // Skilgreinir alla pinna sem (stafr?na)
	CM1CON0 = CM1CON0 & 0x7F;  // Disable comparators
	CM2CON0 = CM2CON0 & 0x7F;  // Disable comparators
	INTCON = 0x00;      // Stillir interrupt bita
    
    RBIF = 0;       // Clear interrupt flag prior to enable
    RBIE = 1;       // enable on change interrupts PORTB
    IOCB6 = 1;      // Interrupt on RB6 change is enabled 
    IOCB7 = 1;      // Interrupt on RB7 change is enabled
 
    PEIE = 1;       // all peripheral interrupts are enabled
    RCIE = 1;       // UART interrupt þegar tekið á móti sendingu
    ei(); 			// enable all interrupts  GIE

	PORTA = 0x00;       // Setur 0 ? alla pinna ? port A
	PORTB = 0x00;       // Setur 0 ? alla pinna ? port B
	PORTC = 0x00;       // Setur 0 ? alla pinna ? port C
	PORTD = 0x00;       // Setur 0 ? alla pinna ? port D
	PORTE = 0x00;       // Setur 0 ? alla pinna ? port E

	TRISA = 0xFF;       // Allt inngangar
	TRISB = 0xC0;       // RB6 og RB7 inngangra rest LCD
	TRISC = 0x00;       // RC0 - RC7 útgangar
	TRISD = 0xF0;       // RD0 - RD3 útgangar / RD4 - RD7 inngangar
	TRISE = 0x01;       // Skilgreinir alla pinna ? port E sem ?tganga

	lcd_init();				  // uppsetning fyrir LCD skj?
    
    reset(); // Endur stilir allar ýtur og belti
    
    while(1){
        int num;
        PORTA = 0x00;
        num = KeyPad();
        if(num == -1){ // Ekkert í gangi       
            lcd_out(1,1,"A: Auto          "); // Valmynd 
            lcd_out(2,1,"B: Manual        ");
            PORTC = 0;
            __delay_ms(250);
        }
        if(num == 10){
            lcd_out(1,1, "                ");
            lcd_out(2,1, "                ");
            A();
            __delay_ms(250);
        }
        else if(num == 11){
            lcd_out(1,1, "                ");
            lcd_out(2,1, "                ");
            B();
            __delay_ms(250);
        }
       if(num != -1 && num != 10 && num != 11 && num != 13){
            lcd_out(1,1, "Villa           ");
            lcd_out(2,1, "Velja A eda B   ");
            __delay_ms(1000);
        }
    } // While endar
} // Main endar

