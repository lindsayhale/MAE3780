/*
 * milestone4.c
 *
 * Created: 11/22/2016 1:10:48 PM
 *  Author: MAE_Labs
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
#include "QTI1.h"
#include "sonar.h"

volatile int itime;
int i;

ISR(PCINT0_vect){ 
	//Interrupt for Sonar
	unsigned char sreg;

	if(PINB & 0b00000001) { //pin PB0
		sreg = SREG;
		cli();
		TCNT1 = 0;
		SREG = sreg;
	} else {
		PCMSK0 &= 0b11111110; //sets PCINT0 to 0
		itime = TCNT1;
	}

}

ISR(PCINT2_vect){
	//Interrupt for QTI's
	//FIX ME: does it sense the other robot when front 1 QTI's go off???
	if (~PIND & 1<<PD4){ 
		killQTI();
	}
	
	if (!(seeOpponent())){
		if ((~PIND & (1<<PD2)) && (~PIND & 1<<PD3)) { //both pins go off PD2 and PD3
			PORTB &= 0b11111001; //stops
			PORTB |=  (1<<PB0) | (1<<PB3); //backwards
			_delay_ms(500); //delay
			PORTB &= 0b11110111; //stops 
			PORTB |= (1<<PB2) | (1<<PB0); //spin left
			i = 0; //continue to spin left in main
			
		} else if (~PIND & 1<<PD2){ // PD2 goes off turn left
			PORTB &= 0b11111101; //stops left wheel
			PORTB |= (1<<PB0) | (1<<PB2); //spin left
			i = 0; //continue to spin left in main

			
		} else if (~PIND & 1<<PD3){ // turn right
			PORTB &= 0b11111011; //stops right wheel
			PORTB |= (1<<PB3) | (1<<PB1); //spin right
			i = 1; //continue to spin right in main

		} else { //no white under any sensors
			PORTB &= 0b11110110;
			PORTB |= (1<<PB1) | (1<<PB2); //drive forward
		}
	}
}


int main(void){
	
	init_uart();

	//setup interrupt for QTI pins and set the LED to an output 
	setupQTI(PD2, PD3, PD4, PCIE2, PD5); //pins for QTIs, interrupt, and LED

	//setup interrupt for sonar
	initSonar();

	//set wheels to outputs
	wheelSetup(PB0, PB1, PB2, PB3);

	//enable interrupt
	sei();
	
	i = 0; //initialize i to spin left first

	while(1){

		while (!(seeOpponent())){
			if (i == 0){
				PORTB |= (1<<PB0) | (1<<PB2); //spin left
			} else {
				PORTB |= (1<<PB3) | (1<<PB1); //spin right
			}
		}

		while(seeOpponent()){
			//drive
			PORTB &= 0b11110110;
			PORTB |= (1<<PB1) | (1<<PB2); //drive
		}
	}
}