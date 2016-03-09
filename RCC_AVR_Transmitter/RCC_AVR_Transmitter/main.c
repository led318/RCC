/*
* RCC_AVR_Transmitter.c
*
* Created: 31/01/2016 14:04:18
* Author : Artem
*/

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nRF24L01.h"

int dataLen = 1;

void LedOn()
{
    SETBIT(PORTB, 2); //led on
}

void LedOff()
{
    CLEARBIT(PORTB, 2); //led off
}

void LedBlink(int duration)
{
    LedOn();
    
    duration /= 10;
    
    while(duration--) {
        _delay_ms(10);
    }
    
    LedOff();
}

ISR(INT0_vect)
{
    cli();	//Disable global interrupt

    LedBlink(50);

    uint8_t W_buffer[dataLen];
    W_buffer[0] = '0';
    
    transmit_payload(W_buffer);
    USART_Transmit(W_buffer[0]);
    USART_Transmit(GetReg(STATUS));  

    sei();
}

ISR(INT1_vect)	//vektorn som g?r ig?ng n?r transmit_payload lyckats s?nda eller n?r receive_payload f?tt data OBS: d? Mask_Max_rt ?r satt i config registret s? g?r den inte ig?ng n?r MAX_RT ?r uppn?d ? s?ndninge nmisslyckats!
{
    cli();	//Disable global interrupt
    
    USART_Transmit('1');
    
    SetCELow();
    
    LedBlink(50);
    
    /*
    //Receiver function to print out on usart:
    //data=WriteToNrf(R, R_RX_PAYLOAD, data, dataLen);	//l?s ut mottagen data
    //reset();
    //
    //for (int i=0;i<dataLen;i++)
    //{
    //USART_Transmit(data[i]);
    //}
    //*/

    USART_Transmit('2');
    sei();
}


ISR(USART_RX_vect)	///Vector that triggers when computer sends something to the Atmega88
{
    LedBlink(50);
    
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

void init_led(void)
{
    DDRB |= (1<<PB2); // init PB2 as output for led
    
    LedBlink(500);
}

void INT01_interrupt_init(void)
{
    DDRD &= ~(1<<DDD2);	//Extern interrupt p? INT0, dvs s?tt den till input!
    CLEARBIT(PORTD, 2);
    
    DDRD &= ~(1<<DDD3);	//Extern interrupt p? INT1, dvs s?tt den till input!
    CLEARBIT(PORTD, 3);
            
    MCUCR |= (1<<ISC00);// INT0 raising edge	PD2
    MCUCR |= (1<<ISC01);// INT0 raising edge	PD2

    MCUCR |= (0<<ISC10);// INT1 falling edge	PD3
    MCUCR |= (1<<ISC11);// INT1 falling edge	PD3

    GIMSK |= (1<<INT0);	//enable int0
    GIMSK |= (1<<INT1);	//enable int1
}

int main(void)
{
    init_led();
    _delay_ms(3000);
    
    LedOn();
    _delay_ms(1000);     
    
    USART_Init();
    InitSPI();
    INT01_interrupt_init();      
    
    nrf24L01_init();    
    
    USART_Transmit('0');
    USART_Transmit(GetReg(STATUS));    
    
    LedOff();
    sei();//разрешение прерываний
    
    while(1){}
}


