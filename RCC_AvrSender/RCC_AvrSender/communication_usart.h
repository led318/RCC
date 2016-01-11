/* 
* communication_usart.h
*
* Created: 11/01/2016 21:09:37
* Author: Artem
*/


#ifndef __COMMUNICATION_USART_H__
#define __COMMUNICATION_USART_H__


class communication_usart
{
//variables
public:
protected:
private:

//functions
public:
	communication_usart();
	~communication_usart();
    static void USART_Init();
    static char USART_Receive();
    static void USART_Transmit(char data);
    static void USART_TransmitString(char* string);
protected:
private:
	communication_usart( const communication_usart &c );
	communication_usart& operator=( const communication_usart &c );
}; //communication_usart

#endif //__COMMUNICATION_USART_H__
