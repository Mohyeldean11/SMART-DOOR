/*
 * MCU_EEPROM_PRIVATE.h
 *
 * Created: 8/28/2022 4:09:54 PM
 *  Author: mohye
 */ 


#ifndef MCU_EEPROM_PRIVATE_H_
#define MCU_EEPROM_PRIVATE_H_


#define EEPROM_EEDR			(*(volatile uint8*)(0x3D))
			
#define EEPROM_EEARL		(*(volatile uint8*)(0x3E))
#define EEPROM_EEARH		(*(volatile uint8*)(0x3F))


#define EEPROM_EECR			(*(volatile uint8*)(0x3C))
			#define EECR_EERE				(0)
			#define EECR_EEWE				(1)
			#define EECR_EEMWE				(2)
			#define EECR_EERIE				(3)

#define EEPROM_EEARH		(*(volatile uint8*)(0x3F))
			#define EEARH_EEAR9				(1)
			#define EEARH_EEAR8				(2)
	
#define EEPROM_SREG			(*(volatile uint8*)(0x5F))
			#define SREG_I					(7)
#endif /* MCU_EEPROM_PRIVATE_H_ */