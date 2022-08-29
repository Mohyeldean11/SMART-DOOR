/*
 * KEYPAD_PRIVATE.h
 *
 * Created: 8/27/2022 8:33:56 PM
 *  Author: mohye
 */ 


#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_

/*KEYPAD ROWS AND COLUMNS DEFINITIONS*/
#define	KEYPAD_ROW_PORT						(PORTA)
		#define  KEYPAD_ROW1				 (pin0)
		#define  KEYPAD_ROW2				 (pin1)
		#define  KEYPAD_ROW3				 (pin2)
		#define  KEYPAD_ROW4				 (pin3)

#define KEYPAD_COL_PORT						(PORTA)
		#define  KEYPAD_COL1				 (pin4)
		#define  KEYPAD_COL2				 (pin5)
		#define  KEYPAD_COL3				 (pin6)

/*KEYPAD BUTTONS SET*/
#define KeyPadArray			{{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}}
	
		#define KeyPadCol						(3)
		#define KeyPadRow						(4)
/*THE DUMMY INITIALIZED KEY*/
#define KeyPad_NoPressed						(0xff)

#endif /* KEYPAD_PRIVATE_H_ */