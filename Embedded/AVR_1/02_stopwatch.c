#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void main() {
	
	const unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f,
	0x6f };
	const unsigned char find_sel[4] = { 0x08,0x04,0x02,0x01 };
	const unsigned char dot = 0x80;
	
	while(1) {
		DDRC = 0xFF;
		DDRG = 0x0F;
		
		double ms = 0.25;
		
		for (int i = 0; i < 10; i++) {
			
			for (int j = 0; j < 10; j++) {
				
				for (int k = 0; k < 10; k++) {		
					
					for (int l = 0; l < 10; l++) {
						PORTC = digit[i] + dot;
						PORTG = find_sel[0];
						_delay_ms(ms);
						PORTC = digit[j];
						PORTG = find_sel[1];
						_delay_ms(ms);
						PORTC = digit[k];
						PORTG = find_sel[2];
						_delay_ms(ms);
						PORTC = digit[l];
						PORTG = find_sel[3];
						_delay_ms(ms);
					}
					
				}
			}
		}
	}
}