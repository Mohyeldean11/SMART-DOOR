/*
 * TWI_PRIVATE.h
 *
 * Created: 8/3/2022 7:44:48 PM
 *  Author: mohye
 */ 


#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

											/************************************************************************/
											/*						REGISTERS                                       */
											/************************************************************************/

#define  TWI_TWDR					(*(volatile uint8*)(0x23))

#define  TWI_TWCR					(*(volatile uint8*)(0x56))
	#define TWCR_TWINT							7
	#define TWCR_TWEA							6
	#define TWCR_TWSTA							5
	#define TWCR_TWSTO							4
	#define TWCR_TWWC							3
	#define TWCR_TWEN							2
	#define TWCR_TWIE							0
	

#define TWI_TWAR					(*(volatile uint8*)(0x22))

	#define TWAR_TWA6							7
	#define TWAR_TWA5							6
	#define TWAR_TWA4							5
	#define TWAR_TWA3							4
	#define TWAR_TWA2							3
	#define TWAR_TWA1							2
	#define TWAR_TWA0							1
	#define TWAR_TWGCE							7




#define TWI_TWSR					(*(volatile uint8*)(0x21))
	#define TWSR_TWS7							7
	#define TWSR_TWS6							6
	#define TWSR_TWS5							5
	#define TWSR_TWS4							4
	#define TWSR_TWS3							3

	#define TWSR_TWPS1							1
	#define TWSR_TWPS0							0


#define TWI_TWBR					(*(volatile uint8*)(0x20))

#endif /* TWI_PRIVATE_H_ */