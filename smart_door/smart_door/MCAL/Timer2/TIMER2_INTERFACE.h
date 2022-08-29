/*
 * TIMER_INTERFACE.h
 *
 * Created: 7/22/2022 2:20:34 PM
 *  Author: mohye
 */ 


#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

typedef enum TimerErrorStatus
{
 TIM_ok,TIMTOV_InitError,TIMCTC_InitError,TIM_OffError,TIM_ResetError,TIM_DelayError 
}TimerErrorStatus;

#define  NULLPTR		(void*)0
              /************************************************************************/
              /*      INTERFACING MACROS										      */
              /************************************************************************/
/*prescalers*/
#define NO_PRESCALER		 1
#define _8_PRESCALER		 2
#define _64_PRESCALER		 3
#define _256_PRESCALER		 4
#define _1024_PRESCALER		 5


/* delay counter variables*/
volatile uint32 DelayCounter;
volatile uint32 DelayCounter1;


              /************************************************************************/
              /*					 FUNCTION PROTOTYPES							  */
              /************************************************************************/

/*a function to initialize normal timer2*/
TimerErrorStatus Timer2TOV_Init(uint8 Prescaler,void(*funcTOptr)(void));

/*a function to initialize compare match timer2*/
TimerErrorStatus Timer2CTC_Init(uint8 Prescaler,uint8 CompareValue,uint8 Oc0Pin,void(*funcTOptr)(void));     

/*a function to reset the timer2*/
TimerErrorStatus Timer2_Reset(void);

/*a function to turn off the timer2*/
TimerErrorStatus Timer2_Off(void);

/*a function to make a delay in milliseconds*/
TimerErrorStatus Timer2_delay_ms(uint32 DelayVariable);

/*a function to initialize a 1 millisecond counter*/
TimerErrorStatus Timer2_1ms_Init(void);

/*a function to increment the delay counter*/
TimerErrorStatus Timer2DelayCounter(void);


/*a function for the delay without interrupt*/
TimerErrorStatus Timer2_delay_ms(uint32 DelayVariable);

/*a delay funcion without interrupt 'using the counter register'*/
TimerErrorStatus Timer2DelayNoInt(uint32 DelayValue);
#endif /* TIMER_INTERFACE_H_ */