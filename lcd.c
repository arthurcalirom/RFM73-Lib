/*
 * lcd.c
 *
 * Created: 24.06.2013 19:21:58
 *  Author: d-wsky
 */ 

#ifndef LCD_C_
#define LCD_C_

#include "lcd.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/io.h>


#define lcd_putc(x)  lcd_putbyte(x, LCD_DATA)

/* ������� �������� ������� � ��� */
void lcd_putnibble(char t)
{
    t&=0x0F;
    t<<=4;
    LCD_E_SET;
    _delay_us(50);
    PORTC&=0x0F;
    PORTC|=t;
    LCD_E_CLR;
    _delay_us(50);
}

/* ������� �������� ����� � ���. 
char c - ��� ����
char rs - ����������, ����������� ��� ����������:
     rs = 0 - ������� (��������������� ����� RS)
	 rs = 1 - ������ (������������ ����� RS) */
void lcd_putbyte(char c, char rs)
{
    char highc=0;
    highc=c>>4;
	if (rs==LCD_COMMAND) LCD_RS_CLR;
	else                 LCD_RS_SET;
    lcd_putnibble(highc);
    lcd_putnibble(c);
}

/* ������� ������������� ������ ���
� 4-������ ������, ��� ������� */
void lcd_init()
{
    PORTC=0x00;
    DDRC=0xF3;
    _delay_ms(15);
    lcd_putbyte(0x33, LCD_COMMAND);
    _delay_ms(4);
    lcd_putbyte(0x32, LCD_COMMAND);
    _delay_us(100);
    lcd_putbyte(0x28, LCD_COMMAND);
    _delay_ms(1);
    lcd_putbyte(0x0C, LCD_COMMAND);
    _delay_ms(1);
    lcd_putbyte(0x06, LCD_COMMAND);
    _delay_ms(1);
}

/* ������� ������� ������� � ��������
������� � ��������� �������*/
void lcd_clear()
{
    lcd_putbyte(0x01, LCD_COMMAND);
    _delay_us(1500);
}

/* ������� ����������� ������� � �������� �������
col - ����� ���������� �� �������������� ��� (�� 0 �� 15)
row - ����� ������ (0 ��� 1) */
void lcd_gotoxy(char col, char row)
{
  char adr;                                           
  adr=0x40*row+col; 
  adr|=0x80;
  lcd_putbyte(adr, LCD_COMMAND);
}

void lcd_puts(char* s) {
	while (*s!=0) {
		lcd_putc(*(s++));
	}
}

	
#endif 