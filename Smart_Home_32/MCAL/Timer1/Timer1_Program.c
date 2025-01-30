
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "Timer1_Interface.h"
#include "Timer1_Private.h"
#include  "Timer1_Config.h"


void (*Ptrf)(void); 

void TIMER1_voidInit(void)
{
	// normal mode ->MODE 0
//	CLR_BIT(TCCR1A,WGM11);
//	CLR_BIT(TCCR1A,WGM10);
//	CLR_BIT(TCCR1B,WGM12);
//	CLR_BIT(TCCR1B,WGM13);

	 // MODE 14
	 SET_BIT(TCCR1A,WGM11);
	 CLR_BIT(TCCR1A,WGM10);
	 SET_BIT(TCCR1B,WGM12);
	 SET_BIT(TCCR1B,WGM13);

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

void TIMER1_voidSetTopValue(u16 Copy_u16TopValue)
{

			ICR1 = Copy_u16TopValue ;
}


void TIMER1_voidServoRotate(u8 Copy_u8Channel ,u8 Copy_u8Angle)
{
	u16 Local_u8Angle =((u16)(Copy_u8Angle*10))+750 ;
	switch(Copy_u8Channel)
				{
				case CHANNELA : OCR1A = Local_u8Angle ;	break;

				case CHANNELB:  OCR1B = Local_u8Angle ;	break;

				}
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



