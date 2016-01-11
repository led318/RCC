/*
* RCC_AvrSender.cpp
*
* Created: 11/01/2016 21:08:06
* Author : Artem
*/

#include "communication_usart.h"
#include <avr/io.h>

int main(void)
{
    communication_usart::USART_Init();
    
    DDRB = 0xFF; //���������������� ����� �� �����
    PORTB = 0x00; //��������� ������������� ��������� �����
    
    PORTB = 0b00000000;
    
    char data;
    
    while (true)
    {
        data = communication_usart::USART_Receive();
        
        if(data != '0')
        {
            communication_usart::USART_Transmit(data);
        }
    }
}

