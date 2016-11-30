/*
 * QTI1.h
 *
 * Created: 11/21/2016 8:01:52 PM
 *  Author: MAE_Labs
 */ 

#ifndef QTI_H
#define QTI_H

void killQTI(){
	//when center QTI goes off kill the robot and stop driving
	//turn on LED
	PORTD |= (1<<PD5); //set LED high
	while(1){
		PORTB &= 0b11100001; //stops
	}
}

void setupQTI(int pin1, int pin2, int pin3, int pin4, int pin5){ 
	//set up all 3 QTI sensors on pins for interrupts
	PCMSK2 |= (1<<pin1) | (1<<pin2) | (1<<pin3);
	PCICR |= (1 << pin4); 
	//set LED to output for when the center QTI goes over the edge
	DDRD |= (1<< pin5); 
}

void wheelSetup(int pin1, int pin2, int pin3, int pin4){
	//make wheels outputs
	DDRB |= (1<<pin1) | (1<<pin2)| (1<<pin3) | (1<<pin4);
}

#endif /* QTI_H */

