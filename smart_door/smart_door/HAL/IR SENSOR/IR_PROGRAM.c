/*
 * IR_PROGRAM.c
 *
 * Created: 8/28/2022 5:04:12 AM
 *  Author: mohye
 */ 
#include "../../UTILITIES/DataTypes.h"
#include "../../MCAL/GPIO/DIO_INTERFACE.h"
#include "IR_INTERFACE.h"
/*a function to read the IR VALUE*/
uint8 IR_GET_READ(void)
{
	/*creating a value to detect obstacles*/
	uint8 readValue='\0';
	/*configuring the input pin for the mcu*/
	PinConfig(IR_PORT,IR_PIN,input_float);
	
	/*checking if there're any obstacles*/
	PinRead(IR_PORT,IR_PIN,&readValue);
	/*returning the read value*/
	return readValue;	
}