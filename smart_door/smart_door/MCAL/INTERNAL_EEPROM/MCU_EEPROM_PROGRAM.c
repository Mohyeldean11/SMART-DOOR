/*
 * MCU_EEPROM_PROGRAM.c
 *
 * Created: 8/28/2022 4:10:17 PM
 *  Author: mohye
 */ 
#include "../../UTILITIES/DataTypes.h"
#include "../../UTILITIES/bitmath.h"
#include "../Timer2/TIMER2_INTERFACE.h"
#include "MCU_EEPROM_PRIVATE.h"
#include "MCU_EEPROM_INTERFACE.h"


/*a function to write on the internal eeprom memory*/
EepromStatus EEPROM_Write(uint8 addresse,uint8 data)
{
	/*create an error flag */
	uint8 errorflag=EEPROMok;
	/*creating an interrupt flag*/
	uint8 interrupt_flag=0;


	/*checking if the interrupt flag was initially active or not*/
	if(ReadBit(EEPROM_SREG,SREG_I)==1)
	{
		ClearBit(EEPROM_SREG,SREG_I);
		/*raising the flag that the interrupt was active*/
		interrupt_flag=1;		
	}
		ClearBit(EEPROM_SREG,SREG_I);
	/*waiting until the previouse operation is finished if there're any*/
	while(ReadBit(EEPROM_EECR,EECR_EEWE)==1);
	/*putting the desired adresse of the memory*/
	EEPROM_EEARL=(addresse);
	/*passing the desired byte to be written inside the eedr*/
	EEPROM_EEDR=(data);
	/*setting the write bit to enable eeprom writting*/
	SetBit(EEPROM_EECR,EECR_EEMWE);
	/*setting the eeprom operating bit to start writting*/
	SetBit(EEPROM_EECR,EECR_EEWE);

	/*checking if the write bit is on or off*/
	if (ReadBit(EEPROM_EECR,EECR_EEWE)==0)
	{
		errorflag=EEPROM_WRITE_Error;
	}
	/*checking the interrupt flag*/
	if(interrupt_flag==1)
	{
		SetBit(EEPROM_SREG,SREG_I);	
	}
	/*returning the function status*/
	return errorflag;
}

EepromStatus EEPROM_READ(uint8 addresse,uint8* read)
{
	/*create an error flag */
	uint8 errorflag=EEPROMok;
	/*creating an interrupt flag*/
	uint8 interrupt_flag=0;
	/*checking if the interrupt flag was initially active or not*/
	if(ReadBit(EEPROM_SREG,SREG_I))
	{
		ClearBit(EEPROM_SREG,SREG_I);
		/*raising the flag that the interrupt was active*/
		interrupt_flag=1;
	}
	/*waiting until the previouse operation is finished if there're any*/
	while(ReadBit(EEPROM_EECR,EECR_EEWE));
	/*putting the desired adresse of the memory*/
	EEPROM_EEARL=(addresse);
	/*setting the write bit to enable eeprom reading*/
	SetBit(EEPROM_EECR,EECR_EERE);
	/*delaying to make sure that the read function is done*/
	/*checking if the read bit is on or off*/
	if (ReadBit(EEPROM_EECR,EECR_EERE)==0)
	{
		errorflag=EEPROM_WRITE_Error;
	}
	/*checking the interrupt flag*/
	if(interrupt_flag==1)
	{
		SetBit(EEPROM_SREG,SREG_I);
	}
	/*reading the desired byte from the EEDR REGISTER*/
	*(read)=EEPROM_EEDR;
	/*returning the function status*/
	return errorflag;
}
