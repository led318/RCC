/*
* comm_spi.c
*
* Created: 31/01/2016 15:08:26
*  Author: Artem
*/

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>

#include "nRF24L01.h"
#include "pins_actions.h"

#define dataLen 1  //l?ngd p? datapacket som skickas/tas emot
uint8_t *data;
uint8_t *arr;

void SetCELow(void){
    CLEARBIT(PORTB, 3);	//CE l?g
}

void SetCEHigh(void){
    SETBIT(PORTB, 3);	//CE h?g=s?nd data	INT0 interruptet k?rs n?r s?ndningen lyckats och om EN_AA ?r p?, ocks? svaret fr?n recivern ?r mottagen
}

void SetCSNLow(void){
    CLEARBIT(PORTB, 4);	//CSN low - nRF starts to listen for command
}

void SetCSNHigh(void){
    SETBIT(PORTB, 4);	//CSN IR_High
}

void InitSPI(void)
{
    /*
    //Set SCK (PB7), MOSI (PB6), CSN (PB4) & CE (PB3)  as outport
    DDRB |= (1<<PB7) | (1<<PB6) | (1<<PB4) |(1<<PB3);
    
    //Set MOSI (PB5) as input OBS: connects to nRF MISO
    DDRB &= ~(1<<PB5);
    PORTB |= (1<<PB5);
    
    USICR |= (1<< USIWM0) | (1<< USICS1) | (1<<USICLK); //???
    
    SetCSNHigh();
    SetCELow();
    */
    
    DDRB |= (1<<PB6);
    DDRB |= (1<<PB7);
    DDRB |= (1<<PB4);
    DDRB &= ~(1<<PB5);  
    
    PORTB &= ~(1<<PB4);
    
    SetCSNHigh();
    SetCELow();
}

char WriteByteSPI(unsigned char cData)
{  
    //Load byte to Data register
    USIDR = cData;
        
    USISR |= (1<<USIOIF); // clear flag to be able to receive new data
    while(!(USISR & (1<<USIOIF))) // Wait for transmission complete
    {
        USICR |= (1<<USIWM0) | (1<<USICS1) | (1<<USICLK) | (1<<USITC);
    }            
    
    return (USIDR);
}

uint8_t GetReg(uint8_t reg)
{
    _delay_us(10);
    SetCSNLow();
    _delay_us(10);
    WriteByteSPI(R_REGISTER + reg);	//R_Register = set the nRF to reading mode, 'reg' = this registry will be read back
    _delay_us(10);
    reg = WriteByteSPI(NOP);	//Send NOP (dummy byte) once to receive back the first byte in the 'reg' register
    _delay_us(10);
    SetCSNHigh();
    
    return reg;	// Return the read registry
}

/*
void WriteToNrf(uint8_t reg, uint8_t package)
{
_delay_us(10);
SetCSNLow();
_delay_us(10);
WriteByteSPI(W_REGISTER + reg);	//W_Register = set the nRF to write mode, 'reg' = this registry will be written to
_delay_us(10);
WriteByteSPI(package); // send the package to be written to the registry 'reg'
_delay_us(10);
SetCSNHigh();
}
*/

uint8_t *WriteToNrf(uint8_t ReadWrite, uint8_t reg, uint8_t *val, uint8_t antVal)	//tar in "ReadWrite" (W el R), "reg" (ett register), "*val" (en array) & "antVal" (antal integer i variabeln)
{
    //cli();	//disable global interrupt
    
    if (ReadWrite == W)	//if 'W' then you want to write to the nRF ('R' - read)
    {
        reg = W_REGISTER + reg;
    }
    
    //Static uint8_t f?r att det ska g? att returnera en array (l?gg m?rke till "*" uppe p? funktionen!!!)
    static uint8_t ret[32];	//antar att det l?ngsta man vill l?sa ut n?r man kallar p? "R" ?r dataleng-l?ngt, dvs anv?nder man bara 1byte datalengd ? vill l?sa ut 5byte RF_Adress s? skriv 5 h?r ist!!!
    
    _delay_us(10);		//alla delay ?r s? att nrfen ska hinna med! (microsekunder)
    SetCSNLow();
    _delay_us(10);
    WriteByteSPI(reg);	//f?rsta SPI-kommandot efter CSN-l?g ber?ttar f?r nrf'en vilket av dess register som ska redigeras ex: 0b0010 0001 write to registry EN_AA
    _delay_us(10);
    
    int i;
    for(i=0; i<antVal; i++)
    {
        if (ReadWrite == R && reg != W_TX_PAYLOAD)
        {
            ret[i]=WriteByteSPI(NOP);	//Andra och resten av SPI kommandot s?ger ?t nrfen vilka v?rden som i det h?r fallet ska l?sas
            _delay_us(10);
        }
        else
        {
            WriteByteSPI(val[i]);	//Andra och resten av SPI kommandot s?ger ?t nrfen vilka v?rden som i det h?r fallet ska skrivas till
            _delay_us(10);
        }
    }
    
    SetCSNHigh();
    
    //sei(); //enable global interrupt
    
    return ret;	//return an array
}

void nrf24L01_init(void)
{
    _delay_ms(100);	//allow radio to reach power down if shut down
    
    uint8_t val[5];	//en array av integers som skickar v?rden till WriteToNrf-funktionen

    //EN_AA - (auto-acknowledgements) - Transmittern f?r svar av recivern att packetet kommit fram, grymt!!! (beh?ver endast vara enablad p? Transmittern!)
    //Kr?ver att Transmittern ?ven har satt SAMMA RF_Adress p? sin mottagarkanal nedan ex: RX_ADDR_P0 = TX_ADDR
    val[0]=0x01;	//ger f?rsta integern i arrayen "val" ett v?rde: 0x01=EN_AA p? pipe P0.
    WriteToNrf(W, EN_AA, val, 1);	//W=ska skriva/?ndra n?t i nrfen, EN_AA=vilket register ska ?ndras, val=en array med 1 till 32 v?rden  som ska skrivas till registret, 1=antal v?rden som ska l?sas ur "val" arrayen.
    
    //SETUP_RETR (the setup for "EN_AA")
    val[0]=0x2F;	//0b0010 00011 "2" sets it up to 750uS delay between every retry (at least 500us at 250kbps and if payload >5bytes in 1Mbps, and if payload >15byte in 2Mbps) "F" is number of retries (1-15, now 15)
    WriteToNrf(W, SETUP_RETR, val, 1);
    
    //V?ljer vilken/vilka datapipes (0-5) som ska vara ig?ng.
    val[0]=0x01;
    WriteToNrf(W, EN_RXADDR, val, 1); //enable data pipe 0

    //RF_Adress width setup (hur m?nga byte ska RF_Adressen best? av? 1-5 bytes) (5bytes s?krare d? det finns st?rningar men l?ngsammare data?verf?ring) 5addr-32data-5addr-32data....
    val[0]=0x03;
    WriteToNrf(W, SETUP_AW, val, 1); //0b0000 00011 motsvarar 5byte RF_Adress
    
    //RF channel setup - v?ljer frekvens 2,400-2,527GHz 1MHz/steg
    val[0]=0x01;
    WriteToNrf(W, RF_CH, val, 1); //RF channel registry 0b0000 0001 = 2,401GHz (samma p? TX ? RX)

    //RF setup	- v?ljer effekt och ?verf?ringshastighet
    val[0]=0x07;
    WriteToNrf(W, RF_SETUP, val, 1); //00000111 bit 3="0" ger l?gre ?verf?ringshastighet 1Mbps=L?ngre r?ckvidd, bit 2-1 ger effektl?ge h?g (-0dB) ("11"=(-18dB) ger l?gre effekt =str?msn?lare men l?gre range)

    //RX RF_Adress setup 5 byte - v?ljer RF_Adressen p? Recivern (M?ste ges samma RF_Adress om Transmittern har EN_AA p?slaget!!!)
    int i;
    for(i=0; i<5; i++)
    {
        val[i]=0x12;	//RF channel registry 0b10101011 x 5 - skriver samma RF_Adress 5ggr f?r att f? en l?tt och s?ker RF_Adress (samma p? transmitterns chip!!!)
    }
    WriteToNrf(W, RX_ADDR_P0, val, 5); //0b0010 1010 write registry - eftersom vi valde pipe 0 i "EN_RXADDR" ovan, ger vi RF_Adressen till denna pipe. (kan ge olika RF_Adresser till olika pipes och d?rmed lyssna p? olika transmittrar)
    
    //TX RF_Adress setup 5 byte -  v?ljer RF_Adressen p? Transmittern (kan kommenteras bort p? en "ren" Reciver)
    //int i; //?teranv?nder f?reg?ende i...
    for(i=0; i<5; i++)
    {
        val[i]=0x12;	//RF channel registry 0b10111100 x 5 - skriver samma RF_Adress 5ggr f?r att f? en l?tt och s?ker RF_Adress (samma p? Reciverns chip och p? RX-RF_Adressen ovan om EN_AA enablats!!!)
    }
    WriteToNrf(W, TX_ADDR, val, 5);

    // payload width setup - Hur m?nga byte ska skickas per s?ndning? 1-32byte
    val[0]=dataLen;		//"0b0000 0001"=1 byte per 5byte RF_Adress  (kan v?lja upp till "0b00100000"=32byte/5byte RF_Adress) (definierat h?gst uppe i global variabel!)
    WriteToNrf(W, RX_PW_P0, val, 1);
    
    //CONFIG reg setup - Nu ?r allt inst?llt, boota upp nrf'en och g?r den antingen Transmitter lr Reciver
    val[0]=0x1E;  //0b0000 1110 config registry	bit "1":1=power up,  bit "0":0=transmitter (bit "0":1=Reciver) (bit "4":1=>mask_Max_RT,dvs IRQ-vektorn reagerar inte om s?ndningen misslyckades.
    WriteToNrf(W, CONFIG, val, 1);

    //device need 1.5ms to reach standby mode
    _delay_ms(100);

    //sei();
}

//Send data
void transmit_payload(uint8_t * W_buff)
{
    WriteToNrf(R, FLUSH_TX, W_buff, 0); //skickar 0xE1 som flushar registret f?r att gammal data inte ska ligga ? v?nta p? att bli skickad n?r man vill skicka ny data! R st?r f?r att W_REGISTER inte ska l?ggas till. skickar inget kommando efterr?t eftersom det inte beh?vs! W_buff[]st?r bara d?r f?r att en array m?ste finnas d?r...
    
    WriteToNrf(R, W_TX_PAYLOAD, W_buff, dataLen);	//skickar datan i W_buff till nrf-en (obs g?r ej att l?sa w_tx_payload-registret!!!)
    
    //sei();	//enable global interrupt- redan p?!
    //USART_Transmit(GetReg(STATUS));

    _delay_ms(10);		//beh?ver det verkligen vara ms ? inte us??? JAAAAAA! annars funkar det inte!!!
    SetCEHigh();
    _delay_us(20);		//at least 10us!
    SetCELow();
    _delay_ms(10);		//beh?ver det verkligen vara ms ? inte us??? JAAAAAA! annars funkar det inte!!!

    //cli();	//Disable global interrupt... ajabaja, d? st?ngs USART_RX-lyssningen av!
}

/*****************Funktioner***************************/ //Funktioner som anv?nds i main
//Resettar nrf'en f?r ny kommunikation
void reset(void)
{
    _delay_us(10);
    SetCSNLow();
    _delay_us(10);
    WriteByteSPI(W_REGISTER + STATUS);
    _delay_us(10);
    WriteByteSPI(0b01110000);	//radedrar alla irq i statusregistret (f?r att kunna lyssna igen)
    // 0x70
    _delay_us(10);
    SetCSNHigh();
}
