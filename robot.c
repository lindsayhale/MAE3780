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
#include "sonar.h"

ISR(){
	//Interrupt for QTI's
}
ISR(){
	//Interrupt for Sonar
}

int main(void){
	//choose pin
	//set as input/output
	//interrupt stuff
	//enable shit
	sei();
	while(){
		//loop that the robot goes through
	}
	//shut down robot when white line

}
