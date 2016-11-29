/*
 * station3.c
 *
 * Created: 11/22/2016 1:10:48 PM
 *  Author: MAE_Labs
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
#include "wheelie2.h"
//#include "QTI1.h"


ISR(PCINT2_vect){
	//Interrupt for QTI's
	//FIX ME: does it sense the other robot when front 1 QTI's go off???
	if ((~PIND & (1<<PD2)) && (~PIND & 1<<PD3)) { //both pin PD1 and PD0
		PORTB &= 0b11110000; //stops
		PORTB |=  (1<<PB0) | (1<<PB2); //backwards
		_delay_ms(1000);
		PORTB &= 0b11110000; //stops
		_delay_ms(1000);
		PORTB|= (1<<PB1) | (1<<PB2) ; //right
		_delay_ms(2500); //delay
		
		OCR1A |= 0xb000; //Duty cycle 50%
		OCR2A |= 0xb000;     
		
	} else if (~PIND & 1<<PD2){ // turn left
		PORTB &= 0b11110000; //stops
		PORTB |= (1<<PB3); //turn left
		_delay_ms(500); //delay half sec
		
	} else if (~PIND & 1<<PD3){ // turn right
		PORTB &= 0b11110000; //stops
		PORTB |= (1<<PB1); //turn right
		_delay_ms(500); //delay half sec
		
	} else { //no white under any sensors
		//drive
		PORTB &= 0b11111010;
		PORTB |= (1<<PB3) | (1<<PB1);
	}
}


int main(void){
	
	init_uart();
	sei();
	//startSonar();
	
	//set up pins
	PCMSK2 |= (1<<PD2) | (1<<PD3);
	PCICR |= (1 << PCIE2);
	
	//wheel setup
	DDRB |= (1<<PB0) | (1<<PB1)| (1<<PB2) | (1<<PB3); //make wheel outputs
	
	//PWM
	wheelSetup();
	
	while(1){
		//drive
		PORTB &= 0b11111010;
		PORTB |= (1<<PB3) | (1<<PB1); //drive(0,0)
	}
}