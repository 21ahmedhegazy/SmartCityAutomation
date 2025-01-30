/*********************************************************/
/* Component : TIMER                                      */
/* File      : TIMER_config.h                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 5 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

/******************* CONFIG MACROS *****************/

/* TIMER0 Mode Configuration
 * OPTIONS:
 * 1-NORMAL_MODE
 * 2-CTC_MODE
 * 3-FAST_PWM
 * 4-PHASE_CORRECT_PWM
 */
#define TIMER0_MODE       FAST_PWM

/* TIMER1 Mode Configuration
 * OPTIONS:
 * 1-NORMAL_MODE
 * 2-CTC_MODE
 * 3-FAST_PWM
 * 4-PHASE_CORRECT_PWM
 */
#define TIMER1_MODE       FAST_PWM

#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
