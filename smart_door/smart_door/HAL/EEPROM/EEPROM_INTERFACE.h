/*
 * EEPROM_INTERFACE.h
 *
 * Created: 8/28/2022 4:12:35 AM
 *  Author: mohye
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/*the fixed addresse for the eeprom*/
#define EEPROM_FIXED_ADDRESS		0b1010000

/*Choose the hardware connection option for A2 Pin: 0 if connected to gnd,1 if connected to VCC*/
#define A2_CONNECTION			0

/*a function used to send a byte to the eeprom memory*/
void EEPROM_SENDBYTE(uint16 MemoryAddresse,uint8 ByteSent);

/*a function used to read a byte from the eeprom memory*/
uint8 EEPROM_READBYTE(uint16 MemoryAddresse);



#endif /* EEPROM_INTERFACE_H_ */