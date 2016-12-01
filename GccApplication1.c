/*
 * robot.c
 *
 * Created: 11/22/2016 1:10:48 PM
 *  Author: MAE_Labs
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
#include "QTI.h"
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
	
	if (seeOpponent() == 0){
	//PB0 = sonar, PB1 = forward right, PB4 = backwards right, PB2 = forward left, PB3 = backwards left
		
		if ((~PIND & (1<<PD2)) && (~PIND & 1<<PD3)) { //both pins go off PD2 and PD3
			PORTB &= 0b11111001; //stops
			PORTB |=  (1<<PB4) | (1<<PB3); //backwards
			_delay_ms(500); //delay
			PORTB &= 0b11100111; //stops 
			PORTB |= (1<<PB2) | (1<<PB4); //spin left
			_delay_ms(500); //delay
			i = 0; //continue to spin left in main
			
		} else if (~PIND & 1<<PD2){ // PD2 goes off turn left
			PORTB &= 0b11110101; //stops wheels
			PORTB |= (1<<PB4) | (1<<PB2); //spin left
			_delay_ms(500); //delay
			PORTB &= 0b11100111;
			PORTB |= (1<<PB1) | (1<<PB2); //drive forward
			_delay_ms(50); //delay
			i = 0; //continue to spin left in main

		} else if (~PIND & 1<<PD3){ // PD3 goes off turn right
			PORTB &= 0b11101011; //stops wheels
			PORTB |= (1<<PB3) | (1<<PB1); //spin right
			_delay_ms(500); //delay
			PORTB &= 0b11100111;
			PORTB |= (1<<PB1) | (1<<PB2); //drive forward
			_delay_ms(50); //delay
			i = 1; //spin right in main

		} else { //no white under any sensors
			PORTB &= 0b11100111;
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
	wheelSetup(PB4, PB1, PB2, PB3);

	//enable interrupt
	sei();
	
	i = 0; //initialize i to spin left first

	while(1){
		while (seeOpponent() == 0){
			//do not see opponent- spin either left or right until you do
			if (i == 0){
				PORTB &= 0b11110101;
				PORTB |= (1<<PB4) | (1<<PB2); //spin left
				
			} else {
				PORTB &= 0b11101011;
				PORTB |= (1<<PB3) | (1<<PB1); //spin right
			}
		}

		while(seeOpponent() == 1){
			//drive if you see the opponent in front of you
			PORTB &= 0b11100111;
			PORTB |= (1<<PB1) | (1<<PB2); //drive
		}
	}
}
