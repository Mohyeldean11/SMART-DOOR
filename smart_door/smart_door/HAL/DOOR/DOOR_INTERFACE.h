/*
 * DOOR_INTERFACE.h
 *
 * Created: 8/27/2022 12:37:45 AM
 *  Author: mohye
 */ 


#ifndef DOOR_INTERFACE_H_
#define DOOR_INTERFACE_H_


typedef enum DOORERRORSTATUS
{
	DoorOK,DoorInitError,DoorOpenError,DoorCloseError
}DoorStatus;

/*DutyCycle degrees*/
#define _0degrees		19
#define _90degrees		80
#define _180degrees		125

/*creating a variable for the door position*/
volatile uint8 DoorPosition;

/*a function to initialize the door to its first state*/
DoorStatus DoorInit(void);

/*a function to open the door*/
DoorStatus DoorOpen(void);

/*a function to close the door*/
DoorStatus DoorClose(void);





#endif /* DOOR_INTERFACE_H_ */