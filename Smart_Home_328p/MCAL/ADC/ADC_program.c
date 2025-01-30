/*********************************************************/
/* Component : ADC                                      */
/* File      : ADC_program.c                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Maths.h"

#include "ADC_interface.h"
#include "ADC_private.h"

// Global pointers for callback and reading
void (*Global_ptrToFunction)(void) = NULL_PTR;
u8 *Global_ptrToReading = NULL_PTR;

// ADC Initialization
void ADC_voidInit(void)
{
    // Set AVcc as reference voltage
    CLR_BIT(ADMUX, ADMUX_REFS1);
    SET_BIT(ADMUX, ADMUX_REFS0);

    // Left adjustment for 8-bit resolution
    SET_BIT(ADMUX, ADMUX_ADLAR);

    // Set ADC prescaler to 128 (ADPS2:0 = 111)
    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);

    // Enable ADC
    SET_BIT(ADCSRA, ADCSRA_ADEN);
}

// Synchronous ADC Conversion
u8 ADC_u8StartConversionSync(u8 Copy_u8ChannelID)
{
    // Set target channel (clear previous selection)
    ADMUX &= CHANNEL_MASK;
    ADMUX |= Copy_u8ChannelID;

    // Start conversion
    SET_BIT(ADCSRA, ADCSRA_ADSC);

    // Wait for conversion to complete
    while (GET_BIT(ADCSRA, ADCSRA_ADIF) == 0);

    // Clear interrupt flag
    SET_BIT(ADCSRA, ADCSRA_ADIF);

    // Return the 8-bit result
    return ADCH;
}

// Asynchronous ADC Conversion
void ADC_voidStartConversionAsync(u8 Copy_u8ChannelID, u8 *Copy_u16DigitalReading)
{
    // Set target channel (clear previous selection)
    ADMUX &= CHANNEL_MASK;
    ADMUX |= Copy_u8ChannelID;

    // Enable ADC interrupt
    SET_BIT(ADCSRA, ADCSRA_ADIE);

    // Start conversion
    SET_BIT(ADCSRA, ADCSRA_ADSC);

    // Store the pointer to the reading variable
    Global_ptrToReading = Copy_u16DigitalReading;
}

// Set ADC Callback Function
void ADC_voidADCSetCallBack(void (*Copy_ptrToFunction)(void))
{
    if (Copy_ptrToFunction != NULL_PTR)
    {
        Global_ptrToFunction = Copy_ptrToFunction;
    }
}

// ISR for ADC Conversion Complete
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
    // Store the result in the global pointer
    *Global_ptrToReading = ADCH;

    // Call the user-defined callback function
    if (Global_ptrToFunction != NULL_PTR)
    {
        Global_ptrToFunction();
    }
}
