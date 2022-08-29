/*
 * LCD_INTERFACE.h
 *
 * Created: 8/27/2022 2:06:27 AM
 *  Author: mohye
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*ERROR STATUS*/
typedef enum LCDErrorStatus
{
	LCDok,
	LCDInitError,
	LCDSendInstructionError,
	LCDSendDataError,
	LCDSendStringError,
	LCDCLearError,
	LCDGoToXYError,
	LCDSendCharError
}LCDstatus;


/*INITIALIZATION COMMANDS*/

#define LCD_ClearDisplay		(0b00000001)
#define LCD_DisplayON			(0b00001111)
#define LCD_DisplayOFF			(0b00001011)
#define LCD_FUNCTION_SET		(0b00111000)


/*LCD ROWS*/

#define  LCD_ROW0	 0
#define  LCD_ROW1	 1



/*LCD COLS*/

#define  LCD_COL0	(0)
#define  LCD_COL1	(1)
#define  LCD_COL2	(2)
#define  LCD_COL3	(3)
#define  LCD_COL4	(4)
#define  LCD_COL5	(5)
#define  LCD_COL6	(6)
#define  LCD_COL7	(7)
#define  LCD_COL8	(8)
#define  LCD_COL9	(9)
#define  LCD_COL10	(10)
#define  LCD_COL11	(11)
#define  LCD_COL12	(12)
#define  LCD_COL13	(13)
#define  LCD_COL14	(14)
#define  LCD_COL15	(15)


					/************************************************************************/
					/*				FUNCTION PROTOTYPES										*/
					/************************************************************************/

/*internal function to send COMMAND to the LCD*/
static void LCD_SEND_COMMAND(uint8 COMMAND);

/*internal function to send DATA to the LCD*/
static void LCD_SEND_DATA(uint8 DATABITE);

/*a function to Initialize the LCD*/
LCDstatus LCD_INIT(void);

/*a function to send a string on the screen*/
LCDstatus LCD_SEND_STRING(uint8* STRING);

/*a function to clear the LCD*/
LCDstatus LCD_Clear(void);

/*a function to type in a specific place*/
LCDstatus LCD_GOTO_XY(uint8 Row,uint8 Col);

/*a function to send a character on the screen*/
LCDstatus LCD_SendChar(uint8 charact);

/*a function to turn off the LCD DISPLAY*/
LCDstatus LCD_OFF(void);

/*a function to turn on the LCD display*/
LCDstatus LCD_ON(void);

#endif /* LCD_INTERFACE_H_ */