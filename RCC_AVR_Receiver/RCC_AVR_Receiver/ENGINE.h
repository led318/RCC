#include <avr/io.h>

#define eng_min 0
#define eng_max 255
#define eng_steps_number 3
#define eng_step (eng_max - eng_min) / eng_steps_number

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
    int new_angle = 0;
    
    if(direction){
        new_angle = eng_min + (eng_step * power);    
        CLEARBIT(PORTC, 2);        
    } else {
        new_angle = eng_max - (eng_step * power);
        SETBIT(PORTC, 2);                
    }
    
    ENGINE_set(new_angle);
}

void ENGINE_set_stop(){
    ENGINE_set_int(0, 0);
}

void ENGINE_init(){   
    TCCR0A|=(1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00);    
    TCCR0B|=(1 << CS01);
    
    DDRD|=(1<<DDD5)|(1<<DDD6);	//PWM Pins as Out
    DDRC|=(1<<DDC2);
    
    ENGINE_set_stop();
}
