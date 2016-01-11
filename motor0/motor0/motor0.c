#include <avr/io.h>//Подключаем библиотеку ввода/вывода

int L = 0, R = 0, F = 0, B = 0, freq = 25;

void GetCommand(unsigned char data)
{
	switch(data)
	{
		case 'l':
		L = 1;
		R = 0;
		break;
		
		case 'r':
		L = 0;
		R = 1;
		break;
		
		case 'm':
		L = 0;
		R = 0;
		break;
		
		case 'q':
		freq += 1;
		break;
		
		case 'a':
		freq -= 1;
		break;
		
		case 'f':
		F = 1;
		B = 0;
		break;
		
		case 'b':
		F = 0;
		B = 1;
		break;
		
		case 's':
		F = 0;
		B = 0;
		break;
		
		default:
		break;
	}
}

void PerformMotion()
{
	if(F)
	MoveForward();
	else if(B)
	MoveBack();
	else
	MoveStop();
	
	if(L)
	TurnLeft(freq);
	else if(R)
	TurnRight(freq);
	else
	TurnPause(freq);
}

//Главная функция
int main(void)
{
	USART_Init();
	
	DDRB = 0xFF;//Конфигурирование порта на выход
	PORTB = 0x00;//Отключаем подтягивающие резисторы порта
	
	PORTB = 0b00000000;
	
	unsigned char data;
	
	while(1)
	{
		data = USART_Receive();
		
		GetCommand(data);
		   
        PerformMotion();
     		
		if(data != '0')
		{
			USART_Transmit(data);
		}
	}
}
