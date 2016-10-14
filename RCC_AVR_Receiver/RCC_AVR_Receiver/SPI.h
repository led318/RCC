
//ножки интерфейса SPI в Attiny2313
#define SS    2
#define MOSI  3
#define MISO  4
#define SCK   5

//порт интерфейса  SPI в Attiny2313
#define SPI_DDR DDRB

// Функция инициализации мастера шины SPI
void SPI_MasterInit(void)
{
    // Установка выводов SPI на вывод
    SPI_DDR|=(1<<SS)|(1<<MOSI)|(1<<SCK);
    SPI_DDR&= ~(1<<MISO);

    SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    DDRD |= (1<<DDD4); //csn
    DDRB |= (1<<DDB0); //CE
}

/* Функция передачи байта данных outData. Ожидает окончания
передачи и возвращает принятый по ножке MOSI байт */
unsigned char SPI_MasterTransmit(char outData)
{
    SPDR = outData;
    
    while(!(SPSR & (1 << SPIF)));
    
    return SPDR;
}