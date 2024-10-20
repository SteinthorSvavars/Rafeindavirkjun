#define	LCD_RS RB4
#define	LCD_RW RB6
#define LCD_EN RB5
#define LCD_DATA	PORTB

#define _LCD_CURSOR_OFF 0x0C
#define _LCD_CURSOR_ON 0x0F
#define _LCD_CURSOR_ON_SOLID 0x0E
#define _LCD_CLEAR 0x01
#define _LCD_BLANK 0x08

#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 8MHz system frequency is assumed
 #define _XTAL_FREQ 8000000
#endif

extern void lcd_write(unsigned char);
extern void lcd_clear(void);
extern void lcd_out( unsigned char line, unsigned char character, const char * s);
extern void lcd_goto(unsigned char pos);
extern void lcd_init(void);
extern void lcd_chr_cp(char);
extern void lcd_cmd(unsigned char);
extern void lcd_chr( unsigned char line, unsigned char character, char c );
//#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)
#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))