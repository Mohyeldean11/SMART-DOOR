/*
 * KEYPAD_PROGRAM.c
 *
 * Created: 8/27/2022 8:55:46 PM
 *  Author: mohye
 */ 

#include "../../UTILITIES/DataTypes.h"
#include "../../MCAL/GPIO/DIO_INTERFACE.h"
#include "KEYPAD_PRIVATE.h"
#include "KEYPAD_INTERFACE.h"

/*a function to initialize the keypad*/
void KeyPad_Init(void)
{
	/*configuring the rows to be all pullups high*/
	PinConfig(KEYPAD_ROW_PORT,KEYPAD_ROW1|KEYPAD_ROW2|KEYPAD_ROW3|KEYPAD_ROW4,input_pullup);
	/*configuring the columns to be all output high*/
	PinConfig(KEYPAD_COL_PORT,KEYPAD_COL1|KEYPAD_COL2|KEYPAD_COL3,output);

}

/*a function to wait for the key to be pressed before getting another key*/
uint8 KeyPad_Work(void)
{
	/*creating a flag for the keypad and assigning it with the dummy value*/
	uint8 pressedkey=KeyPad_NoPressed;
	do 
	{
		/*checking if there's any key pressed or not*/
		pressedkey=KeyPad_GetKey();
	/*polling over the keypad buttons waiting to be pressed*/	
	} while (pressedkey==KeyPad_NoPressed);
	
	/*returning the key that was pressed*/
	return pressedkey;
}

/*a function to get the pressed key with debouncing fixations*/
static uint8 KeyPad_GetKey(void)
{
	/*passing the ARRAY of buttons*/
	static uint8 keypadarr[KeyPadRow][KeyPadCol]=KeyPadArray;
	/*putting all the COLUMNS pins to an array to iterate through them*/
	static uint8 ColumARRAY[KeyPadCol]={KEYPAD_COL1,KEYPAD_COL2,KEYPAD_COL3};
	/*putting all the ROWS pins to an array to iterate through them*/
	static uint8 RowARRAY[KeyPadRow]={KEYPAD_ROW1,KEYPAD_ROW2,KEYPAD_ROW3,KEYPAD_ROW4};
	/*assigning the pressed key to the dummy value at first*/
	uint8 PressedKey=KeyPad_NoPressed;
	/*creating a read flag to check for the key that was pressed*/
	uint8 *readValue='\0';
	/*iterating over the columns*/
	for (uint8 columnum=0;columnum<KeyPadCol;columnum++)
	{
		/*changing the index column to low to check which row index will be low state*/
		PinWrite(KEYPAD_COL_PORT,ColumARRAY[columnum],LOW);
		/*iterating over the rows*/
		for(uint8 rownum=0;rownum<KeyPadRow;rownum++)
		{
			/*reading every row index to know which key was pressed after matching the row and the columns*/
			PinRead(KEYPAD_ROW_PORT,RowARRAY[rownum],readValue);
			if(*(readValue)==LOW)
			{
				/*assigning the pressed key value with the row number and the column number*/
				PressedKey=keypadarr[rownum][columnum];
				/*busy waiting until the key is not pressed anymore*/
				while(*(readValue)==LOW)
				{
					PinRead(KEYPAD_ROW_PORT,RowARRAY[rownum],readValue);
				}
				/*returning the pressed key from the function*/
				return PressedKey;
			}
		}
		/*reActivating the column index to high and checking for the next one*/
		PinWrite(KEYPAD_COL_PORT,ColumARRAY[columnum],HIGH);
	}
	/*if no key was pressed the function will return the dummy value as it was initialized at the beginning*/
	return PressedKey;
}