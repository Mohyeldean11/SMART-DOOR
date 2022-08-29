/*
 * DIO_INTERFACE.h
 *
 * Created: 7/21/2022 2:44:31 AM
 *  Author: mohye
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/*interfacing typedefs*/
typedef enum ErrorStatus
{
	ok,read_error,write_error,config_error,toggle_error
}DIO_ErrorStatus;

										/************************************************************************/
										/*							Interfacing Macros							*/
										/************************************************************************/
/*PORTS*/
#define PORTA		0
#define PORTB		1
#define PORTC		2
#define PORTD		3

/*PINS*/
#define pin0		(0b00000001)
#define pin1		(0b00000010)
#define pin2		(0b00000100)
#define pin3		(0b00001000)
#define pin4		(0b00010000)
#define pin5		(0b00100000)
#define pin6		(0b01000000)
#define pin7		(0b10000000)

/*STATUS*/
#define input_float			0
#define input_pullup		1
#define output				2


/*value*/
#define  HIGH				1
#define  LOW				0
										/************************************************************************/
										/*							FUNCTION PROTOTYPES							*/
										/************************************************************************/

/*a function to configure the direction and the port of the pin */
DIO_ErrorStatus PinConfig(uint8 port,uint8 pin,uint8 status);

/*a function to write a value on a pin,High or Low*/
DIO_ErrorStatus PinWrite(uint8 port,uint8 pin,uint8 value);

/*a function to read the value that's on the pin*/
DIO_ErrorStatus PinRead(uint8 port,uint8 pin, uint8* returned);

/*a function to toggle the value that's on the pin already*/
DIO_ErrorStatus PinToggle(uint8 port,uint8 pin);


#endif /* DIO_INTERFACE_H_ */