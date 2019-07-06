
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
	BLINK_DELAY_MS = 100,
};
int a[100];
  int i;
  int c = 0;
  float val;
  float Volts;

void reverse(char *str, int len) 
{ 
    int i=0, j=len-1, temp; 
    while (i<j) 
    { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; j--; 
    } 
}

int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) 
    { 
        str[i++] = (x%10) + '0'; 
        x = x/10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
}

void ftoa(float n, char *res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) 
    { 
        res[i] = '.';  // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter is needed 
        // to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
} 

static void ADC0_init (void)
{
    DDRC &= ~_BV(DDC0); /* AC pin connected to PORTC0(ADC0) */
    ADMUX =
          BVV(MUX0, 0) | BVV(MUX1, 0) | BVV(MUX2, 0) | BVV(MUX3, 0) /* Read ADC0 */
        | BVV(ADLAR, 1) /* Left justify */
        | BVV(REFS0, 1) | BVV(REFS1, 0); /* AVCC as reference voltage */
    ADCSRA =
          BVV(ADPS0, 1) | BVV(ADPS1, 1) | BVV(ADPS2, 1) /* clk/128 */
        | BVV(ADIE, 0) | BVV(ADIF, 0) /* No interrupt */
        | BVV(ADATE, 0) /* No auto-update */
        | BVV(ADSC, 0) /* Don't start conversion */
        | BVV(ADEN, 1); /* Enable */
}

static uint8_t read_ADC(void)
{
    ADCSRA |= _BV(ADSC); /* Start conversion */
    loop_until_bit_is_clear(ADCSRA, ADSC); /* Wait for end of conversion */
    return ADCH; /* lower means more humidity */
}

int main (void)
{
	/* set pin 5 of PORTB for output*/
	DDRB |= _BV(DDB5);
	usart_init();
	a[0] = 0;
	for(i=0; i<100;i++){
    a[i] = i;
  }
  ADC0_init();
  i = 0;
  while(1){
		/* set pin 5 high to turn led on */
		/*PORTB |= _BV(PORTB5);
		_delay_ms(BLINK_DELAY_MS);*/

		/* set pin 5 low to turn led off */
		/*PORTB &= ~_BV(PORTB5);*/
		_delay_ms(BLINK_DELAY_MS);
		  c = a[i] + c;
 		 if (i < 100){
    		i = i+1;
  		} else{
   			i = 0;
    		c = 0;
    		for(int j = 0; j<100; j = j+1){
      			a[j] = 0;
    			}
  		}
  		char greeting[20];
  		val = read_ADC();
  		Volts = val*0.01953;
  		ftoa(Volts,greeting,3);
  		strcat(greeting, "V \n\r");
  		
		usart_puts(greeting);
	}

	return 0;
}

