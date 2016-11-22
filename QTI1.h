/*
 * QTI1.h
 *
 * Created: 11/21/2016 8:01:52 PM
 *  Author: MAE_Labs
 */ 


#ifndef QTI1_H_
#define QTI1_H_

void killQTI(int pin){
	//when center QTI goes off kill the robot
	//stop driving
	//turn all 4 wheels off
	
}

void alertQTI(int pin1, int pin2){
	//front QTI senses white
	//send left, right, both to main??
}

void setupQTI(int pin1, int pin2, int pin3){ //make applicable for all QTI
	//DDRD |= (1<<pin1) | (1<<pin2) | (1<<pin3);
	PCMSK2 |= (1<<pin1) | (1<<pin2) | (1<<pin3);
	PCICR |= (1 << PCIE2); 
}




#endif /* QTI1_H_ */