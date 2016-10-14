/*
���������� ��� ������ � ������������� nRF24L01
�������� nRF24L01_Product_Specification_v2_0.pdf
*/

/* Register Map (��������) ��� 53-58 */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17

/* Bit Mnemonics (���� ���������)*/
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define PLL_LOCK    4
#define RF_DR       3
#define RF_PWR      1
#define LNA_HCURR   0
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0

/* Command ������� (��� 46-47) */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF
#define REGISTER_MASK 0x1F

#include <util/delay.h>
#include <avr/interrupt.h>

#define nrf24l01_CSN_PORT PORTB //����� �SN
#define nrf24l01_CSN_DDR DDRB
#define nrf24l01_CSN_PIN 4

#define nrf24l01_CE_PORT PORTB //����� �E
#define nrf24l01_CE_DDR DDRB
#define nrf24l01_CE_PIN 3

#define nrf24l01_IRQ_PORT PORTD //����� IRQ
#define nrf24l01_IRQ_DDR DDRD
#define nrf24l01_IRQ_PIN 3

// ������ ��� "1" �� ����� ����� (x-����,y-�����)
#define CLEARBIT(x,y) x&=~(1<<y)
// ������ ��� "0" �� ����� ����� (x-����,y-�����)
#define SETBIT(x,y)   x|=1<<y

// ������� ������ ��� ������ ������ CE
#define nrf24l01_CLE_CE CLEARBIT(nrf24l01_CE_PORT,nrf24l01_CE_PIN)
#define nrf24l01_SET_CE SETBIT(nrf24l01_CE_PORT,nrf24l01_CE_PIN)
// ������� ������ ��� ������ ������ CSN
#define nrf24l01_CLE_CSN CLEARBIT(nrf24l01_CSN_PORT,nrf24l01_CSN_PIN)
#define nrf24l01_SET_CSN SETBIT(nrf24l01_CSN_PORT,nrf24l01_CSN_PIN)
// ������� ������ ��� ������ ������ IRQ
#define nrf24l01_CLE_IRQ CLEARBIT(nrf24l01_IRQ_PORT,nrf24l01_IRQ_PIN)
#define nrf24l01_SET_IRQ SETBIT(nrf24l01_IRQ_PORT,nrf24l01_IRQ_PIN)

/* ������� ��������� ������ �������� ��������
-��������� ����� ��������
-���������� �������� � ���� ��������
*/
unsigned char nrf24l01_wr_register (char r_n_reg,unsigned char mask1,unsigned char mask2 )
{
    //char SR=SREG;//��������� �������� ��������
    cli(); //��������� ����������
    unsigned char r_regist=0; //���������� ��� �������� register
    nrf24l01_CLE_CSN;//�������� ����� ��� ������ ��������
    SPI_MasterTransmit(mask1+r_n_reg);//������� ������ ��������
    r_regist=SPI_MasterTransmit(mask2);//������ �������
    nrf24l01_SET_CSN;//�������� �����
    //SREG=SR;
    return r_regist; //���������� �������� ��������
}
//������ ������ �������� ��������
#define nrf24l01_readregister(x) nrf24l01_wr_register(x,R_REGISTER,NOP)
//������ ������ �������� ��������
#define nrf24l01_writeregister(x,y) nrf24l01_wr_register(x,W_REGISTER,y)

//������� ������ ��� ������
unsigned char nrf24l01_command (unsigned char M_ask)
{
    //char SR0=SREG;//��������� �������� ��������
    cli(); //��������� ����������
    unsigned char ST=0;//���������� ��� �������� STATUS
    nrf24l01_CLE_CSN;//�������� ����� ��� ������ ��������        
    
    ST=SPI_MasterTransmit(M_ask);//������ ������� STATUS       
        
    nrf24l01_SET_CSN;//�������� �����
    //SREG=SR0;
    return ST; //���������� �������� STATUS
}
//������ ��������� �������� �������
#define nrf24l01_getstatus nrf24l01_command(NOP)
//������ ������� ����������� �������� �����������
#define nrf24l01_FLUSH_TX nrf24l01_command(FLUSH_TX)
//������ ������� ����������� �������� ���������
#define nrf24l01_FLUSH_RX nrf24l01_command(FLUSH_RX)
//������ ��������� �������� ������������� ������
#define nrf24l01_REUSE_TX_PL nrf24l01_command(REUSE_TX_PL)


/* ������� ��������� ������ ���� ��� � ��������
-��������� ������� � ������� ����� �������� ���
-��� ������� ����� ��������
-�������� �� ������� ����� ��������
*/
void nrf24l01_sc_bit (unsigned char reg_ister,unsigned char register_bit,char W)
{
    unsigned char buf;//���������� ���������� ��������
    buf=nrf24l01_readregister(reg_ister);//������ �������� ��������
    if(W)//���� ����� ���������� ��� � "1"
    buf=buf|(1<<register_bit);//������ ��� � ����������� ��������
    else
    buf=buf&(~(1<<register_bit));//������ ��� � ����������� ��������
    nrf24l01_writeregister(reg_ister,buf);//����� � ������� ����� ��������
}

// ������� ������������� ����� ��������
#define  PTX 0
#define  PRX 1
void nrf24l01_RX_TX_mode (char z)
{
    //��������� � ����� ��������-1 �� ������ ���������
    nrf24l01_CLE_CE;
    //������������� ����� ��������	����� PRIM_RX ���
    nrf24l01_sc_bit(CONFIG,PRIM_RX,z);
    //��������� � ���� �� �������
    nrf24l01_SET_CE;
    _delay_us(15);
    if(!z)  nrf24l01_CLE_CE;
    _delay_us(140);//�������� �� ������� (10+140)
}

//���������� �����
void nrf24l01_write_data (unsigned char data)
{
    nrf24l01_CLE_CSN;//�������� ����� ��� ������ ��������
    SPI_MasterTransmit(W_TX_PAYLOAD);//������� ������
    SPI_MasterTransmit(data);
    nrf24l01_SET_CSN;//�������� �����
    //���������� ���������� ���� ��� ���������
}

//���������� ������ � ������ �����������
void nrf24l01_Sent_data_Ret (unsigned char data)
{
    nrf24l01_write_data(data);//���������� ����� � ����� �����������
    nrf24l01_RX_TX_mode(PTX);//���� ������� �� �������� ���� ����� �� ��������
    nrf24l01_RX_TX_mode(PRX);//����� �������� ������������ � ����� ���������
}

//������ ������
unsigned char nrf24l01_read_data (void)
{
    unsigned char i;
    nrf24l01_CLE_CSN;//�������� ����� ��� ������ ��������
    SPI_MasterTransmit(R_RX_PAYLOAD);//������� ������
    i=SPI_MasterTransmit(NOP);
    nrf24l01_SET_CSN;//�������� �����
    return i;
}

//(�������������) ������� ������ ��������-1
void nRF24L01_init (unsigned char m)
{
    //������������� ����� CSN �� �����
    SETBIT(nrf24l01_CSN_DDR,nrf24l01_CSN_PIN);
    //������������� ����� CE �� �����
    SETBIT(nrf24l01_CE_DDR,nrf24l01_CE_PIN);
    //������������� ����� IRG �� ����
    CLEARBIT(nrf24l01_IRQ_DDR,nrf24l01_IRQ_PIN);
    //������������� ����� IRG 5v
    //SETBIT(nrf24l01_IRQ_PORT,nrf24l01_IRQ_PIN);
    
    nrf24l01_CLE_CSN;//���� �� �����
    nrf24l01_CLE_CE;//���� �� �����
    _delay_ms(15);//����� �� ������������� (�������� ����� ������ �������)
    
    /*
    ���������� �� ���� ��������� ������� � EN_AA
    � �������������� ��������� �������� ���� ��������� ����� ������ ���� ���
    
    1) ��������� ��������������� �������  �������� �� ���������    EN_AA
    2) ��������� ������� ������                                    EN_RXADDR
    3) ����� ����� ������                                          SETUP_AW
    4) ��������� ������������ ������                               SETUP_RETR
    5) ��������� �������                                           RF_CH
    6) ���������� �������� �������� + �������� ���������           RF_SETUP
    7) ������� ������� (�� �������������)                          STATUS
    8) ������� ���������� ��������� ������� ������                 OBSERVE_TX
    9) ������� ������������ ��� ������� �������                    CD
    10) �������� �������� ������� �� ����� ������                  RX_ADDR_P(0-5)
    11) ������� ��� �������� ������ �� ��������                    TX_ADDR
    12) �������� ��������� �������� �������� ��� ������� ������    RX_PW_P(0-5)
    13) ������� ������� ������� ��������� � �����������            FIFO_STATUS
    */
    //12-�� ����� ��������� � ���������
    nrf24l01_sc_bit(RX_PW_P0,0,1);// ������������� 8��� �������� ��������
    
    //���������� ���������� (���/���������) �� 3-� �� ��������� �������� ���!
    nrf24l01_sc_bit(CONFIG,MASK_MAX_RT,m&0b00000001);
    nrf24l01_sc_bit(CONFIG,MASK_TX_DS,m&0b00000010);
    nrf24l01_sc_bit(CONFIG,MASK_RX_DR,m&0b00000100);
    
    // nrf24l01_sc_bit(CONFIG,PRIM_RX,1);//������������� ����� ��������
    nrf24l01_sc_bit(CONFIG,PWR_UP,1);//������������� ��� ��� � ������� (�������� ������)
    _delay_ms(2);//�������� �� ���������
    
    //������ �� � ������ ��������-1
}
