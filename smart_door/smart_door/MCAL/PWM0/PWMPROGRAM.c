/*
 * PWMPROGRAM.c
 *
 * Created: 8/26/2022 7:00:39 PM
 *  Author: mohye
 */ 
#include "../../UTILITIES/DataTypes.h"
#include "../../UTILITIES/bitmath.h"
#include "../GPIO/DIO_INTERFACE.h"
#include "TIMER_PRIVATE.h"
#include "PWMINTERFACE.h"






PwmStatus PwmInit(uint8 PwmType,uint8 Prescaler)
{
	/*creating a flag error*/
	uint8 Errorflag=pwm_initerror;
	if(PwmType==fastPwm)
	{
		/*activating the fast pwm */
		SetBit(TIM_TCCR0,TCCR0_WGM00);
		SetBit(TIM_TCCR0,TCCR0_WGM01);	
		/*assigning the Errorflag*/
		Errorflag=pwmok;
	}
	if(PwmType==phasePwm)
	{
		/*activating the correct phase pwm */
		SetBit(TIM_TCCR0,TCCR0_WGM00);
		ClearBit(TIM_TCCR0,TCCR0_WGM01);
		/*assigning the flag*/
		Errorflag=pwmok;
	}
	/*configuring the oc0 to be output*/
	PinConfig(PORTB,pin3,output);
	/*making it always non inverting mode*/
	ClearBit(TIM_TCCR0,TCCR0_COM00);
	SetBit(TIM_TCCR0,TCCR0_COM01);
	
	/*assigning the prescaler*/
	TIM_TCCR0|=Prescaler;

	return Errorflag;
}


PwmStatus PwmDuty(uint8 DutyCycle)
{
	/*creating a flag error*/
	uint8 Errorflag=pwmok;
	/*loading the ocr0 with the duty cycle value*/
	TIM_OCR0=DutyCycle;
	/*checking if there is any error occured*/
	if(TIM_OCR0==0)
	{
		Errorflag==pwmdutyerror;
	}
	return Errorflag;
}