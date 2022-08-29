/*
 * APP_INTERFACE.h
 *
 * Created: 8/27/2022 10:09:36 PM
 *  Author: mohye
 */ 


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*a function to initialize all the used drivers in the application*/
void INITIALIZE_ALL(void);

/*a function to turn on the buzzer*/
void BUZZERON(void);

/*a function to turn off the buzzer*/
void BUZZEROFF(void);

/*the algorithm for the whole application*/
void AppWorking(void);


#endif /* APP_INTERFACE_H_ */