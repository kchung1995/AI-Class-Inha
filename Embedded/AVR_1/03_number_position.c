#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect) {
	
}

void main() {
	
	const unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f,
	0x6f };
	const unsigned char find_sel[4] = { 0x08,0x04,0x02,0x01 };
	
	while(1) {
		DDRA = 0xFF;
		DDRC = 0xFF;
		DDRG = 0x0F;
		
		//TCCR0 = 0x02;
		TIMSK = 0x01;
		
		srand(TCNT0);
		int number = rand() % 8;
		
		int value = 1;
		value <<= number;

		for (int i = 0; i < 4; i++) {
			PORTA = value;
			PORTC = digit[number];
			PORTG = find_sel[i];
			_delay_ms(1);
		}

	}
}