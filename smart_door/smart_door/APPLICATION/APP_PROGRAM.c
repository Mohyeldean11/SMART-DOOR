/*
 * APP.c
 *
 * Created: 8/27/2022 10:09:06 PM
 *  Author: mohye
 */ 

#include "../UTILITIES/DataTypes.h"
#include "../UTILITIES/bitmath.h"
#include "../MCAL/GPIO/DIO_INTERFACE.h"
#include "../MCAL/INTERNAL_EEPROM/MCU_EEPROM_INTERFACE.h"
#include "../MCAL/PWM0/PWMINTERFACE.h"
#include "../MCAL/Timer2/TIMER2_INTERFACE.h"
#include "../HAL/DOOR/DOOR_INTERFACE.h"
#include "../HAL/IR SENSOR/IR_INTERFACE.h"
#include "../HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../HAL/LCD/LCD_INTERFACE.h"


/*a function to initialize all the used drivers in the application*/
void INITIALIZE_ALL(void)
{
	/*INITIALIZING THE DOOR,LCD,KEYPAD AND DOOR LCDS*/
	DoorInit();
	LCD_INIT();
	KeyPad_Init();
	PinConfig(PORTC,pin1|pin2,output);
	/*LOADING THE MEMORY WITH THE DOOR PIN*/
	for (uint8 loop=0;loop<4;loop++)
	{
		EEPROM_Write(loop,'1'+loop);
		Timer2DelayNoInt(8);
	}
	
}

/*a function to turn on the buzzer*/
void BUZZERON(void)
{
	PinConfig(PORTC,pin0,output);
	PinWrite(PORTC,pin0,HIGH);
}

/*a function to turn off the buzzer*/
void BUZZEROFF(void)
{
	PinConfig(PORTC,pin0,output);
	PinWrite(PORTC,pin0,LOW);
}

/*the algorithm for the whole application*/
void AppWorking(void)
{
	/*a read value for the eeprom memory*/
	uint8* memoryRead='\0';
	/*a value to carry the pressed keypad key*/
	uint8 keypadValue=0;
	/*a flag to know how many times the pin was wrong*/
	static uint8 wrongPW=0;
	/*a flag to know how many numbers are right in the entered pin*/
	uint8 PWvalue=0;
	/*a loop value to enter the pin */
	uint8 PWloop=0;
	/*checking if the IR Sensor is off or on*/
	if(IR_GET_READ())
	{
		/*opening the lcd display*/
		LCD_ON();
		/*clearing the previouse display*/
		LCD_Clear();
		/*go to the middle of the screen*/
		LCD_GOTO_XY(LCD_ROW0,LCD_COL3);
		/*asking for the pw*/
		LCD_SEND_STRING("ENTER PW");
		/*getting the pw */
		LCD_GOTO_XY(LCD_ROW1,LCD_COL0);
		/*a loop to get the 4pin digits*/
		while(PWloop<4)
		{
			/*getting the pressed key*/
			keypadValue=KeyPad_Work();
			/*displaying the pressed key on the screen*/
			LCD_SendChar(keypadValue);
			/*reading the targeted pw from the memory*/
			EEPROM_READ(PWloop,memoryRead);
			/*comparing the pin in the memory with the entered pin*/
			if (*(memoryRead)==keypadValue)
			{
				/*iterating the pw value if the pressed key was like the memory*/
				PWvalue++;
			}
			PWloop++;
		}
			/*if the memory was correct*/
			if (PWvalue==4)
			{
				/*turning on the green light and off the red light*/
				PinWrite(PORTC,pin1,HIGH);
				PinWrite(PORTC,pin2,LOW);
				/*clearing the lcd*/
				LCD_Clear();
				LCD_GOTO_XY(LCD_ROW0,LCD_COL0);
				/*display a greeting message*/
				LCD_SEND_STRING("WELCOME MOHIE !");
				/*opening the door*/
				DoorOpen();
				/*waiting for the person to enter the door*/
				while(IR_GET_READ());
				/*display a closing message */
				LCD_Clear();
				LCD_GOTO_XY(LCD_ROW0,LCD_COL0);
				LCD_SEND_STRING("CLOSING !!");
				/*turning on the red light and off the green light*/
				PinWrite(PORTC,pin1,LOW);
				PinWrite(PORTC,pin2,HIGH);
				/*closing the door*/
				DoorClose();
				/*clearing the display*/
				LCD_Clear();
				LCD_OFF();
			}
			/*if pw is wrong*/
			else if(PWvalue<4)
			{
				/*iterating the trials of the entered pin*/
				wrongPW++;
				/*display a wrong pin message*/
				LCD_Clear();	
				LCD_GOTO_XY(LCD_ROW0,LCD_COL3);
				LCD_SEND_STRING("WRONG PIN");
				/*delaying for 2 seconds*/
				Timer2DelayNoInt(2000);
				/*if the pin was wrong 3 times*/
				if (wrongPW>=3)
				{
					/*turning on the buzzer*/
					BUZZERON();				
					/*display a NO MORE TRYING message*/	
					LCD_Clear();
					LCD_GOTO_XY(LCD_ROW0,LCD_COL0);
					LCD_SEND_STRING("NO MORE TRYING !!");
					/*make sure the red light is on*/
					PinWrite(PORTC,pin2,HIGH);
					/*flashing the buzzer*/
					BUZZEROFF();
					Timer2DelayNoInt(500);
					BUZZERON();
					Timer2DelayNoInt(500);			
					BUZZEROFF();
					Timer2DelayNoInt(500);
					BUZZERON();
					Timer2DelayNoInt(500);
					BUZZEROFF();
					Timer2DelayNoInt(500);
					BUZZERON();
					/*turning off the buzzer*/						
					BUZZEROFF();
					/*clearing the  screen*/
					LCD_Clear();
					/*reseting the pw flag*/
					wrongPW=0;	
					/*turning the lcd*/
					LCD_OFF();
				}
			}
	}
	/*if no one infront of the door*/
	else if (IR_GET_READ()==0)
	{
				/*turning off the lcd*/
				LCD_OFF();
				/*turning on the red led*/
				PinWrite(PORTC,pin2,HIGH);
	}
	
}