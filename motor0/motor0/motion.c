#include <avr/io.h>

//region Outputs
#define wB0(x)  (PORTB = (PORTB & ~_BV(PB0)) | ((x) << PB0))
#define wB1(x)  (PORTB = (PORTB & ~_BV(PB1)) | ((x) << PB1))
#define wB2(x)  (PORTB = (PORTB & ~_BV(PB2)) | ((x) << PB2))
#define wB3(x)  (PORTB = (PORTB & ~_BV(PB3)) | ((x) << PB3))
#define wB4(x)  (PORTB = (PORTB & ~_BV(PB4)) | ((x) << PB4))
#define wB5(x)  (PORTB = (PORTB & ~_BV(PB5)) | ((x) << PB5))
#define wB6(x)  (PORTB = (PORTB & ~_BV(PB6)) | ((x) << PB6))
#define wB7(x)  (PORTB = (PORTB & ~_BV(PB7)) | ((x) << PB7))
//endregion

#define nop() {asm("nop");}//подключаем функция для формирваония задержки
int x, j, m=100, f = 20; //переменные

//Функция задержки
void delay(int t)
{
    for (x=0; x<t ;x++)
    {
        nop ();
    }
}

//Функция длинной задержки
void long_delay(int p)
{
    for (j=0; j<p; j++)
    {
        delay(f);
    }
}

//Функция поворота ротора вправо
void TurnLeft (int newF)
{
    f = newF;
    
    /* half step mode */
    
    //PORTB = 0b00001000;
    wB0(0);
    wB1(0);
    wB2(0);
    wB3(1);
    long_delay(m);
    
    //PORTB = 0b00001100;
    wB0(0);
    wB1(0);
    wB2(1);
    wB3(1);
    long_delay(m);
    
    //PORTB = 0b00000100;
    wB0(0);
    wB1(0);
    wB2(1);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000110;
    wB0(0);
    wB1(1);
    wB2(1);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000010;
    wB0(0);
    wB1(1);
    wB2(0);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000011;
    wB0(1);
    wB1(1);
    wB2(0);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000001;
    wB0(1);
    wB1(0);
    wB2(0);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00001001;
    wB0(1);
    wB1(0);
    wB2(0);
    wB3(1);
    long_delay(m);
    /* end */
}

//Функция поворота ротора влево
void TurnRight(int newF)
{
    f = newF;
    
    /* half step mode */
    
    //PORTB = 0b00000001;
    wB0(1);
    wB1(0);
    wB2(0);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000011;
    wB0(1);
    wB1(1);
    wB2(0);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000010;
    wB0(0);
    wB1(1);
    wB2(0);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000110;
    wB0(0);
    wB1(1);
    wB2(1);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00000100;
    wB0(0);
    wB1(0);
    wB2(1);
    wB3(0);
    long_delay(m);
    
    //PORTB = 0b00001100;
    wB0(0);
    wB1(0);
    wB2(1);
    wB3(1);
    long_delay(m);
    
    //PORTB = 0b00001000;
    wB0(0);
    wB1(0);
    wB2(0);
    wB3(1);
    long_delay(m);
    
    //PORTB = 0b00001001;
    wB0(1);
    wB1(0);
    wB2(0);
    wB3(1);
    long_delay(m);
    /* end */
}

void TurnPause(int newF)
{
    f = newF;
    
    //PORTB = 0b00000000;
    wB0(0);
    wB1(0);
    wB2(0);
    wB3(0);

    long_delay(m);
}

void MoveForward()
{
    wB4(1);
    wB5(1);
    wB6(0);
    wB7(0);
}

void MoveBack()
{
    wB4(0);
    wB5(0);
    wB6(1);
    wB7(1);
}

void MoveStop()
{
    wB4(0);
    wB5(0);
    wB6(0);
    wB7(0);
}