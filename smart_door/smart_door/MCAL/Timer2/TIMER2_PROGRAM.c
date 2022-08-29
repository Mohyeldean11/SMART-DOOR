
/*
 * TIMER_PROGRAM.c
 *
 * Created: 7/22/2022 2:32:50 PM
 *  Author: mohye
 */ 

									/************************************************************************/
									/*								INCLUDES								*/
									/************************************************************************/
#include "../../UTILITIES/DataTypes.h"
#include "../../UTILITIES/bitmath.h"
#include "TIMER2_PRIVATE.h"
#include "TIMER2_INTERFACE.h"

									/************************************************************************/
									/*								GLOBAL VARIABLES						*/
									/************************************************************************/
void (*GbTo_TOVtim) (void)=NULLPTR;

void (*GbTo_CTCtim) (void)=NULLPTR;


/*a function to initialize normal timer0*/
TimerErrorStatus Timer2TOV_Init(uint8 Prescaler,void(*funcTOptr)(void))
{
	uint8 ErrorFlag=TIM_ok;
	
	/*activating the global interrupt flag*/
	SetBit(TIM_SREG2,SREG_I);
	
	/*reseting the prescaler to begin counting*/
	 SetBit(TIM_SFIOR,SFIOR_PSR2);
	
	/*adjusting the timer mode to normal mode*/
	 ClearBit(TIM_TCCR2,TCCR2_WGM20);
	 ClearBit(TIM_TCCR2,TCCR2_WGM21);
 
	/*disabling the oc0 pin as its normal mode*/
	 ClearBit(TIM_TCCR2,TCCR2_COM20);
	 ClearBit(TIM_TCCR2,TCCR2_COM21);

	/*activating the interrupt for timer overflow event*/ 
	 SetBit(TIM_TIMSK2,TIMSK2_TOIE2);
 
	/*setting the prescaler for the counter*/
	 TIM_TCCR2|=Prescaler;

	/*passing the function to the global pointer*/
	GbTo_TOVtim=funcTOptr;
	
	/*checking for the error flag*/
	 if(TIM_TCCR2==0)
	 {
		 ErrorFlag=TIMTOV_InitError;
	 }
	/*returning the function status*/
	 return ErrorFlag;
}

/*a function to initialize compare match timer2*/
TimerErrorStatus Timer2CTC_Init(uint8 Prescaler,uint8 CompareValue,uint8 Oc0Pin,void(*funcTOptr)(void))
{
		/*creating error flag*/
		uint8 Errorflag=TIM_ok;
		/*activating the global interrupt flag*/
		SetBit(TIM_SREG2,SREG_I);
			
		/*adjusting the timer mode to CTC mode*/
		ClearBit(TIM_TCCR2,TCCR2_WGM20);
		SetBit(TIM_TCCR2,TCCR2_WGM21);
		
		/*disabling the oc0 pin*/
		ClearBit(TIM_TCCR2,TCCR2_COM20);
		ClearBit(TIM_TCCR2,TCCR2_COM21);
		
		/*activating the interrupt for timer overflow event*/
		SetBit(TIM_TIMSK2,TIMSK2_OCIE2);
		
		/*putting the value to be compared with*/
		TIM_OCR2=CompareValue;
		
		/*setting the prescaler for the counter*/
		TIM_TCCR2|=Prescaler;

		/*passing the function to the global pointer*/
		GbTo_CTCtim=funcTOptr;
		
		/*reseting the prescaler to begin counting*/
		SetBit(TIM_SFIOR,SFIOR_PSR2);
		
		/*checking for the error flag*/
		if(TIM_TCCR2==0)
		{
			Errorflag=TIMCTC_InitError;
		}
		/*returning the function status*/
		return Errorflag;
}

/*a function to reset the timer*/
TimerErrorStatus Timer2_Reset(void)
{
	/*creating error flag*/
	uint8 Errorflag=TIM_ok;
	
	/*reseting the counter register*/
	SetBit(TIM_SFIOR,SFIOR_PSR2);
	
	/*checking the function error status*/
	if(ReadBit(TIM_SFIOR,SFIOR_PSR2)==1)
	{
		Errorflag=TIM_ResetError;
	}
	/*returning the function status*/
	return Errorflag;
}

/*a function to turn off the timer*/
TimerErrorStatus Timer2_Off(void)
{
	/*creating error flag*/
	uint8 Errorflag=TIM_ok;
	/*DISABLING THE TIMER CONTROL REGISTER AS PUTTING THE PRESCALER TO 0 */
	TIM_TCCR2=0;
	/*checking for the error flag*/
	if(TIM_TCCR2!=0)
	{
		Errorflag=TIM_OffError;
	}
	/*returning the function status*/
	return Errorflag;
}






									/************************************************************************/
									/*							DELAY FUNCTIONS                             */
									/************************************************************************/

/*a function to make a delay in milliseconds*/
TimerErrorStatus Timer2_delay_ms(uint32 DelayVariable)
{
	/*create error flag*/
	uint8 Errorflag=TIM_ok;
	/*checking for the timer error status*/
	if(GbTo_CTCtim==NULLPTR)
	{
		Errorflag=TIM_DelayError;
	}
	/*reseting the delay counter for the delay operation*/
	DelayCounter=0;
	Timer2_Reset();
	/*creating the delay by the polling on while loop*/
	while(DelayVariable>=DelayCounter);
	
	/*returning the function status*/	
	return Errorflag;
}


/*a function to initialize compare match timer0 to 1 millisecond*/
TimerErrorStatus Timer2_1ms_Init(void)
{
	/*creating error flag*/
	uint8 Errorflag=TIM_ok;
	/*activating the global interrupt flag*/
	SetBit(TIM_SREG2,SREG_I);
	
	/*adjusting the timer mode to CTC mode*/
	ClearBit(TIM_TCCR2,TCCR2_WGM20);
	SetBit(TIM_TCCR2,TCCR2_WGM21);
	

	/*disabling the oc0 pin*/
	ClearBit(TIM_TCCR2,TCCR2_COM20);
	ClearBit(TIM_TCCR2,TCCR2_COM21);
	
	/*activating the interrupt for timer overflow event*/
	SetBit(TIM_TIMSK2,TIMSK2_OCIE2);
	
	/*putting the value to be compared with*/
	TIM_OCR2=250;
	
	/*setting the prescaler for the counter*/
	TIM_TCCR2|=_64_PRESCALER;

	/*passing the function to the global pointer*/
	GbTo_CTCtim=Timer2DelayCounter;
	
	/*reseting the prescaler to begin counting*/
	SetBit(TIM_SFIOR,SFIOR_PSR2);
	
	/*checking for the error flag*/
	if(TIM_TCCR2==0)
	{
		Errorflag=TIM_DelayError;
	}
	/*returning the function status*/
	return Errorflag;
}


/*a function to increment the delay counter*/
TimerErrorStatus Timer2DelayCounter(void)
{
	/*creating error flag*/
	uint8 Errorflag=TIM_ok;
	/*incrementing the delay counter each millisecond to accumelate a delay*/
	DelayCounter++;
	/*checking for the error flag*/
	if (DelayCounter==0)
	{
		Errorflag=TIM_DelayError;
	}
	/*returning the function status*/
	return Errorflag;
}


/*a delay funcion without interrupt 'using the counter register'*/
TimerErrorStatus Timer2DelayNoInt(uint32 DelayValue)
{
	/*creating a flag error*/
	uint8 Errorflag=TIM_ok;
	/*reseting the delay counter to 0*/
	DelayCounter1=0;
	/*reseting the counter register to 0*/
	TIM_TCNT2=0;
	/*busy waiting as a delay*/
	while(2*DelayValue>DelayCounter1)
	{
		/*if the counter equals 250 '0.5 milli second'*/
		if (TIM_TCNT2==250)
		{
			/*increment the delay counnter by 1*/
			DelayCounter1++;
		}
	}
	/*checking for the error flag*/
	if(TIM_TCNT2==0)
	{
		Errorflag=TIM_DelayError;
	}
	/*returning the function status*/
	return Errorflag;

}

									/************************************************************************/
									/*								ISR										*/
									/************************************************************************/

/*ISR FOR COMPARE MATCH OVERFLOW*/
void __vector_4 (void)		__attribute__((signal));
void __vector_4 (void)
{
	if(GbTo_CTCtim!=NULLPTR)
	{
		GbTo_CTCtim();
	}

}

/*ISR FOR TIMER OVERFLOW*/
void __vector_5 (void)		__attribute__((signal));
void __vector_5 (void)
{
	if(GbTo_TOVtim!=NULLPTR)
	{
		GbTo_TOVtim();
	}

}

