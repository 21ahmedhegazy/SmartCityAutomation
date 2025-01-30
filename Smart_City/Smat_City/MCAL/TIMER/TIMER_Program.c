/*********************************************************/
/* File      : TIMER_Program.c                           */
/* Author    : Ahmed Hegazy                              */
/* Version   : V1.0                                      */
/*********************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMER_Config.h"
#include "TIMER_Interface.h"
#include "TIMER_Private.h"


void (*Ptrf)(void); 

void TIMER1_voidInit(void)
{

	 // MODE 14
	 SET_BIT(TCCR1A,WGM11);
	 CLR_BIT(TCCR1A,WGM10);
	 SET_BIT(TCCR1B,WGM12);
	 SET_BIT(TCCR1B,WGM13);

}
void TMR0_voidInit(void)
{
    // Configure Timer0 for Fast PWM mode
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM0); // Set WGM00 for Fast PWM
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM1); // Set WGM01 for Fast PWM

    // Set initial non-inverted mode for OC0
    SET_BIT(TIMER0_TCCR0, TCCR0_COM1); // Set COM01 to 1
    CLR_BIT(TIMER0_TCCR0, TCCR0_COM0); // Clear COM00 to 0
}

void TMR2_voidInit(void) {
    // Set Timer 2 to Fast PWM mode
    SET_BIT(TCCR2, WGM20);
    SET_BIT(TCCR2, WGM21);
    // Non-inverted mode
    SET_BIT(TCCR2, COM21);
    CLR_BIT(TCCR2, COM20);
}


void TMR0_voidFastPWMNonInverted(u8 Copy_u8Prescaler)
{
    // Configure Timer0 for Fast PWM mode
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM0); // Set WGM00 for Fast PWM
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM1); // Set WGM01 for Fast PWM

    // Set non-inverted mode
    SET_BIT(TIMER0_TCCR0, TCCR0_COM1); // Set COM01 to 1
    CLR_BIT(TIMER0_TCCR0, TCCR0_COM0); // Clear COM00 to 0

    // Apply prescaler by masking the clock bits and setting the desired value
    TIMER0_TCCR0 &= ~((1 << TCCR0_CS2) | (1 << TCCR0_CS1) | (1 << TCCR0_CS0)); // Clear prescaler bits
    TIMER0_TCCR0 |= Copy_u8Prescaler; // Set the desired prescaler
}
void TMR2_voidFastPWMNonInverted(u8 Copy_u8Prescaler)
{
    // Configure Timer2 for Fast PWM mode
    SET_BIT(TCCR2, WGM20); // Set WGM20 for Fast PWM
    SET_BIT(TCCR2, WGM21); // Set WGM21 for Fast PWM

    // Set non-inverted mode
    SET_BIT(TCCR2, COM21); // Set COM21 to 1
    CLR_BIT(TCCR2, COM20); // Clear COM20 to 0

    // Apply prescaler by masking the clock bits and setting the desired value
    TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Clear prescaler bits
    TCCR2 |= Copy_u8Prescaler; // Set the desired prescaler
}

void TMR0_voidSetDutyCycle(u8 dutyCycle)
{
    // Set duty cycle for Timer 0 (Servo 1)
    TIMER0_OCR0 = dutyCycle;
}



void TMR2_voidSetDutyCycle(u8 dutyCycle) {
    // Set duty cycle for Timer 2 (Servo 2)
    TIMER2_OCR2 = dutyCycle;
}
void TIMER1_voidFastPWMNonIntvered(u8 Copy_u8Channel , u8 Copy_u8Prescaler)
{
				switch(Copy_u8Channel)
				{
				case CHANNELA :
					SET_BIT(TCCR1A ,COM1A1);
					CLR_BIT(TCCR1A ,COM1A0);
					break;

				case CHANNELB:
					SET_BIT(TCCR1A ,COM1B1);
					CLR_BIT(TCCR1A ,COM1B0);
					break;
				}


				//Run timer with target prescaler

				TCCR1B &= CLK_MASK ;
				TCCR1B |=Copy_u8Prescaler ;
}


void TIMER1_voidSetDutyCycle(u8 Copy_u8Channel ,u16 Copy_u16DutyCycle)
{

	switch(Copy_u8Channel)
			{
			case CHANNELA : OCR1A = Copy_u16DutyCycle ;	break;

			case CHANNELB:  OCR1B = Copy_u16DutyCycle ;	break;

			}

}

void TMR0_voidSetTopValue(u8 Copy_u8TopValue)
{
    // Set the top value for Timer0
    TIMER0_OCR0 = Copy_u8TopValue;
}

void TIMER1_voidSetTopValue(u16 Copy_u16TopValue)
{

			ICR1 = Copy_u16TopValue ;
}

void TMR2_voidSetTopValue(u8 Copy_u8TopValue)
{
    // Set the top value for Timer2
    TIMER2_OCR2 = Copy_u8TopValue;
}


void TIMER1_voidNormalMode(u8 Copy_u8Prescaler)
{
	//Run timer with target prescaler

	TCCR1B &= CLK_MASK ;
	TCCR1B |=Copy_u8Prescaler ;
}

void TIMER1_voidResetTimer(void)
{
 TCNT1 = 0 ;
}

u16  TIMER1_u16GetElapsedTimer(void)
{

	return TCNT1 ;
}
void TIMER1_voidStopTimer1(void)
{
	//Run timer with target prescaler

	TCCR1B &= CLK_MASK ;
	TCCR1B |=PRESCALAR_NO_CLOCK ;
}













void ICU_CallBackFun(void (*ptr)(void))
{
	Ptrf=ptr;
	
}

u16 ICU_u16ReadInputCapture (void)
{
	return ICR1;
}

void __vector_6(void) __attribute__((signal)); 
void __vector_6(void)
{
	
	Ptrf();
	
} 



