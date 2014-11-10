#include <avr/io.h>
//#include <util/delay.h>

void delay_ms(uint8_t ms) 
{
   uint16_t delay_count = F_CPU / 17500;
   volatile uint16_t i;
 
   while (ms != 0) {
     for (i=0; i != delay_count; i++);
     ms--;
   }
}

int main(void)
{
    DDRD |= (1 << PD6);    // LED on PD5. Setting it as output
    
    while(1)
    {
        if (ACSR & (1 << ACO)) {            // comparator output high?
            // flash LED if comparator output is high
            PORTD |=  (1 << PD6);			// switch PD5 LED on
        }
        else {
            // comparator output low, so switch LED off                                        
            PORTD &= ~(1 << PD6);			// switch PD5 LED off
        }            
    }
}