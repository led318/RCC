#include <avr/io.h>

#define middle 87
#define steps_number 12
#define max_angle 24
#define min_angle max_angle / steps_number
#define min middle - max_angle
#define max middle + max_angle

int current;

int SERVO_get_current(){
    return current;
}

void SERVO_turn(int value){	
	if(value < min){
		value = min;
	}else if(value > max){
		value = max;
	}
	
	current = value;
    
	OCR1A=current;    
}
	
void SERVO_turn_min(){
    SERVO_turn(min);
}

void SERVO_turn_max(){
    SERVO_turn(max);
}

void SERVO_turn_up(){
    SERVO_turn(current + 1);
}

void SERVO_turn_down(){
    SERVO_turn(current - 1);
}

void SERVO_turn_middle(){
    SERVO_turn(middle);
}

void SERVO_turn_int(int direction, int power){
    if(direction == 0){
        direction = -1;
    }   

    int new_angle = middle + (direction * min_angle * power); 
    SERVO_turn(new_angle);
}

void SERVO_init(){
	TCCR1A|=(1<<COM1A1)|(1<<WGM11);		 	//NON Inverted PWM // (1<<COM1B1) - add for B output
    //TCCR1B|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);	
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);	//PRESCALER=64 MODE 14(FAST PWM)

	ICR1=4999;	//fPWM=50Hz (Period = 20ms Standard).
	
	DDRB|=(1<<DDB1)|(1<<DDB2);	//PWM Pins as Out
	
	SERVO_turn_middle();
}
