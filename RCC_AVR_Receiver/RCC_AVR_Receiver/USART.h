/*
* comm_usart.c
*
* Created: 31/01/2016 14:06:38
*  Author: Artem
*/

#include <stdio.h>
#include <avr/io.h>

void USART_Init()
{
    UBRR0H = 0x00; //MYUBRR >> 8;    
    UBRR0L = 0x0B; //MYUBRR;
    UCSR0B = ((1<<RXEN0)|(1<<TXEN0) | (1<<RXCIE0));    
}


char USART_Receive() //Функция приема данных
{
    while(!(UCSR0A & (1<<RXC0))); //Ожидание приема символа    
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
