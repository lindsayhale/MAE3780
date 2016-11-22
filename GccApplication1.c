/*
 * GccApplication1.c
 *
 * Created: 11/21/2016 8:00:03 PM
 *  Author: MAE_Labs
 */ 



#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <util/delay.h>
#include "QTI1.h"
#include "wheelie.h"
//#include "Sonar.h"
//#include "motor.h"
//#include "active.h"

volatile int itime;
//volatile int go = 1; //whether or not the center QTI sees white

ISR(PCINT2_vect){
	//Interrupt for QTI's
	//FIX ME: does it sense the other robot when front 1 QTI's go off???
	if (~PIND & 1<<PD2) { //pin PD2 attached to center QTI
		//go = 0; //stop while loop
		//killQTI(PD2);
		//turn LED on
	} else if ((~PIND & (1<<PD1)) && (~PIND & 1<<PD0)) { //both pin PD1 and PD0
		//turn 90 degrees
		//OCR0A |= 0x8000;
		//OCR0B |= 0x8000;
		oneEighty(); //turn off wheels
		OCR0A |= 0x8000; //Duty cycle 50%
		OCR0B |= 0x8000;
		drive(0,0);
		
	} else if (~PIND & 1<<PD0){ // just pin PD0 (right)
		//turn 90 degrees
		oneEighty(); //turn off wheels
		OCR0A |= 0x8000; //Duty cycle 50%
		OCR0B |= 0x8000;
		drive(0,0);
		
	} else if (~PIND & 1<<PD1){ // just pin PD1 (left)
		//turn 90 degrees
		oneEighty(); //turn off wheels
		OCR0A |= 0x8000; //Duty cycle 50%
		OCR0B |= 0x8000;
		drive(0,0);
	} else { //no white under any sensors
		drive(0,0);
	}
}

ISR(PCINT0_vect){
	//Interrupt for Sonar
	unsigned char sreg;
	if(PINB & 1<<PB0) { //pin PB0
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
	//startSonar();
	setupQTI(PD0, PD1, PD2);
	wheelSetup();
	drive(0,0);
	
	while(1){
		//loop that the robot goes through
	}
	//shut down robot when white line

}