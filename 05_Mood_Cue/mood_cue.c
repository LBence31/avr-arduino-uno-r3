#include <avr/io.h>

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

int main(void)
{
    adc_init();
    while (1)
    {
        uint16_t value = adc_read(0);
    }
}
