/*
 * Sonar.h
 *
 * Created: 11/18/2016 2:11:52 PM
 *  Author: Lindsay, Jonah, Andy
*/

#ifndef SONAR_H
#define SONAR_H

void initSonar(){
	TCCR1B |= 0b00000011; //sets CS11 and CS12 to 1
	//TCCR1B |= (1<<CS11) | (1<<CS12);
	TCCR1B &= 0b11111011; //sets CS13 to zero
	PCICR |= 0b00000001; //sets PC I/O to 1
}

void startSonarMeasurement(){
	DDRB |= (1<<PB0); //sets to output
	PORTB |= (1<<PB0); //sets hight
	_delay_us(5); //delay
	PORTB &= 0b11111110; //sets low
	DDRB &= 0b11111110; //sets to input
	PCMSK0 |= 0b00000001; //sets PCINT0 to 1
	//PCMSK0 |= (1<<PCINT0);
}

int getSonar(){
	startSonarMeasurement(); //start measurement
	int irange; //intialize
	irange = 0.02712 * (float)itime; //find range
	return (uint16_t)irange; //return distance
}


//does this make sense?? I chose 28 because the circle is 36 inches in Diamater (3ft right) and 
//the robot is 8 by 8
bool seeOpponent(){
	if (getSonar() <= 25){ //sense robot within circle
		return TRUE; //return true if find robot in circle
	} else { 
		return FALSE; //return fale if dont sense robot at that point
	}
}

#endif /* SONAR_H */
