/*
* RCC_AVR_Receiver.c
*
* Created: 02/02/2016 21:35:52
* Author : Artem
*/

#define F_CPU 3686400UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include "USART.h"
#include "nRF24L01.h"
#include "pins_actions.h"
#include "SERVO.h"
#include "ENGINE.h"

#define turn_direction_mask 0x1f
#define turn_direction_bit 0x04
#define turn_power_mask 0x0f

#define engine_subcommand_bit0 0x05
#define engine_subcommand_bit1 0x06
#define engine_subcommand_bit2 0x07
#define engine_direction_bit 0x02
#define engine_power_mask 0x03

unsigned char data;

int get_engine_subcommand(int command){
    int bit0 = (command >> engine_subcommand_bit0) & 1;
    int bit1 = (command >> engine_subcommand_bit1) & 1;
    int bit2 = (command >> engine_subcommand_bit2) & 1;    
    
    int subcommand = 0;
    subcommand |= bit0 << 0;
    subcommand |= bit1 << 1;
    subcommand |= bit2 << 2;
    
    return subcommand;
}

void process_command(int command){
    int turn_subcommand = command & turn_direction_mask;// command &  //turn_bits_mask;    
    
    int turn_direction = (turn_subcommand >> turn_direction_bit) & 1;
    int turn_power = turn_subcommand & turn_power_mask;

    SERVO_turn_int(turn_direction, turn_power);    
    
    int engine_subcommand = get_engine_subcommand(command);
    int engine_direction = (engine_subcommand >> engine_direction_bit) & 1;
    int engine_power = engine_subcommand & engine_power_mask;
    
    ENGINE_set_int(engine_direction, engine_power);
    //ENGINE_set_int(turn_direction, turn_power);
    
    //USART_Transmit(engine_direction);
    //USART_Transmit(engine_power);
    //USART_Transmit(turn_power);
}

ISR(INT0_vect)	//vektorn som g?r ig?ng n?r transmit_payload lyckats s?nda eller n?r receive_payload f?tt data OBS: d? Mask_Max_rt ?r satt i config registret s? g?r den inte ig?ng n?r MAX_RT ?r uppn?d ? s?ndninge nmisslyckats!
{
    cli();
    
    LedBlink(5);

    data=nrf24l01_getstatus;
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

ISR(USART_RX_vect)	///Vector that triggers when computer sends something to the Atmega88
{
    cli();    
    
    data=USART_Receive();	//receive the USART
	
	process_command(data);
	
    //USART_Transmit(data);	//Transmit the Data back to the computer to make sure it was correctly received

    //nrf24l01_Sent_data_Ret(data);	//send data to nrf

    //USART_Transmit(nrf24l01_getstatus);
    //USART_Transmit('#');	//visar att chipet mottagit datan...
    
    sei();
}

void init_interrupt(void){
    DDRD &= ~(1<<DDD2);	//Extern interrupt p? INT0, dvs s?tt den till input!
    CLEARBIT(PORTD, 2);
    
    MCUCR |= (1<<ISC01);// INT0 falling edge	PD2
    MCUCR &= ~(1<<ISC00);// INT0 falling edge	PD2

    EIMSK |= (1<<INT0);	//enable int1

    EIFR=0b01000000;
}

int main(void)
{
    USART_Init();
    USART_Transmit('0');
    
    init_led();
    _delay_ms(3000);
    
    LedOn();
    _delay_ms(1000);
    
    //USART_Init();
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
	
	SERVO_init();	
	ENGINE_init();
    
    sei();//разрешение прерываний

    while(1){}
}



