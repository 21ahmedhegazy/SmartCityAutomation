/*********************************************************/
/* Component : EXTI                                      */
/* File      : EXTI_program.c                           */
/* Author    : Hegazy                                     */
/* Date      : 17 . 7 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


void (*CallbackFuncINT0) (void) = NULL ;
void (*CallbackFuncINT1) (void) = NULL ;
void (*CallbackFuncINT2) (void) = NULL ;

void EXTI_voidEnableInterrupt(u8 Copy_u8InterruptId)
{
	//switching over interrupt sources
	switch(Copy_u8InterruptId)
	{
		case EXTI_INT0 :
				SET_BIT(EXTI_GICR , GICR_INT0) ; break ;

		case EXTI_INT1 :
				SET_BIT(EXTI_GICR , GICR_INT1) ; break ;

		case EXTI_INT2 :
				SET_BIT(EXTI_GICR , GICR_INT2) ; break ;
	}
}

void EXTI_voidDisableInterrupt(u8 Copy_u8InterruptId)
{
	//switching over interrupt sources
	switch(Copy_u8InterruptId)
	{
		case EXTI_INT0 :
				CLR_BIT(EXTI_GICR , GICR_INT0) ; break ;

		case EXTI_INT1 :
				CLR_BIT(EXTI_GICR , GICR_INT1) ; break ;

		case EXTI_INT2 :
				CLR_BIT(EXTI_GICR , GICR_INT2) ; break ;
	}
}

void EXTI_voidSetSenseSignalINT0(u8 Copy_u8INT0SenseSignal)
{
	//switch over available sense signals for interrupt 0
	switch(Copy_u8INT0SenseSignal)
	{
		case EXTI_INT0_FALLING_EDGE :
			SET_BIT(EXTI_MCUCR , MCUCR_ISC01) ;
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC00) ;
			 break ;

		case EXTI_INT0_RISING_EDGE :
			SET_BIT(EXTI_MCUCR , MCUCR_ISC01) ;
			SET_BIT(EXTI_MCUCR , MCUCR_ISC00) ;
			break ;

		case EXTI_INT0_LOW_LEVEL :
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC01) ;
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC00) ;
			break ;

		case EXTI_INT0_ON_CHANGE :
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC01) ;
			SET_BIT(EXTI_MCUCR , MCUCR_ISC00) ;
			break ;
	}
}

void EXTI_voidSetSenseSignalINT1(u8 Copy_u8INT1SenseSignal)
{
	//switch over available sense signals for interrupt 0
	switch(Copy_u8INT1SenseSignal)
	{
		case EXTI_INT1_FALLING_EDGE :
			SET_BIT(EXTI_MCUCR , MCUCR_ISC11) ;
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC10) ;
			 break ;

		case EXTI_INT1_RISING_EDGE :
			SET_BIT(EXTI_MCUCR , MCUCR_ISC11) ;
			SET_BIT(EXTI_MCUCR , MCUCR_ISC10) ;
			break ;

		case EXTI_INT1_LOW_LEVEL :
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC11) ;
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC10) ;
			break ;

		case EXTI_INT1_ON_CHANGE :
			CLR_BIT(EXTI_MCUCR , MCUCR_ISC11) ;
			SET_BIT(EXTI_MCUCR , MCUCR_ISC10) ;
			break ;
	}
}

void EXTI_voidSetSenseSignalINT2(u8 Copy_u8INT2SenseSignal)
{
	//switch over available sense signals for interrupt 0
	switch(Copy_u8INT2SenseSignal)
	{
		case EXTI_INT2_FALLING_EDGE :
			CLR_BIT(EXTI_MCUCSR , MCUCSR_ISC2) ;
			 break ;

		case EXTI_INT2_RISING_EDGE :
			SET_BIT(EXTI_MCUCSR , MCUCSR_ISC2) ;
			break ;
	}


}

void EXTI_voidControlGlobalInterrupt(u8 Copy_u8State)
{
	//Write 0 or 1 to the bit depending on input state
	switch(Copy_u8State)
		{
			case GIE_DISABLED :
				CLR_BIT(GIE_SREG , SREG_I) ;
				 break ;

			case GIE_ENABLED :
				SET_BIT(GIE_SREG , SREG_I) ;
				break ;
		}


}

void EXTI_voidSetCallbackINT0(void (*Copy_voidFuncptr) (void))
{
	CallbackFuncINT0 = Copy_voidFuncptr ;
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
  if (CallbackFuncINT0 != NULL)
  {
	  CallbackFuncINT0();
  }
}

void EXTI_voidSetCallbackINT1(void (*Copy_voidFuncptr) (void))
{
	CallbackFuncINT1 = Copy_voidFuncptr ;
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
  if (CallbackFuncINT1 != NULL)
  {
	  CallbackFuncINT1();
  }
}
void EXTI_voidSetCallbackINT2(void (*Copy_voidFuncptr) (void))
{
	CallbackFuncINT2 = Copy_voidFuncptr ;
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
  if (CallbackFuncINT2 != NULL)
  {
	  CallbackFuncINT2();
  }
}


