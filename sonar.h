/*
 * Sonar.h
 *
 * Created: 11/18/2016 2:11:52 PM
 *  Author: Lindsay, Jonah, Andy
#include <avr/io.h>
#define F_CPU 16000000UL
#include "serial.h"
#include <avr/interrupt.h>
#include <util/delay.h>
 */ 
volatile int itime;

void initSonar()
{
	//printf("initSonar \n");
	TCCR1B |= 0b00000011; //sets CS11 and CS12 to 1
	TCCR1B &= 0b11111011; //sets CS13 to zero
	PCICR |= 0b00000001; //sets PC I/O to 1
}

void startSonarMeasurement(){
	//printf("start \n");
	DDRB |= 0b00000001; //pin 8, PB0, PCINT0
	PORTB |= 0b00000001;
	_delay_us(5);
	PORTB &= 0b11111110;
	DDRB &= 0b11111110;
	PCMSK0 |= 0b00000001; //sets PCINT0 to 1
}

/*ISR(PCINT0_vect)
{
	unsigned char sreg;
	if(PINB & 0b00000001){
		sreg = SREG;
		cli();
		TCNT1 = 0;
		SREG = sreg;
		}else{
		PCMSK0 &= 0b11111110; //sets PCINT0 to 0
		itime = TCNT1;
	}
}*/

void getSonar(){
	//printf("getSonar\n");
	startSonarMeasurement();
	int irange;
	irange = 0.02712 * (float)itime;
	printf("Distance: %u [inches]\r\n", (uint16_t)irange);
}


void startSonar(){
	initSonar();
	while(1)
	{
		getSonar();
		_delay_ms(500);
	}
