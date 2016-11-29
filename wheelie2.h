/*
 * wheelie2.h
 *
 * Created: 11/21/2016 8:59:34 PM
 *  Author: MAE_Labs Lindsay Hale
 */ 

#ifndef WHEELIE2_H							// This is to prevent this file from being included more than once in the project
#define WHEELIE2_H

void wheelSetup(){ //PWM
	
	printf("wheelsetup\n");
	
	
	//set timers:
	TCCR1A |= (1<< COM1A1) | (1<< COM1A0)| (1<< COM1B1)| (1<< COM1B0);
	TCCR1B |= (1<<WGM13);
	ICR1 |= 0xFF;

	OCR1A |= 0x0000; //Duty cycle 100%
	OCR1B |= 0x0000;
	
}

#endif /* wheelie2_H_ */