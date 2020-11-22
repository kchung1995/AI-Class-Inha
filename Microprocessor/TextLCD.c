#include "TextLCD.h"

void LCD_pulse_enable(void) {
    set_bit(PORTL, E_PIN);
    _delay_us(1);
    clear_bit(PORTL, E_PIN);
    _delay_ms(1);
}

uint8_t reverse_bit_order(uint8_t data) {
    if (data & (1 << 0)) result |= (0x80 >> 0);
    if (data & (1 << 1)) result |= (0x80 >> 1);
    if (data & (1 << 2)) result |= (0x80 >> 2);
    if (data & (1 << 3)) result |= (0x80 >> 3);
    if (data & (1 << 4)) result |= (0x80 >> 4);
    if (data & (1 << 5)) result |= (0x80 >> 5);
    if (data & (1 << 6)) result |= (0x80 >> 6);
    if (data & (1 << 7)) result |= (0x80 >> 7);

    return result;
}

void LCD_write_date(uint8_t data) {
    set_bit(PORTL, RS_PIN);

    uint8_t temp = reverse_bit_order(data);

    PORTL = (PORTL & 0xF0) | (temp & 0x0F);
    LCD_pulse_enable();

    PORTL = (PORTL & 0xF0) | (temp >> 4);
    LCD_pulse_enable();

    _delay_ms(2);
}

void LCD_write_command(uint8_t command) {
    clear_bit(PORTL, RS_PIN);

    uint8_t temp = reverse_bit_order(command);

    PORTL = (PORTL & 0xF0) | (temp & 0x0F);
    LCD_pulse_enable();

    PORTL = (PORTL & 0xF0) | (temp >> 4);
    LCD_pulse_enable();

    _delay_ms(2);
}

void LCD_clear(void) {
    LCD_write_command(COMMAND_CLEAR_DISPLAY);
    _delay_ms(2);
}

void LCD_write_string(char *string) {
    uint8_t i;
    for (i = 0; string[i]; i++)
    LCD_write_data(string[i]);
}

void LCD_goto_XY(uint8_t row, uint8_t col) {
    col %= 16;
    row %= 2;

    uint8_t address = (0x40 * row) + col;
    uint8_t command = 0x80 + address;
    LCD_write_command(command);
}

void LCD_init(void) {
    _delay_ms(50);

    DDRL |= 0X0F;
    DDRL |= (1 << RS_PIN) | (1 << E_PIN);

    LCD_write_command(0x02);
    LCD_write_command(COMMAND_4_BIT_MODE);

    uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
    LCD_write_command(command);

    LCD_clear();

    LCD_write_command(0x06);
}