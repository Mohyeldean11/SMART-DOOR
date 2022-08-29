/*
 * MCU_EEPROM_INTERFACE.h
 *
 * Created: 8/28/2022 4:09:41 PM
 *  Author: mohye
 */ 


#ifndef MCU_EEPROM_INTERFACE_H_
#define MCU_EEPROM_INTERFACE_H_


/*eeprom function status*/
typedef enum EEPROM_ERROR_STATUS
{
	EEPROMok,EEPROM_WRITE_Error,EEPROM_READ_Error
	}EepromStatus;

/*a function to write on the internal eeprom memory*/
EepromStatus EEPROM_Write(uint8 addresse,uint8 data);

/*a function to read  from the internal eeprom memory*/
EepromStatus EEPROM_READ(uint8 addresse,uint8* read);


#endif /* MCU_EEPROM_INTERFACE_H_ */