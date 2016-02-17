/*
 * RCC_AVR_Receiver.c
 *
 * Created: 02/02/2016 21:35:52
 * Author : Artem
 */ 

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nRF24L01.h"

int dataLen = 1;
uint8_t *data;

ISR(INT0_vect)	//vektorn som g?r ig?ng n?r transmit_payload lyckats s?nda eller n?r receive_payload f?tt data OBS: d? Mask_Max_rt ?r satt i config registret s? g?r den inte ig?ng n?r MAX_RT ?r uppn?d ? s?ndninge nmisslyckats!
{
    cli();	//Disable global interrupt
    
    SETBIT(PORTD, 7); //led on
    _delay_ms(50);
    CLEARBIT(PORTD, 7); //led off
    
    //USART_Transmit('1');
    
    SetCELow();
    
    //Receiver function to print out on usart:
    data = WriteToNrf(R, R_RX_PAYLOAD, data, dataLen);	//l?s ut mottagen data
    reset();
    
    for (int i=0;i<dataLen;i++)
    {
        USART_Transmit(data[i]);
    }
    
    sei();    
}
 
ISR(USART_RX_vect)	///Vector that triggers when computer sends something to the Atmega88
{
    SETBIT(PORTD, 7); //led on
    _delay_ms(50);
    CLEARBIT(PORTD, 7); //led off
    
    uint8_t W_buffer[dataLen];	//Creates a buffer to receive data with specified length (ex. dataLen = 5 bytes)
    
    int i;
    for (i=0;i<dataLen;i++)
    {
        W_buffer[i]=USART_Receive();	//receive the USART
        USART_Transmit(W_buffer[i]);	//Transmit the Data back to the computer to make sure it was correctly received
        //This probably should wait until all the bytes is received, but works fine in to send and receive at the same time... =)
    }    
         
    transmit_payload(W_buffer);	//S?nder datan
            
    USART_Transmit('#');	//visar att chipet mottagit datan...
}

void init_led(void){
    DDRD |= (1<<PORTD7); // init PB7 as output for led
    
    SETBIT(PORTD, 7);
    _delay_ms(500);
    CLEARBIT(PORTD, 7);    
}

void INT0_interrupt_init(void){
    DDRD &= ~(1<<DDD2);	//Extern interrupt p? INT0, dvs s?tt den till input!    
    CLEARBIT(PORTD, 2);
       
    MCUCR |= (1<<ISC01);// INT0 falling edge	PD2
    MCUCR &= ~(1<<ISC00);// INT0 falling edge	PD2

    EIMSK |= (1<<INT0);	//enable int1
       
    //GIMSK=0b11000000; //разрешаем прерывание int0 и int1 -  кнопка
    //MCUCR=0b00001111;// int by rising front -  для кнопки 1 и 2
    EIFR=0b01000000;          
}

int main(void)
{    
    init_led(); 
    
    _delay_ms(5000);
    
    SETBIT(PORTD, 7);
    _delay_ms(1000);      
        
    USART_Init();
    InitSPI();
    INT0_interrupt_init();   
    
    //nrf24L01_init();     
    
    USART_Transmit('0');
    //USART_Transmit(GetReg(STATUS));
    
    //CLEARBIT(PORTD, 7);    
    sei();//разрешение прерываний
        
    CLEARBIT(PORTD, 7);

    while(1){}
}


