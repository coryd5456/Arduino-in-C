#include <avr/io.h>
#include <math.h>
#define PI 3.14159265
double a[256];
int b[256];


int main(void){


for (int i = 0; i < 255; ++i)
{
	a[i] = 75*sin(2*PI*i/255);
	b[i] = a[i] + 128;

}

DDRD = 0xFF;
PORTD = 0b00000110;
while(1){
for (int i = 0; i < 255; ++i)
{
	PORTD = b[i];
}
}
	
}

