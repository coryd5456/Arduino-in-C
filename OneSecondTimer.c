#include <avr/io.h>
#include <avr/interrupt.h>



int main(void)
{
	DDRB = 0x01 ;
	
	TCCR1B = (1 << WGM12); // Set Clear Timer on Compare bit. 
	OCR1A  = 19531; //Number of ticks to be compared to for 1 second.
	TIMSK1 = (1 << OCIE1A); //Sets interrupt

	sei();//interrupt function from interrupt.h

	TCCR1B |= (1 << CS12)|(1 << CS10);//Start at 1024 prescalar
	while(1){

	}

	return 0;
}

ISR(TIMER1_COMPA_vect){
		PORTB ^= (1 << PORTB0); // toggles LED on or off so we can see what is happening
		//Note PORTB0 = Pin D8 on Arduino Nano
}
