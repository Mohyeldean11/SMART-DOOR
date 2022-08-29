/*
 * IR_INTERFACE.h
 *
 * Created: 8/29/2022 6:25:33 AM
 *  Author: mohye
 */ 


#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_

/*assigning the ir port and pin*/
#define IR_PORT					PORTA
		#define	IR_PIN			pin7
		
		
/*a function to read the IR VALUE*/		
uint8 IR_GET_READ(void);



#endif /* IR_INTERFACE_H_ */