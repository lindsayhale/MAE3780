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
int i;

ISR(PCINT2_vect){
	//Interrupt for QTI's
	//FIX ME: does it sense the other robot when front 1 QTI's go off???
	if ((~PIND & (1<<PD2)) && (~PIND & 1<<PD3)) { //both pin PD1 and PD0
		OCR1A = 0xffff;
		OCR1B = 0xffff;
		//PORTB &= 0b11110110; //stops
		PORTB |=  (1<<PB0) | (1<<PB3); //backwards
		_delay_ms(1000);
		PORTB &= 0b11110110; //stops
		_delay_ms(1000);
		OCR1A = 0x0000;
		PORTB |= (1<<PB3);
		//PORTB|=  (1<<PB3) ; //right
		_delay_ms(1500); //delay
		OCR1A = 0xffff;
		PORTB &= 0b11110111;
		i = i + 1; 
		
	} else if (~PIND & 1<<PD2){ // turn left
		OCR1A = 0xffff;
		//OCR1B = 0xffff;
		//
		OCR1B = 0x0000;
		PORTB |= (1<<PB0); //turn left
		_delay_ms(500); //delay half sec
		PORTB &= 0b11110110; //stops
		
	} else if (~PIND & 1<<PD3){ // turn right
		//OCR1A = 0xffff;
		OCR1B = 0xffff;
		//PORTB &= 0b11110110; //stops
		OCR1A = 0x0000;
		PORTB |= (1<<PB3); //turn left
		_delay_ms(500); //delay half sec
		PORTB &= 0b11110110; //stops
		
		
		
	} else { //no white under any sensors
		//drive
		//PORTB &= 0b11110110;
		OCR1A = 0xffff;
		OCR1B = 0xffff;
	}
}


int main(void){
	
	init_uart();
	//startSonar();
	
	//set up pins
	PCMSK2 |= (1<<PD2) | (1<<PD3);
	PCICR |= (1 << PCIE2);
	
	//wheel setup
	DDRB |= (1<<PB0) | (1<<PB1)| (1<<PB2) | (1<<PB3); //make wheel outputs
	
	//PWM
	//set timers:
	TCCR1A |= (1<< COM1A1) | (1<< COM1A0)| (1<< COM1B1)| (1<< COM1B0);
	TCCR1B |= (1<<WGM13) | (1<<CS10);
	ICR1 |= 0xFF;

	OCR1A = 0x0000; //Duty cycle 100%
	OCR1B = 0x0000;
	
	sei();
	i = 0;
	while(1){
		//drive
		//PORTB &= 0b11110110;
		if (i == 0) {
			OCR1A = 0x0000;
			OCR1B = 0x0000; //drive(0,0)
		} else if (i == 1){
			//printf("else");
			OCR1A = 0x0008; //Duty cycle 50%
			OCR1B = 0x0008;
		} else {
			OCR1A = 0xffff;
			OCR1B = 0xffff;
		}
		
	}
}
