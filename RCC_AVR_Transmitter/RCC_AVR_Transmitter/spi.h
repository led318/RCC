
//ножки интерфейса SPI в Attiny2313
#define SS    4
#define MOSI  5
#define MISO  6
#define SCK   7

//порт интерфейса  SPI в Attiny2313
#define SPI_DDR DDRB

// Функция инициализации мастера шины SPI
void SPI_MasterInit(void)
{
    // Установка выводов SPI на вывод
    SPI_DDR|=(1<<SS)|(1<<MISO)|(1<<SCK);
    SPI_DDR&= ~(1<<MOSI);    
}

/* Функция передачи байта данных outData. Ожидает окончания
передачи и возвращает принятый по ножке MOSI байт */
unsigned char SPI_MasterTransmit(char outData)
{
    USIDR = outData;// Начало передачи
           
    USISR |= (1<<USIOIF); // clear flag to be able to receive new data
    while(!(USISR & (1<<USIOIF))) // Wait for transmission complete
    {
        USICR |= (1<<USIWM0) | (1<<USICS1) | (1<<USICLK) | (1<<USITC);
    }
    
    return (USIDR); //возвращаем принятый байт
}