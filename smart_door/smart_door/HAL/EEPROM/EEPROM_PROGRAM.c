/*
 * EEPROM_PROGRAM.c
 *
 * Created: 8/28/2022 4:12:06 AM
 *  Author: mohye
 */ 

#include "../../UTILITIES/DataTypes.h"
#include "../../MCAL/I2C/TWI_INTERFACE.h"
#include "EEPROM_INTERFACE.h"

/*a function used to send a byte to the eeprom memory*/
void EEPROM_SENDBYTE(uint16 MemoryAddresse,uint8 ByteSent)
{
	/*creating an adressepacket to have the slave adresse of the eeprom*/
	uint8 addressepacket=(EEPROM_FIXED_ADDRESS)|(uint8)(MemoryAddresse>>8);
	/*sending a start condition to initialize the communication*/
	Twi_MasterStart();
	/*sending the addresse packet with write operation*/
	Twi_MasterSend_SLA_W(addressepacket);
	/*choosing the memory adresse of which place to write*/
	Twi_MastersendByte((uint8)(MemoryAddresse));
	/*writing the byte sent to the desired memory adresse*/
	Twi_MastersendByte(ByteSent);
	/*stopping the communication*/
	Twi_MasterStop();
}
uint8 EEPROM_READBYTE(uint16 MemoryAddresse)
{
	/*creating a pointer to carry the value of the read byte*/
	uint8 READVALUE=0;
	/*creating an adressepacket to have the slave adresse of the eeprom*/
	uint8 addressepacket=(EEPROM_FIXED_ADDRESS)|(uint8)(MemoryAddresse>>8);
	/*sending a start condition to initialize the communication*/
	Twi_MasterStart();
	/*sending the addresse packet with write operation*/
	Twi_MasterSend_SLA_W(addressepacket);
	/*initializing a repeated start to change the operation to reading from the memory*/
	Twi_MasterRepeatedStart();
	/*choosing the memory adresse to be read from the eeprom*/
	Twi_MasterSend_SLA_R((uint8)(MemoryAddresse));
	/*reading the byte from the desired memory adresse*/
	Twi_MasterReceiveByte(&READVALUE);
	/*stopping the communication*/
	Twi_MasterStop();
	/*returning the read byte from the function*/
	return (READVALUE);
}