/*
 * LCD_CONFIG.h
 *
 * Created: 8/27/2022 2:52:41 PM
 *  Author: mohye
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_DATA_PORT				PORTD
		#define LCD_DATA_BYTE		(0b11111111)
		
#define LCD_INST_PORT				PORTC
		#define LCD_ENABLE_PIN		pin7
		#define LCD_RW_PIN			pin6
		#define LCD_RS_PIN			pin5



#endif /* LCD_CONFIG_H_ */