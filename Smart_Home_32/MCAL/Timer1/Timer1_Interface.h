#ifndef TIMER1_INTERFACE_H
#define TIMER1_INTERFACE_H


#define PRESCALAR_NO_CLOCK          0
#define PRESCALAR_1_CLOCK           1
#define PRESCALAR_8_CLOCK           2
#define PRESCALAR_64_CLOCK          3
#define PRESCALAR_256_CLOCK         4
#define PRESCALAR_1024_CLOCK        5
#define EXTERNAL_FALLING_CLOCK      6
#define EXTERNAL_RAISING_CLOCK      7

//Timer/conter1 channel for pwm or ctc
#define CHANNELA      0
#define CHANNELB      1

#define  ICU_RAISING_EDGE  1
#define  ICU_FALLING_EDGE  0

void TIMER1_voidInit(void);
void TIMER1_voidFastPWMNonIntvered(u8 Copy_u8Channel , u8 Copy_u8Prescaler);
void TIMER1_voidNormalMode(u8 Copy_u8Prescaler);
void TIMER1_voidResetTimer(void);

void TIMER1_voidSetDutyCycle(u8 Copy_u8Channel ,u16 Copy_u16DutyCycle);
void TIMER1_voidSetTopValue(u16 Copy_u16TopValue);
void TIMER1_voidServoRotate(u8 Copy_u8Channel ,u8 Copy_u8Angle);
u16  TIMER1_u16GetElapsedTimer(void);

void TIMER1_voidStopTimer1(void);


void TIMER1_voidSetTimer(u16 Copy_u16Ticks);


void ICU_voidSetTrigger(u8 Copy_u8Edge);
void ICU_voidEnableInterrupt(void);
void ICU_voidDisableInterrupt(void);
void ICU_CallBackFun(void (*ptr)(void));

#endif
