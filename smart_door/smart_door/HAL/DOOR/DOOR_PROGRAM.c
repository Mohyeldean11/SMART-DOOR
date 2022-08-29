/*
 * DOOR_PROGRAM.c
 *
 * Created: 8/27/2022 12:38:10 AM
 *  Author: mohye
 */ 

#include "../../UTILITIES/DataTypes.h"
#include "../../UTILITIES/bitmath.h"
#include "../../MCAL/Timer2/TIMER2_INTERFACE.h"
#include "../../MCAL/PWM0/PWMINTERFACE.h"
#include "DOOR_INTERFACE.h"

/*to get the following degree cycles we will use the 256 prescaler and fast pwm*/
/*for 0 degree------->19 dutycycle   0.388ms 
  for 90 degree------>80 dutycycle	 1.264ms 
  for 180 degree---->125 dutycycle	 2.14ms 
  */
	
/*a function to initialize the door to its first state*/
DoorStatus DoorInit(void)
{
	/*creating an error flag*/
	uint8 Errorflag=DoorOK;
	/*initializing the timer delay*/
	Timer2_1ms_Init();
	/*initializing the pwm generator*/
	PwmInit(fastPwm,_256_PRESCALER);
	/*setting the door to its initial state*/
	DoorPosition=_0degrees;
	/*updating the servo motor with the position*/
	PwmDuty(DoorPosition);
	/*returning the function status*/
	return Errorflag;
}

/*a function to open the door*/
DoorStatus DoorOpen(void)
{
	/*creating an error flag*/
	uint8 Errorflag=DoorOpenError;
	
	/*rechecking if the door is actually closed*/
	//uint8 DoorValue=_0degrees;
	
	/*decrementing the pwm to open the door from 0 to 180*/
	while(DoorPosition<=_180degrees)
	{
		/*updating the error flag to ok*/
		Errorflag=DoorOK;
		/*updating the servo motor with the position*/
		PwmDuty(DoorPosition);
		/*delaying*/
		Timer2_delay_ms(50);
		/*incrementing the duty cycle*/
		DoorPosition++;
	}
	/*returning the function status*/	
	return Errorflag;
}
/*a function to close the door*/
DoorStatus DoorClose(void)
{
	/*creating an error flag*/
	uint8 Errorflag=DoorCloseError;
	
	/*rechecking if the door is actually opened*/
	//uint8 DoorValue=_180degrees;
	
	/*decrementing the pwm to close the door from 180 to 0*/
	while(DoorPosition>=_0degrees)
	{
		/*updating the error flag to ok*/
		Errorflag=DoorOK;
		/*updating the servo motor with the position*/
		PwmDuty(DoorPosition);
		/*delaying*/
		Timer2_delay_ms(50);
		/*decrementing the duty cycle*/
		DoorPosition--;
	}
	/*returning the function status*/
	return Errorflag;	
}