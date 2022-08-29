/*
 * TWI_PROGRAM.c
 *
 * Created: 8/28/2022 1:39:12 AM
 *  Author: mohye
 */ 
#include "../../UTILITIES/DataTypes.h"
#include "../../UTILITIES/bitmath.h"
#include "TWI_PRIVATE.h"
#include "TWI_INTERFACE.h"

/*a function to initialize the Master*/
TWI_ErrorStatus Twi_MasterInit(uint8 SlaveAdresse)
{
	/*creating an error flag*/
	uint8 Errorflag=TWI_ok;
	/*setting the SYSTEM CLOCK FREQUENCY TWBR TO 72*/
	TWI_TWBR=3;
	/*setting the TWPS VALUE TO 0*/
	ClearBit(TWI_TWSR,TWSR_TWPS0);
	ClearBit(TWI_TWSR,TWSR_TWPS1);
	/*NOW THE SCL FREQUENCY IS 100KhZ*/
	
	/*assigning a slave adress to the master incase it changed to slave*/
	if (SlaveAdresse!=0)
	{
		TWI_TWAR=(SlaveAdresse<<1);
	}
	/*RESETTING THE CONTROL REGISITER*/
	TWI_TWCR=0;
	
	/*enabling the acknowledge bit*/
	SetBit(TWI_TWCR,TWCR_TWEA);
	
	/*checking if the interrupt enable flag is set or not */
	if(ReadBit(TWI_TWCR,TWCR_TWINT))
	{
		Errorflag=TWI_InitError;
	}
	return Errorflag;
}

/*a function to send a start condition*/
TWI_ErrorStatus Twi_MasterStart(void)
{
	/*creating an error flag*/
	uint8 Errorflag=TWI_ok;
	/*sending a start condition*/
	SetBit(TWI_TWCR,TWCR_TWSTA);
	/*enabling the TWO WIRE INTERFACE*/
	SetBit(TWI_TWCR,TWCR_TWEN);
	/*clearing the twi int flag to perform the start condition*/
	SetBit(TWI_TWCR,TWCR_TWINT);
	/*waiting untill the interrupt flag is one again*/
	while(ReadBit(TWI_TWCR,TWCR_TWINT)==0);
	
	/*checking for the status of the status register*/
	if ((TWI_TWSR&(0xF8))!=Start_MasterTransmit)
	{
		Errorflag=TWI_StartError;
	}
	return Errorflag;
}

/*a function to send a repeated start*/
TWI_ErrorStatus Twi_MasterRepeatedStart(void)
{
		/*creating an error flag*/
		uint8 Errorflag=TWI_ok;
		
		/*sending a start condition*/
		SetBit(TWI_TWCR,TWCR_TWSTA);
		/*enabling the TWO WIRE INTERFACE*/
		SetBit(TWI_TWCR,TWCR_TWEN);
		/*clearing the twi int flag to perform the start condition*/
		SetBit(TWI_TWCR,TWCR_TWINT);

		/*waiting untill the interrupt flag is one again*/
		while(!(ReadBit(TWI_TWCR,TWCR_TWINT)));
		
		/*checking for the status of the status register*/
		if ((TWI_TWSR&(0xF8))!=RepeatedStart_MasterTransmit)
		{
			Errorflag=TWI_RepeatedStartError;
		}
		/*returning the status of the function*/		
		return Errorflag;	
}

/*a function to send a write command along with the slave addresse*/
TWI_ErrorStatus Twi_MasterSend_SLA_W(uint8 SLaveAdresse)
{
		/*creating an error flag*/
		uint8 Errorflag=TWI_ok;

		/*loading the slave addresse in the data register*/
		TWI_TWDR=(SLaveAdresse<<1);
		/*sending a write order*/
		ClearBit(TWI_TWDR,0);

		/*enabling the TWO WIRE INTERFACE*/
		//SetBit(TWI_TWCR,TWCR_TWEN);
		
		/*clearing the twi int flag to perform the start condition*/
		SetBit(TWI_TWCR,TWCR_TWINT);
		/*waiting untill the interrupt flag is one again*/
		while(!(ReadBit(TWI_TWCR,TWCR_TWINT)));

		/*checking for the status of the status register*/
		if ((TWI_TWSR&(0xF8))!=SLA_Ack_MasterTransmit)
		{
			Errorflag=TWI_Sla_W_Error;
		}
		/*returning the status of the function*/
		return Errorflag;
}

/*a function to send a Read command along with the slave addresse*/
TWI_ErrorStatus Twi_MasterSend_SLA_R(uint8 SlaveAdresse)
{
		/*creating an error flag*/
		uint8 Errorflag=TWI_ok;
		/*stopping the start condition*/
		//ClearBit(TWI_TWCR,TWCR_TWSTA);
		
		
		/*loading the slave addresse in the data register*/
		TWI_TWDR|=(SlaveAdresse<<1);
		/*sending a READ order*/
		SetBit(TWI_TWDR,0);
		
		/*enabling the TWO WIRE INTERFACE*/
		SetBit(TWI_TWCR,TWCR_TWEN);
		
		/*clearing the twi int flag to perform the start condition*/
		SetBit(TWI_TWCR,TWCR_TWINT);
		/*waiting untill the interrupt flag is one again*/
		while(!(ReadBit(TWI_TWCR,TWCR_TWINT)));
		
		/*checking for the status of the status register*/
		if ((TWI_TWSR&(0xF8))!=SLA_Ack_MasterTransmit)
		{
			Errorflag=TWI_Sla_R_Error;
		}
		/*returning the status of the function*/
		return Errorflag;	
}

/*a function to send a byte to the slave*/
TWI_ErrorStatus Twi_MastersendByte(uint8 Data)
{
		/*creating an error flag*/
		uint8 Errorflag=TWI_ok;
		/*loading the data to be transferred in the data register*/
		TWI_TWDR=Data;
		/*clearing a start condition*/
		ClearBit(TWI_TWCR,TWCR_TWSTA);

		/*clearing the twi int flag to perform the start condition*/
		SetBit(TWI_TWCR,TWCR_TWINT);
		
		/*waiting untill the interrupt flag is one again*/
		while(!(ReadBit(TWI_TWCR,TWCR_TWINT)));
		
		/*checking for the status of the status register*/
		if ((TWI_TWSR&(0xF8))!=Data_Ack_MasterTransmit)
		{
			Errorflag=TWI_DataSendError;
		}
		/*returning the status of the function*/
		return Errorflag;	
}

/*a function to receive a byte from the slave*/
TWI_ErrorStatus Twi_MasterReceiveByte(uint8 *Data)
{
		/*creating an error flag*/
		uint8 Errorflag=TWI_ok;

		/*clearing the twi int flag to perform the start condition*/
		SetBit(TWI_TWCR,TWCR_TWINT);
		/*waiting untill the interrupt flag is one again*/
		while(!(ReadBit(TWI_TWCR,TWCR_TWINT)));
		
		/*checking for the status of the status register*/
		if ((TWI_TWSR&(0xF8))!=Data_Ack_MasterTransmit)
		{
			Errorflag=TWI_DataReceiveError;
		}
		/*reading the received data from the data register*/
		*(Data)=TWI_TWDR;
		/*returning the status of the function*/
		return Errorflag;	
}

/*a function to send a stop condition*/
TWI_ErrorStatus Twi_MasterStop(void)
{
	/*creating an error flag*/
	uint8 Errorflag=TWI_ok;
	/*sending a stop condition*/
	SetBit(TWI_TWCR,TWCR_TWSTO);
	/*clearing the twi int flag to perform the start condition*/
	SetBit(TWI_TWCR,TWCR_TWINT);
	
	return Errorflag;
}