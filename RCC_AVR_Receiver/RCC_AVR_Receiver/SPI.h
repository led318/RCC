
//����� ���������� SPI � Attiny2313
#define SS    2
#define MOSI  3
#define MISO  4
#define SCK   5

//���� ����������  SPI � Attiny2313
#define SPI_DDR DDRB

// ������� ������������� ������� ���� SPI
void SPI_MasterInit(void)
{
    // ��������� ������� SPI �� �����
    SPI_DDR|=(1<<SS)|(1<<MOSI)|(1<<SCK);
    SPI_DDR&= ~(1<<MISO);

    SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);

    DDRD |= (1<<DDD4); //csn
    DDRB |= (1<<DDB0); //CE
}

/* ������� �������� ����� ������ outData. ������� ���������
�������� � ���������� �������� �� ����� MOSI ���� */
unsigned char SPI_MasterTransmit(char outData)
{
    SPDR = outData;
    
    while(!(SPSR & (1 << SPIF)));
    
    return SPDR;
}