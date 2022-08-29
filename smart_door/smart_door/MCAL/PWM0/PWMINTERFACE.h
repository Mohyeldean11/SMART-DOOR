/*
 * PWMINTERFACE.h
 *
 * Created: 8/26/2022 7:00:59 PM
 *  Author: mohye
 */ 


#ifndef PWMINTERFACE_H_
#define PWMINTERFACE_H_

/*types of pwm*/
#define fastPwm			1
#define phasePwm		2



/*Prescalers*/
#define prescaler1		1
#define prescaler8		2
#define prescaler64		3
#define prescaler256	4
#define prescaler1024	5

typedef enum PWMSTATUS				//defining a status for the pwm functions
{
	pwmok,pwm_initerror,pwmdutyerror
}PwmStatus;

/*a function to initialize the pwm and activate it*/
PwmStatus PwmInit(uint8 PwmType,uint8 Prescaler);

PwmStatus PwmDuty(uint8 DutyCycle);


#endif /* PWMINTERFACE_H_ */