#include <avr/io.h>
//#include <util/delay.h>

#define FAN PD6
#define LIGHT PD5
#define RESET PD3

void delay_ms(uint8_t ms) 
{
   uint16_t delay_count = F_CPU / 17500;
   volatile uint16_t i;
 
   while (ms != 0) {
     for (i=0; i != delay_count; i++);
     ms--;
   }
}

void switchOn()
{
	PORTD |=  (1 << FAN);
	PORTD |=  (1 << LIGHT);
}
void switchOff()
{
	PORTD &= ~(1 << FAN);
	PORTD &= ~(1 << LIGHT);
}
/*
void resetPressed()
{
	switchOn();
	for(int i = 0;i < 100; i++)//10 seconds delay
	{
		delay_ms(1000); 
	}
}
*/
void resetPressed()
{
	switchOff();
	delay_ms(500);
	switchOn();
	delay_ms(500);
	switchOff();
	delay_ms(500);
	switchOn();
}

int main(void)
{
    DDRD |= (1 << FAN);    // Setting it as output
    DDRD |= (1 << LIGHT);
	DDRD &= ~(1 << RESET);  //Input
	PORTD |= (1 << RESET);    // enable pull-up resistor
	int state = 0;
	int timerVal = 0;
	switchOn();
    while(1)
    {
		if (!(PIND & (1 << RESET))) {   //reset switch closed
			state = 0;
			resetPressed();
			
		}
		if(state==0) { 		//Normal State------------------------------
			if (!(ACSR & (1 << ACO))) { 		//Latch Closed
				state = 1;
				timerVal = 0;
			}
		}
		else if (state==1) { 		//Intermediate----------------------
			if (ACSR & (1 << ACO)) { 		//Latch Opened
				state = 0;
			}
			else if(timerVal>10000) {
				state = 2;
				switchOff();
			}
			timerVal++;
		}
        else if(state==2) { 		//Off State-------------------------
			if (ACSR & (1 << ACO)) { 		//Latch Opened
				state = 0;
				switchOn();
			}
		}
		        
    }
}
