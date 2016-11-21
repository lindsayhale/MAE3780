/*
 * QTI.c
 *
 * Created: 11/18/2016 2:11:52 PM
 *  Author: Lindsay Jonah Andy
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include "serial.h"
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(PCINT2_vect){
	if((PIND & 0b00001000)){
		PORTD &= 0b11110111;
		PORTD |= 0b00000100;
		PORTB |= 1<<PB5;
		printf("sense black");
	}else {
		PORTB &= 0b00000000;
		printf("sense white");
	}
}

int main(void) {
	//DDRD |= 0b00000100;
	DDRB |= 1<<PB5;
	PCMSK2 |= 0b00001000;
	PCICR |= 0b00000100;
	sei();
	init_uart();
	while(1){
		//printf(PIND3);
	}
	
}


