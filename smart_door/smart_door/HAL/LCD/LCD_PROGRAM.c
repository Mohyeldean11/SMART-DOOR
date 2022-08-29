/*
 * LCD_PROGRAM.c
 *
 * Created: 8/27/2022 2:06:13 AM
 *  Author: mohye
 */ 
							/************************************************************************/
							/*							INCLUDES                                    */
							/************************************************************************/

#include "../../UTILITIES/DataTypes.h"
#include "../../UTILITIES/bitmath.h"
#include "../../MCAL/GPIO/DIO_INTERFACE.h"
#include "../../MCAL/Timer2/TIMER2_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LCD_INTERFACE.h"


/*internal function to send COMMAND to the LCD*/
static void LCD_SEND_COMMAND(uint8 COMMAND)
{
	/*INITIALIZING THE INSTRUCTION PINS AND SETTING THEM TO LOW*/
	PinConfig(LCD_INST_PORT,LCD_ENABLE_PIN|LCD_RW_PIN|LCD_RS_PIN,output);	
	PinConfig(LCD_DATA_PORT,LCD_DATA_BYTE,output);
	/*resetting the data pins at the beginning*/
	PinWrite(LCD_DATA_PORT,LCD_DATA_BYTE,LOW);
	/*SETTING THE RS PIN TO BE A COMMAND*/
	PinWrite(LCD_INST_PORT,LCD_RS_PIN,LOW);
	/*SETTING THE R/W PIN TO BE WRITE*/
	PinWrite(LCD_INST_PORT,LCD_RW_PIN,LOW);
	/*WRITING ON THE DATA PITS*/
	PinWrite(LCD_DATA_PORT,COMMAND,HIGH);
	/*SENDING AN ENABLE PULSE*/
	PinWrite(LCD_INST_PORT,LCD_ENABLE_PIN,HIGH);
	/*DELAYING FOR 2ms*/
	Timer2_delay_ms(3);
	PinWrite(LCD_INST_PORT,LCD_ENABLE_PIN,LOW);

}

/*internal function to send DATA to the LCD*/
static void LCD_SEND_DATA(uint8 DATABITE)
{
	/*INITIALIZING THE INSTRUCTION PINS*/
	PinConfig(LCD_INST_PORT,LCD_ENABLE_PIN|LCD_RW_PIN|LCD_RS_PIN,output);
	PinConfig(LCD_DATA_PORT,LCD_DATA_BYTE,output);
	/*resetting the data pins at the beginning*/
	PinWrite(LCD_DATA_PORT,LCD_DATA_BYTE,LOW);
	/*SETTING THE RS PIN TO BE A DATA*/
	PinWrite(LCD_INST_PORT,LCD_RS_PIN,HIGH);
	/*SETTING THE R/W PIN TO BE WRITE*/
	PinWrite(LCD_INST_PORT,LCD_RW_PIN,LOW);
	/*WRITING ON THE DATA PITS*/
	PinWrite(LCD_DATA_PORT,DATABITE,HIGH);
	/*SENDING AN ENABLE PULSE*/
	PinWrite(LCD_INST_PORT,LCD_ENABLE_PIN,HIGH);
	/*DELAYING FOR 2ms*/
	Timer2_delay_ms(3);
	PinWrite(LCD_INST_PORT,LCD_ENABLE_PIN,LOW);
}

/*a function to Initialize the LCD*/
LCDstatus LCD_INIT(void)
{
	
	/*creating a flag error*/
	uint8 Errorflag=LCDok;
	/*delaying for 40 milliseconds*/
	Timer2_delay_ms(40);
	/*sending the function set command to have 2 lines,font size*/
	LCD_SEND_COMMAND(LCD_FUNCTION_SET);
	/*activating the display*/
	LCD_SEND_COMMAND(LCD_DisplayON);
	/*clearing the display for the first time*/
	LCD_SEND_COMMAND(LCD_ClearDisplay);
	/*waiting for 2 milliseconds*/
	Timer2_delay_ms(2);
	/*returning function error status*/
	return Errorflag;
}

/*a function to turn off the LCD DISPLAY*/
LCDstatus LCD_OFF(void)
{
	/*creating a flag error*/
	uint8 Errorflag=LCDok;
	/*sending a display off command*/
	LCD_SEND_COMMAND(LCD_DisplayOFF);
	/*return the status of the function*/
	return Errorflag;	
}

/*a function to turn ON the LCD DISPLAY*/
LCDstatus LCD_ON(void)
{
	/*creating a flag error*/
	uint8 Errorflag=LCDok;
	/*sending a display off command*/
	LCD_SEND_COMMAND(LCD_DisplayON);
	/*return the status of the function*/
	return Errorflag;
}

/*a function to send a string on the screen*/
LCDstatus LCD_SEND_STRING(uint8* STRING)
{
	/*creating a flag error*/
	uint8 Errorflag=LCDSendStringError;
	
	while(*(STRING)!='\0')
	{
		LCD_SEND_DATA(*(STRING));
		STRING++;
		Errorflag=LCDok;
	}
	return Errorflag;
}

/*a function to clear the LCD*/
LCDstatus LCD_Clear(void)
{
	/*creating a flag error*/
	uint8 Errorflag=LCDok;
	/*sending a clear command*/
	LCD_SEND_COMMAND(LCD_ClearDisplay);
	/*waiting for two milliseconds*/
	Timer2_delay_ms(2);
	/*returning the error status*/
	return Errorflag;
}

/*a function to send a character on the screen*/
LCDstatus LCD_SendChar(uint8 charact)
{
	/*creating an error flag*/
	uint8 Errorflag=LCDok;
	
	/*sending a character to the LCD*/
	LCD_SEND_DATA(charact);
	
	/*checking if the character was null or not*/
	if(charact==('\0'))
	{
		/*updating the flag error*/
		Errorflag=LCDSendCharError;
	}
	/*returning the status of the function*/
	return Errorflag;
}

/*a function to type in a specific place*/
LCDstatus LCD_GOTO_XY(uint8 Row,uint8 Col)
{
	/*creating an error flag*/
	uint8 Errorflag=LCDGoToXYError;
	/*initializing the ram address for positioning*/
	uint8 DDRAMAdress=0;
	/*checking for which row to write at*/
	if(Row==LCD_ROW0)
	{
		/*typing at the desired column at Row 0*/
		DDRAMAdress=Col;
		/*setting the MSB with one*/
		DDRAMAdress|=(1<<7);
		/*updating the error flag status*/
		Errorflag=LCDok;
	}
	/*incase of Row1*/
	else if(Row==LCD_ROW1)
	{
		/*adding the desired column with the beginning of the second row to write at it*/
		DDRAMAdress=Col+(0x40);
		/*setting the MSB with one*/
		DDRAMAdress|=(1<<7);
		/*updating the error flag status*/
		Errorflag=LCDok;
	}
	/*sending the command */
	LCD_SEND_COMMAND(DDRAMAdress);
	
	return Errorflag;
}