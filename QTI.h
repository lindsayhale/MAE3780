/*
 * QTI.h
 *
 * Created: 11/18/2016 2:11:52 PM
 *  Author: Lindsay Jonah Andy
 */ 

/*ISR(PCINT2_vect){
	if((PIND & 0b00001000)){
		PORTD &= 0b11110111;
		PORTD |= 0b00000100;
		PORTB |= 1<<PB5;
		printf("sense black");
	}else{
		PORTB &= 0b00000000;
		printf("sense white");
	}
} */
void killQTI(int pin){
	//when center QTI goes off kill the robot
}

void alertQTI(int pin1, int pin2){
	//front QTI senses white
	//send left, right, both to main??
}

void setupQTI(int pin){ //make applicable for all QTI
	//DDRD |= 0b00000100;
	DDRB |= 1<<pin;
	PCMSK2 |= 0b00001000; //fix
	PCICR |= 0b00000100; //fix
}


