/*
 * TIMER_PRIVATE.h
 *
 * Created: 8/26/2022 10:45:47 PM
 *  Author: mohye
 */ 


#ifndef TIMER2_PRIVATE_H_
#define TIMER2_PRIVATE_H_

#define  TIM_TCNT2			(*(volatile uint8 *)(0x44))

#define  TIM_OCR2			(*(volatile uint8 *)(0x43))

#define	 TIM_TCCR2			(*(volatile uint8 *)(0x45))
		#define		TCCR2_FOC2					7
		#define		TCCR2_WGM20					6
		#define		TCCR2_COM21					5
		#define		TCCR2_COM20					4
		#define		TCCR2_WGM21					3
		#define		TCCR2_CS22					2
		#define		TCCR2_CS21					1
		#define		TCCR2_CS20					0

#define TIM_SFIOR			(*(volatile uint8 *)(0x50))
		#define		SFIOR_PSR2					1

#define TIM_SREG2			(*(volatile uint8 *)(0x5F))
		#define    SREG_I						7
		
#define TIM_TIMSK2			(*(volatile uint8 *)(0x59))
		#define		TIMSK2_OCIE2				7
		#define		TIMSK2_TOIE2				6

#endif /* TIMER_PRIVATE_H_ */