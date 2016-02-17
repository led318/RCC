/*
* comm_usart.c
*
* Created: 31/01/2016 14:06:38
*  Author: Artem
*/

#include <stdio.h>
#include <avr/io.h>

#define RXEN 4
#define TXEN 3
#define USBS 3
#define UCSZ0 1

//#define FOSC 8000000
//#define BAUD 1200
//#define MYUBRR FOSC/16/BAUD-1

void USART_Init()
{
    /*
    UCSRB = 0x00; //disable while setting baud rate
    UCSRA = 0x00; //Bit1–U2X=0: Double the USART transmission speed
    //Bit2–PE=0: Parity Error-Disabled
    UCSRC = 0x06; //UCSZ0=1,UCSZ1=1, UCSZ2=0 => Charcter Size=8bit
    //UBRRL = 0x33; //set baud rate lo
    UBRRL = 0x19; //set baud rate lo
    UBRRH = 0x00; //set baud rate hi; UBRR=0x0033=51;=> BAUD=Fclk/(16*(UBRR+1))=9615 (при U2X=0)
    UCSRB = 0x98; //1001 1000: bit7-enable RX Complete Interrupt;
    //	bit4-Receiver enable
    //	bit3-Transmit enable
    */
    
    UBRR0H = 0x00; //MYUBRR >> 8;    
    UBRR0L = 0xBF; //MYUBRR;
    UCSR0B = ((1<<RXEN0)|(1<<TXEN0) | (1<<RXCIE0));    
}


char USART_Receive() //Функция приема данных
{
    while( !(UCSR0A & (1<<RXC0)) ); //Ожидание приема символа
    
    return(UDR0); //Возврат содержимого буфера приема символа
}

void USART_Transmit(char data) //Функция отправки данных
{
    while ( !( UCSR0A & (1<<UDRE0)) ); // Ждем,если предыдущий символ не передался.
    {
        UDR0 = data;
    }        
}

void USART_TransmitString(char* string)
{
    while (*string)
    {
        USART_Transmit(*string++);
    }
}
