/*
 * RCC_AVR_Transmitter.c
 *
 * Created: 31/01/2016 14:04:18
 * Author : Artem
 */ 

#include <avr/io.h>

int main(void)
{
    USART_Init();
    
    DDRB = 0xFF; //Конфигурирование порта на выход
    PORTB = 0x00; //Отключаем подтягивающие резисторы порта
    
    PORTB = 0b00000000;
    
    char data;
    
    while (1)
    {
        data = USART_Receive();
        
        if(data != '0')
        {
            USART_Transmit(data);
        }
    }
}
