#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

double dutyCycle =5.0;
int j = 0;

int main(void){

	DDRD = (1 << PORTD6); //PortD6 coorisponds to pin D6 making it an output. 
	//Pin D6 can be used for PWM because it is connected to OC0A.
	
	TCCR0A = (1 << COM0A1)|(1<<WGM00)|(1 << WGM01);
	//when timer is starting over the PWM will be turned on and when it gets to the compare value it will be turned off.


	TIMSK0 = (1 << TOIE0);
	// We want to set the PWM to reset when there is an overflow 

	OCR0A = (dutyCycle/100.0)*255.0;//Value for time on (0-100)
	//Value 0-255 is the duration that we want it on. 
	sei(); //Starts the PWM
	
	TCCR0B = (1 << CS00)|(1 << CS02);
	//Setting the prescalar

	while(1){


		for (int i = 0; i < 99; ++i)
		{
			/* code */
			_delay_ms(20);//from delay.h
			dutyCycle +=1;
		}
		for (int i = 0; i < 99; ++i)
		{
			_delay_ms(20);//from delay.h
			dutyCycle -=1;
		}



	}
}

ISR(TIMER0_OVF_vect){
	//What you would like to happen during the interrupts
	//dynamic PWM code mid program.
	OCR0A = (dutyCycle/100.0)*255;
}
