 #include <avr/io.h>

 #define MAX_LED_NR 7

 void initLEDport(char key)
 {
	 switch (key)
	 {
		 case 'A':
		 DDRA = 0b11111111;
		 PORTA = 0xFF;
		 break;
		 case 'B':
		 DDRB = 0b11111111;
		 PORTB = 0xFF;
		 break;
		 case 'C':
		 DDRC = 0b11111111;
		 PORTC = 0xFF;
		 break;
		 case 'D':
		 break;
		 DDRD = 0b11111111;
		 PORTD = 0xFF;
		 break;
		 default:
		 DDRC = 0b11111111;
		 PORTC = 0xFF;
		 break;
	 }
 }

 void writeAllLEDs(unsigned char pattern)
 {
	 // Inverted as system is Active low
	 PORTC = ~pattern;
 }

 void turnOnLED(unsigned char led_nr)
 {
	 unsigned char mask;
	 if (led_nr <= MAX_LED_NR)
	 {
		 mask = ~(0b00000001 << led_nr);
		 PORTC = PORTC & mask;
	 }
 }

 void turnOffLED(unsigned char led_nr)
 {
	 unsigned char mask;
	 if (led_nr <= MAX_LED_NR)
	 {
		 mask = 0b00000001 << led_nr;
		 PORTC = PORTC | mask;
	 }
 }

 void toggleLED(unsigned char led_nr)
 {
	 unsigned char mask;
	 if (led_nr <= MAX_LED_NR)
	 {
		 mask = 0b00000001 << led_nr;
		 PORTC = PORTC ^ mask;
	 }
 }
