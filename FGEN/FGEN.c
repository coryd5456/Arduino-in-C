#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "ADC.h"

float dutyCycle =0.0;
int j = 0;
int N = 200;
float a[200];
char greeting[20];
int i = 0;
float e[2];
int val;

int main(void){

	for (int i = 0; i < N; ++i)
	{
		a[i] = i/2;
	}

	val = a[0];


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


	usart_init();
	ADC0_init();
	while(1){


		if (i > 199)
		{
			i = 0;
		}else{
			i++;
			/* code */
			_delay_ms(1);//from delay.h
			dutyCycle = a[i];
			//e[1] = (a[i]-(val*100)/255);
			//dutyCycle = (val*100)/255 + e[1]*0.1;
			val = read_ADC();
			//float val = read_ADC()*0.01953;
			ftoa(val,greeting,3);
  			strcat(greeting, "V \n\r");
  		
			usart_puts(greeting);

			

			 

			
			
		}
		



	}
}

ISR(TIMER0_OVF_vect){
	//What you would like to happen during the interrupts
	//dynamic PWM code mid program.
	OCR0A = (dutyCycle/100.0)*255;
}

/*ISR(ADC_vect){
	read_ADC();
}*/