#define F_CPU 16000000L
#define STOP 0
#define START 1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f,
0x6f };
const unsigned char find_sel[4] = { 0x08,0x04,0x02,0x01 };
const unsigned char dot = 0x80;

volatile int signal = 0;
volatile int count = 0;

ISR(INT4_vect) {
	if (signal == START)
		signal = STOP;
	else
		signal = START;
	_delay_ms(10);
}

ISR(INT5_vect) {
	if (signal == STOP)
		count = 0;
	_delay_ms(10);
	
}

void display(int c) {
	int i;
	unsigned char digits[4];
	digits[3] = digit[(c / 10000)%10];
	digits[2] = digit[(c / 1000)%10] + dot;;
	digits[1] = digit[(c / 100)%10];
	digits[0] = digit[(c / 10)%10];
	
	for(i = 0; i < 4; i++) {
		PORTC = digits[i];
		PORTG = find_sel[3-i];
		_delay_ms(0.25);
	}
}

void main() {
	DDRC = 0xFF;
	DDRG = 0x0F;
	DDRE = 0x00;
	EICRB = 0x0A;
	EIMSK = 0x30;
	SREG |= 1 << 7;
	
	while(1) {
		
		display(count);
		if (signal == START) {
			count = (count + 1) % 100000;
		}
	}
}