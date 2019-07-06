#define BAUD 9600
#include <util/setbaud.h>
#define BVV(bit, val) ((val)?_BV(bit):0)


static void usart_init(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~_BV(U2X0);
#endif
    UCSR0B = BVV(TXEN0, 1) | BVV(RXEN0, 0); /* Only TX */
}

static void usart_tx(char c) {
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = c;
}

static void usart_puts(const char *s)
{
    while(*s != '\0')
    {
        usart_tx(*s++);
    }
}