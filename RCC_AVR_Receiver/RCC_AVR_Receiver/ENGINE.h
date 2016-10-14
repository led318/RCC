#include <avr/io.h>

#define eng_middle 128
#define eng_steps_number 3
#define eng_max_angle 126
#define eng_min_angle eng_max_angle / eng_steps_number
#define eng_min eng_middle - eng_max_angle
#define eng_max eng_middle + eng_max_angle

int current;

int ENGINE_get_current(){
    return current;
}

void ENGINE_set(int value){
    if(value < eng_min){
        value = eng_min;
        }else if(value > eng_max){
        value = eng_max;
    }
    
    current = value;
    
    OCR0A=current;
}

void ENGINE_set_int(int direction, int power){
    if(direction == 0){
        direction = -1;
    }

    int new_angle = eng_middle + (direction * eng_min_angle * power);
    ENGINE_set(new_angle);
}

void ENGINE_set_middle(){
    ENGINE_set_int(0, 0);
}

void ENGINE_init(){   
    TCCR0A|=(1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00);    
    TCCR0B|=(1 << CS01);
    
    DDRD|=(1<<DDD5)|(1<<DDD6);	//PWM Pins as Out
    
    ENGINE_set_middle();
}
