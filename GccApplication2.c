/*
 * GccApplication2.c
 *
 * Created: 11/22/2016 1:10:48 PM
 *  Author: MAE_Labs
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
//#include "wheelie2.h"
//#include "QTI1.h"


ISR(PCINT2_vect){
	//Interrupt for QTI's
	//FIX ME: does it sense the other robot when front 1 QTI's go off???
	
	//if (~PIND & 1<<PD1) { //pin PD2 attached to center QTI
		//go = 0; //stop while loop
		//killQTI(PD2);
		//turn LED on
	if ((~PIND & (1<<PD2)) && (~PIND & 1<<PD3)) { //both pin PD1 and PD0
		PORTB &= 0b11111000; //stops
		_delay_ms(500); //delay half sec
		PORTB |=  (1<<PB1); //turn left
		_delay_ms(500);
		PORTB|= (1<<PB2);
		_delay_ms(500); //delay       
		PORTB &= 0b11111000; //stops
		
		while((~PIND & (1<<PD2))){
			PORTB |= (1<<PB2); //turn left
		}
		while((~PIND & (1<<PD3))){
			PORTB |= (1<<PB0); //turn right
		}
		/*
		PORTB &= 0b11111000; //stops
		_delay_ms(500);
		PORTB|= (1<<PB2)| (1<<PB1); 
		_delay_ms(6000); //delay half sec
		PORTB &= 0b11111000; //stops
		PORTB |= (1<<PB2) | (1<<PB0); //drive(0,0)
		*/
	} else if (~PIND & 1<<PD2){ // turn left
		PORTB &= 0b11111000; //stops
		PORTB |= (1<<PB2); //turn left
		_delay_ms(500); //delay half sec
		PORTB &= 0b11111000; //stops
		
	} else if (~PIND & 1<<PD3){ // turn right
		PORTB &= 0b11111000; //stops
		PORTB |= (1<<PB0); //turn right
		_delay_ms(500); //delay half sec
		PORTB &= 0b11111000; //stops
		
	} else { //no white under any sensors
		//drive
		PORTB &= 0b11111101;
		PORTB |= (1<<PB0) | (1<<PB2);
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
	DDRB |= (1<<PB0) | (1<<PB1)| (1<<PB2); //make wheel outputs
	//DDRB |= (1<<PB0);
	//PORTB |= (1<<PB0);
	
	//set timers:
	//TCCR0A |= (1<<WGM00) | (1<< COM0A1) | (1<< COM0A0)| (1<< COM0B1)| (1<< COM0B0);
	//TCCR0B |= (1<<WGM02) | (1<<CS00);

	//OCR0A |= 0x8000; //Duty cycle 50%
	//OCR0B |= 0x8000;
	
	while(1){
		//drive
		PORTB &= 0b11111101;
		PORTB |= (1<<PB2) | (1<<PB0); //drive(0,0)
		_delay_ms(500);
	}
	//shut down robot when white line

}
