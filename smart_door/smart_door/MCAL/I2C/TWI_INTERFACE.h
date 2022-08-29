/*
 * TWI_INTERFACE.h
 *
 * Created: 8/28/2022 1:39:01 AM
 *  Author: mohye
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/*the I2C error status*/
typedef enum  TWI_ErrorStatus
{
	TWI_ok,
	TWI_InitError,
	TWI_StartError,
	TWI_StopError,
	TWI_Sla_W_Error,
	TWI_Sla_R_Error,
	TWI_DataSendError,
	TWI_DataReceiveError,
	TWI_RepeatedStartError
}TWI_ErrorStatus;

/************************************************************************/
/*								TWI STATUS                              */
/************************************************************************/

/*MASTER TRANSMIT*/
#define		Start_MasterTransmit											(0x08)
#define		RepeatedStart_MasterTransmit									(0x10)
#define		SLA_Ack_MasterTransmit											(0x18)
#define		SLA_NotAck_MasterTransmit										(0x20)
#define     Data_Ack_MasterTransmit											(0x28)
#define		Data_NotAck_MasterTransmit										(0x30)
#define		ArbLost_MasterTransmit
/*MASTER RECEIVE*/
#define		SLA_Ack_MasterReceive											(0x38)
#define		SLA_NotAck_MasterReceive										(0x40)
#define     Data_Ack_MasterReceive											(0x50)
#define		Data_NotAck_MasterReceive										(0x58)
#define		ArbLost_MasterReceive


/************************************************************************/
/*								INTERFACING MACROS                      */
/************************************************************************/


/*TWPS VALUES */  //ITS NOT USED IN THIS DRIVER
#define  TWPS_1																0
#define  TWPS_4																1
#define  TWPS_16															2
#define  TWPS_64															3




/*a function to initialize the Master*/
TWI_ErrorStatus Twi_MasterInit(uint8 SlaveAdresse);

/*a function to send a start condition*/
TWI_ErrorStatus Twi_MasterStart(void);

/*a function to send a repeated start*/
TWI_ErrorStatus Twi_MasterRepeatedStart(void);

/*a function to send a write command along with the slave addresse*/
TWI_ErrorStatus Twi_MasterSend_SLA_W(uint8 SlaveAdresse);

/*a function to send a Read command along with the slave addresse*/
TWI_ErrorStatus Twi_MasterSend_SLA_R(uint8 SlaveAdresse);

/*a function to send a byte to the slave*/
TWI_ErrorStatus Twi_MastersendByte(uint8 Data);

/*a function to receive a byte from the slave*/
TWI_ErrorStatus Twi_MasterReceiveByte(uint8 *Data);

/*a function to send a stop condition*/
TWI_ErrorStatus Twi_MasterStop(void);




#endif /* TWI_INTERFACE_H_ */