/* GPIO로 LED 켜고 끄기 1번 예
LED 8개로 연결되어 있는 포트: PORT A (PA)
- 비트 7: LED7(LD1), 비트 6: LED6(LD2)
- ...
- 비트 1: LED1(LD7), 비트 0: LED0(LD8) */

 #include <avr/io.h>  //ATmage128 레지스터 정의
 int main(){
 	DDRA= 0xff; // 포트 A를 출력 포트로 사용 
 	PORTA = 0xff; // 0xff = 0b11111111, LED 모두 ON
 }