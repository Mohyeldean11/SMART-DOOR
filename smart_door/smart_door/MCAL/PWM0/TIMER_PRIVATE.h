/*
 * TIMER_PRIVATE.h
 *
 * Created: 7/22/2022 2:21:09 PM
 *  Author: mohye
 */ 


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

                /************************************************************************/
                /*     TIMER REGISTERS DEFINITIONS										*/
                /************************************************************************/
#define  TIM_SREG    (*(volatile uint8*)(0x5F))
	#define SREG_I			7

#define TIM_OCR0    (*(volatile uint8*)(0x5C))     //compare match register

#define TIM_TIMSK   (*(volatile uint8*)(0x59))
	#define TIMSK_OCIE0     1
	#define TIMSK_TOIE0     0

#define TIM_TIFR    (*(volatile uint8*)(0x58))
	#define TIFR_OCF0		1
	#define TIFR_TOV0		0


#define TIM_TCCR0   (*(volatile uint8*)(0x53))
	#define TCCR0_WGM00     6
	#define TCCR0_COM01     5
	#define TCCR0_COM00     4
	#define TCCR0_WGM01     3 
	#define TCCR0_CS02		2
	#define TCCR0_CS01		1
	#define TCCR0_CS00		0

#define TIM_TCNT0   (*(volatile uint8*)(0x52))     //counter register

#define TIM_SFIOR   (*(volatile uint8*)(0x50))
	#define SFIOR_PSR10     0
 
 
#endif /* TIMER_PRIVATE_H_ */