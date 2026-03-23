#include <avr/io.h>
#include <util/delay.h>

#define ANALOG_POT_MAX 905 // my observed maximum value for the potentiometer

void adc_init()
{
    // 0. optimization: disable digital input for pin and set port as input
    DIDR0 |= (1 << ADC0D);
    DDRC &= ~(1 << DDC0);

    // 1. Set voltage reference to AVcc (5v) default
    ADMUX |= (1 << REFS0);

    // 2. Set prescaler to 128
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

    // 3. enable ADC
    ADCSRA |= (1 << ADEN);
}

uint16_t adc_read(uint8_t channel)
{
    // 1. Leaving higher 4 bits unchanged, setting lower 4 bits to channel
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // 2. Start convertion
    ADCSRA |= (1 << ADSC);

    // 3. wait for convertion to complete (ADSC bit is 0)
    while (ADCSRA & (1 << ADSC))
        ;

    // 4. 10-bit value
    return ADC;
}

void usart_init(uint16_t ubrr)
{
    // 0. empty Control and Status register A
    UCSR0A = 0x00;

    // 1. enable Receiver and Transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // 3. set number of data bits (character size): 8bit
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    // Set baud rate
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
}

void usart_print(char *s)
{
    while (*s)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = *s++;
    }
}

void usart_print_uint16(uint16_t n)
{
    char buf[6]; // max value 65535 -> 5chars + '\0'
    buf[5] = '\0';

    if (n == 0)
    {
        buf[4] = '0';
        usart_print(&buf[4]);
    }

    else
    {
        int8_t i = 4;
        while (n > 0 && i >= 0)
        {
            buf[i] = (n % 10) + '0';
            n /= 10;
            i--;
        }
        usart_print(&buf[i + 1]);
    }
}

int main(void)
{
    const uint16_t myubr = (F_CPU / (16UL * 9600)) - 1;
    usart_init(myubr);

    adc_init();
    while (1)
    {
        uint16_t value = adc_read(0);
        usart_print("Value: ");
        usart_print_uint16(value);
        usart_print("\r\n");
        _delay_ms(200);
    }
}
