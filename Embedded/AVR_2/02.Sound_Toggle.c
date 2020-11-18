#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ON 1
#define OFF 0

#define DO 17
#define RE 43
#define MI 66
#define FA 77
#define SOL 97
#define LA 114
#define SI 129
#define DOH 137

const unsigned char melody[8] = { DO, RE, MI, FA, SOL, LA, SI, DOH};

volatile int mel_index = 4;
volatile int state = OFF;

ISR (TIMER0_OVF_vect) {
	if (state == ON) {
		PORTB = 0x00;
		state = OFF;
	}
	else {
		PORTB = 0x10;
		state = ON;
	}
}

ISR(INT4_vect) {
	TIMSK ^= 0x01;
	_delay_ms(10);
}

ISR(INT5_vect) {
	mel_index = (mel_index + 1) % 8;
	_delay_ms(10);
}

void main() {
	
	DDRB = 0x10;
	DDRE = 0x00;
	EICRB = 0x0A;
	EIMSK = 0x30;
	
	TCCR0 = 0x03;
	TIMSK = 0x00;
	TCNT0 = melody[mel_index];
	
	sei();
	while(1);
}