/*
 * milestone3.c
 *
 * Created: 11/21/2016 9:32:12 PM
 *  Author: MAE_Labs Lindsay, Jonah, Andy
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
#include "QTI1.h"
#include "wheelie2.h"

ISR(PCINT2_vect){
	//Interrupt for QTI's
	//FIX ME: does it sense the other robot when front 1 QTI's go off???
	if (~PIND & 1<<PD2) { //pin PD2 attached to center QTI
		//go = 0; //stop while loop
		//killQTI(PD2);
		//turn LED on
	} else if ((~PIND & (1<<PD1)) && (~PIND & 1<<PD0)) { //both pin PD1 and PD0
		straightline();
		//squareTest();
	} else if (~PIND & 1<<PD0){ // just pin PD0 (right)
		straightline();
		//squareTest();
	} else if (~PIND & 1<<PD1){ // just pin PD1 (left)
		straightline();
		//squareTest();
	} else { //no white under any sensors
		drive(0,0);
	}
}

int main(void){
	//choose pin
	//set as input/output
	//interrupt stuff
	//enable shit
	init_uart();
	sei();
	//startSonar();
	setupQTI(PD0, PD1, PD2);
	wheelSetup();
	drive(0,0);
	while(1){}
}
