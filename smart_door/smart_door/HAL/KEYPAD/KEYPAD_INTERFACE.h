/*
 * KEYPAD.h
 *
 * Created: 8/27/2022 8:33:32 PM
 *  Author: mohye
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

/*a function to initialize the keypad*/
void KeyPad_Init(void);
/*a function to wait for the key to be pressed before getting another key*/
uint8 KeyPad_Work(void);
/*a function to get the pressed key with debouncing fixations*/
static uint8 KeyPad_GetKey(void);


#endif /* KEYPAD_H_ */