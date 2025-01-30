/*********************************************************/
/* Component : KPD                                       */
/* File      : KPD_interface.h                           */
/* Author    : Hegazy                                     */
/* Date      : 28 . 7 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/


#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

/*************************************************************************/
/*****************************Interfacing macros**************************/
/*************************************************************************/


/*************************************************************************/
/*****************************Functions' prototypes***********************/
/*************************************************************************/

/*Description : This function shall initialize the KPD              				 */
/*Input       : void  							                                     */
/*Return      : void                                                                 */
void KPD_voidInit(void);

/*Description : This function shall get the value of any pressed key in the kpd		 */
/*Input       : void  							                                     */
/*Return      : void                                                                 */
u8 KPD_u8GetPressedKey(void);




#endif /* HAL_KPD_KPD_INTERFACE_H_ */
