/*
  Course: Microcontroller Embedded Systems
  Microcontroller: ATMEGA16
  Label: 1st Milestone
  Authors: Loukopoulos Georgios, Kasfikhs Konstantinos
  Date:20/10/2017 
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000
#define Interrupt_SW1 2
#define Interrupt_SW2 3
#define UserInput_SW3 6
#define LED_1 4
#define LED_2 5

int check;

int main(void)
{
	GICR |= (1<<INT0);
	GICR |= (1<<INT1);
	MCUCR = 0xF;
	
	DDRD &= ~(1<<Interrupt_SW1);
	DDRD &= ~(1<<Interrupt_SW2);
	DDRD &= ~(1<<UserInput_SW3);
	DDRD |= (1<<LED_1);
	DDRD |= (1<<LED_2);
	
	sei();
	outputHigh(LED_1);
	outputHigh(LED_2);
	
	while (1)
	{
	}
}

void outputHigh(int output){
	PORTD |= (1<<output);
}

void outputLow(int output){
	PORTD &= ~(1<<output);
}

void waitForSecs(uint32_t ticks){
	TCCR1B = 0x05; //mode
	TCNT1 = ticks; 
	TIMSK |= (1<<TOIE1); //Enable Overflow Interrupt
}



ISR(INT0_vect){
	if( (PIND&(1<<UserInput_SW3)) == 0){
		check = 1;
		waitForSecs(60634); //5secs
	
	}
	else{
		check = 0;
		waitForSecs(64555); //1sec
	
	}
}

ISR(INT1_vect){
	outputHigh(LED_1);
	outputHigh(LED_2);
}

ISR(TIMER1_OVF_vect){
	if(check == 0){
		outputLow(LED_1);
	}
	else{
		outputLow(LED_2);
	}
	TCCR1B = 0x00; 
}
