 /*
 * main.c
 *
 *
 *  Created on: Nov 17, 2015
 *      Author: Lindsay, Jonah, Andrew
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
//#include "motor.h"
//#include "active.h"
#include "QTI.h"
#include "Sonar.h"

volatile int itime;

ISR(PCINT2_vect){ 
	//Interrupt for QTI's
	if (PIND & 0b00001000) { //pin PD3
		PORTD &= 0b11110111;
		PORTD |= 0b00000100;
		PORTB |= 1<<PB5;
		printf("sense black");
	} else {
		PORTB &= 0b00000000;
		printf("sense white");
	} 
}

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

int main(void){
	//choose pin
	//set as input/output
	//interrupt stuff
	//enable shit
	init_uart();
	sei();
	startSonar();
	while(){
		//loop that the robot goes through
	}
	//shut down robot when white line

}
