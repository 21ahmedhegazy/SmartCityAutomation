/*
 * LCD_Interface.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Hegazy
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

#define Lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define Lcd_Home            0x02          /* return cursor to first position on first line                   */
#define Lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define Lcd_DisplayOff      0x08          // turn display off
#define Lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define Lcd_FunctionReset   0x30          // reset the LCD
#define Lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define Lcd_SetCursor       0x80          // set cursor position

void LCD_voidInit(void);
void LCD_voidWriteCommand (u8 Copy_u8Command);
void LCD_voidWriteData (u8 Copy_u8Data);
void LCD_voidWriteString(u8* Copy_pu8String );
void LCD_voidWriteStringTwoLine(u8* Copy_pu8String );
void LCD_voidGOToXY(u8 Copy_u8ROW ,u8 Copy_u8COL);
void LCD_voidSendSpecialCharacter(u8 * Copy_pu8Pattern , u8 Copy_u8Location
								  ,u8 Copy_u8Row , u8 Copy_u8Col );
void LCD_voidFree(u8 Copy_u8ROW ,u8 Copy_u8COL);
void LCD_voidClearDisplay(void);
void LCD_voidWriteNumber(u32 copy_u32Number);


#endif /* HAL_LCD_LCD_INTERFACE_H_ */

