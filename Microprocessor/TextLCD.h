#ifndef _TEXT_LCD_
#define _TEXT_LCD_

#include <avr/io.h>
#include <util/delay.h>

#ifndef set_bit
#define set_bit(value, bit) ( _SFR_BYTE(value)) |= _BV(bit) )
#endif

#ifndef clear_bit
#define clear_bit(value, bit) ( _SFR_BYTE(value)) &= ~_BV(bit) )
#endif

#define FS_PIN 5
#define E_PIN 4

#define COMMAND_CLEAR_DISPLAY 0x01
#define COMMAND_4_BIT_MODE 0x28

#define COMMAND_DISPLAY_ON_OFF_BIT 2
#define COMMAND_CURSOR_ON_OFF_BIT 1
#define COMMAND_BLINK_ON_OFF_BIT 0

void LCD_pulse_enable(void);
uint8_t reverse_bit_order(uint8_t data);
void LCD_write_date(uint8_t data);
void LCD_write_command(uint8_t command);
void LCD_clear(void);
void LCD_write_string(char *string);
void LCD_goto_XY(uint8_t row, uint8_t col);
void LCD_init(void);

#endif