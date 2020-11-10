#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void main() {

    unsigned char value= 128;
    DDRA = 0xFF;                    //use port A as output
    while(1) {
        if (value == 128) {
            while (value != 1) {
                PORTA = value;
                _delay_ms(200);
                value >>=1;
            }
        }
        if (value == 1) {
            while (value != 128) {
                PORTA = value;
                _delay_ms(200);
                value <<=1;
            }
        }
    }
}