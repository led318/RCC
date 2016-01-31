/*
 * pins_actions.h
 *
 * Created: 31/01/2016 19:10:59
 *  Author: Artem
 */ 

//region Outputs
/*
#define wB0(x)  (PORTB = (PORTB & ~_BV(PB0)) | ((x) << PB0))
#define wB1(x)  (PORTB = (PORTB & ~_BV(PB1)) | ((x) << PB1))
#define wB2(x)  (PORTB = (PORTB & ~_BV(PB2)) | ((x) << PB2))
#define wB3(x)  (PORTB = (PORTB & ~_BV(PB3)) | ((x) << PB3))
#define wB4(x)  (PORTB = (PORTB & ~_BV(PB4)) | ((x) << PB4))
#define wB5(x)  (PORTB = (PORTB & ~_BV(PB5)) | ((x) << PB5))
#define wB6(x)  (PORTB = (PORTB & ~_BV(PB6)) | ((x) << PB6))
#define wB7(x)  (PORTB = (PORTB & ~_BV(PB7)) | ((x) << PB7))
*/
//endregion

//region Inputs
/*
#define b1()    ((PINA & _BV(PA4)) >> PA4)
#define b2()    ((PINA & _BV(PA7)) >> PA7)
#define b3()    ((PINC & _BV(PC5)) >> PC5)
#define b4()    ((PINA & _BV(PA5)) >> PA5)
#define b5()    ((PINC & _BV(PC7)) >> PC7)
#define b6()    ((PINC & _BV(PC4)) >> PC4)
#define b7()    ((PINA & _BV(PA6)) >> PA6)
#define b8()    ((PINC & _BV(PC6)) >> PC6)
#define b9()    ((PINC & _BV(PC3)) >> PC3)
*/
//endregion