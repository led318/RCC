/*
* RCC_AVR_Transmitter.c
*
* Created: 31/01/2016 14:04:18
* Author : Artem
*/

#define F_CPU 8000000UL  // 8 MHz

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "SPI.h"
#include "nRF24L01.h"
#include "pins_actions.h"

unsigned char data;

ISR(INT0_vect)
{
    cli();	//Disable global interrupt

    LedBlink(5);  
    
    data = '4';    
    
    USART_Transmit(data);
    
    nrf24l01_Sent_data_Ret(data);
    
    USART_Transmit(nrf24l01_getstatus);

    sei();
}

ISR(INT1_vect)	//vektorn som g?r ig?ng n?r transmit_payload lyckats s?nda eller n?r receive_payload f?tt data OBS: d? Mask_Max_rt ?r satt i config registret s? g?r den inte ig?ng n?r MAX_RT ?r uppn?d ? s?ndninge nmisslyckats!
{
    cli();
    
    data=nrf24l01_getstatus;
    USART_Transmit(data);
    if(data&0b01000000)
    {
        //отправляем принятые данные через UART
        USART_Transmit(nrf24l01_read_data());
        //сбрасываем прерывание по приему пакета
        nrf24l01_sc_bit(STATUS,RX_DR,1);
    }
    
    _delay_us(10);
    
    sei();
}

ISR(USART_RX_vect)	///Vector that triggers when computer sends something to the controller
{
    cli();
    
    data=USART_Receive();	//receive the USART
    USART_Transmit(data);	//Transmit the Data back to the computer to make sure it was correctly received

    nrf24l01_Sent_data_Ret(data);	//send data to nrf

    USART_Transmit(nrf24l01_getstatus);
    USART_Transmit('#');	//visar att chipet mottagit datan...
    
    sei();
}

void init_interrupt(void)
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
    USART_Init();    
    USART_Transmit('0');    
    
    init_led();
    _delay_ms(3000);
    
    LedOn();
    _delay_ms(1000);
    
    SPI_MasterInit();//инициализация SPI
    nRF24L01_init(0b00000011);//инициализация модуля
    init_interrupt();
    nrf24l01_RX_TX_mode(PRX);//переходим в режим приемника
    
    USART_Transmit('1');
    USART_Transmit(nrf24l01_getstatus);
    
    USART_Transmit(nrf24l01_readregister(EN_AA));
    USART_Transmit(nrf24l01_readregister(EN_RXADDR));
    USART_Transmit(nrf24l01_readregister(SETUP_AW));
    USART_Transmit(nrf24l01_readregister(SETUP_RETR));
    USART_Transmit(nrf24l01_readregister(RF_CH));
    USART_Transmit(nrf24l01_readregister(RF_SETUP));
    USART_Transmit(nrf24l01_readregister(STATUS));
    USART_Transmit(nrf24l01_readregister(OBSERVE_TX));
    USART_Transmit(nrf24l01_readregister(CD));
    USART_Transmit(nrf24l01_readregister(RX_ADDR_P0));
    USART_Transmit(nrf24l01_readregister(TX_ADDR));
    USART_Transmit(nrf24l01_readregister(RX_PW_P0));
    USART_Transmit(nrf24l01_readregister(FIFO_STATUS));    
    
    LedOff();
    sei();//разрешение прерываний
    
    while(1){}
}


