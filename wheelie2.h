/*
 * wheelie2.h
 *
 * Created: 11/21/2016 8:59:34 PM
 *  Author: MAE_Labs Lindsay Hale
 */ 


#ifndef wheelie2_H_
#define wheelie2_H_

void straightline(){
	//oneEighty
	PORTD &= (0<<PD6) | (0<<PD5); //stops
	_delay_ms(500); //delay half sec
	PORTD |= (1<<PD5) | (1<<PD4); //turn
	_delay_ms(500); //delay half sec
	PORTD &= (0<<PD4) | (0<<PD5); //stop
	OCR0A |= 0x8000; //Duty cycle 50%
	OCR0B |= 0x8000;
	PORTD |= (1<<PD5) | (1<<PD6); //drive(0,0)
}

void squaretest(){
	PORTD &= (0<<PD6) | (0<<PD5); //stops
	_delay_ms(500); //delay half sec
	PORTD |= (1<<PD5) //turn left
	_delay_ms(500); //delay half sec
	PORTD &= (0<<PD5); //stop
	PORTD |= (1<<PD5) | (1<<PD6); //drive(0,0)
}


void drive(int left, int right){
	//PD5(right) and PD6 (left)
	if (left && right){ 
	//} else if (right) { //right QTI goes off, turn left
		//PORTD |= (1<<PD5);
		//PORTD &= (0<<PD6);
	//} else if (left) { //left QTI goes off, turn right
		//PORTD |= (1<<PD6);
		//PORTD &= (0<<PD5);
	} else {
		PORTD |= (1<<PD5) | (1<<PD6);
	}
}

void wheelSetup(){ //PWM
	DDRD |= (1<<PD5) | (1<<PD6); //make wheel outputs
	
	//set timers:
	TCCR0A |= (1<<WGM00) | (1<< COM0A1) | (1<< COM0A0)| (1<< COM0B1)| (1<< COM0B0);
	TCCR0B |= (1<<WGM02) | (1<<CS00); 

	OCR0A |= 0x0000; //Duty cycle 100%
	OCR0B |= 0x0000;
	
}
/*
void oneEighty(){
	PORTD &= (0<<PD6) | (0<<PD5); //stops
	_delay_ms(500); //delay half sec
	PORTD |= (1<<PD5) | (1<<PD4); //turn
	_delay_ms(500); //delay half sec
	PORTD &= (0<<PD4) | (0<<PD5); //stop
}
*/
#endif /* wheelie2_H_ */
