/*********************************************************/
/* Component : ADC                                      */
/* File      : ADC_interface.h                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_



/***********************************************************************/
/*************************Interfacing macros****************************/
/***********************************************************************/

//For ADC channels IDs
#define CHANNEL0       0
#define CHANNEL1       1
#define CHANNEL2       2
#define CHANNEL3       3
#define CHANNEL4       4
#define CHANNEL5       5
#define CHANNEL6       6
#define CHANNEL7       7



/***********************************************************************/
/************************Functions' prototypes**************************/
/***********************************************************************/

void ADC_voidInit(void);


u8 ADC_u8StartConversionSync(u8 Copy_u8ChannelID);


void ADC_voidStartConversionAsync(u8 Copy_u8ChannelID , u8 * Copy_u16DigitalReading);

void ADC_voidADCSetCallBack(void(*Copy_ptrToFunction)(void));


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
