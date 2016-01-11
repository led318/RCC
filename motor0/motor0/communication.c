#include <avr/io.h>

#define RXEN 4
#define TXEN 3
#define USBS 3
#define UCSZ0 1

void USART_Init(void)
{
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
}


unsigned char USART_Receive(void) //Функция приема данных
{
    //while (!(UCSRA & (1<<RXC))); //Ожидание приема символа
    //return UDR; //Возврат содержимого буфера приема символа
    
    if(UCSRA & (1<<RXC))
    {
        return UDR;
    } else {
        return '0';
    }
}

void USART_Transmit(unsigned char data) //Функция отправки данных
{
    while (!(UCSRA & (1<<UDRE)) ); //Ожидание опустошения буфера приема
    {
        UDR = data; //Начало передачи данных
    }
}

void USART_TransmitString(char* string)
{
    while (*string)
    {
        USART_Transmit(*string++);
    }
}